
// *********************************************************************
// * CLAIRE                                            Sylvain Benilan *
// * scanf.cl                                                          *
// * Copyright (C) 2005 xl. All Rights Reserved                        *
// *********************************************************************

//<sb> This file implements the evaluation part of the scanf construction
// which is at read what printf is at write. It is aimed at make the boring
// task of parsing simpler, i.e. realize in a simple way the extraction of
// datas inherent to a given protocol. The construct is used as follow :
//
// 			scanf(<input>, "regex" [, arg]* [, res [, err]?]?)
//
// 		where :
// 			input evaluates to a string or a port : the input data stream
// 			regex is a static string representing the regular expression
// 			arg(s) is a list of arguments (say regex parameters)
// 			res if any is the returned value of scanf in case of match
//
// 		return value :
// 			true or res (when given) if the entire regex matched the input
// 			false otherwise
//
// Scanf implements regular expression matching (grep) and stream editing (sed)'s
// like concepts but tightly integrated with the claire language, that is it offer
// parametric behavior of the expression. Indeed, as a descendent of claire 
// Construct lexical object, scanf takes a list of instruction as arguments that are
// parametrized by named captures stored in language variables and defined "on the
// fly" having the scope of the scanf construct and therefore visible from its
// arguments. For instance we can write :
//
// 			scanf("<foo>", "<$v>~I", princ(v))
// 
// 		that would princ 'foo' and return true.
//
//			scanf("<foo>", "<$v>", v)
//
// 		would return the string "foo"
//
// Scanf constructs may be nested (as we write nested printfs), a special filter
// is silently used to make nested constructs working together on a unique buffer
// that is used to performs matches. This ensures that an inner scanf, that wouldn't
// match, won't cause data loss from the outer scanf point of view. This filter is
// implemented in the Core module (port.cl) such that compiled code using scanf may not
// use the Reader.
// 
// Reading a Scanf construct differ from reading a normal call because we have
// to create the reader binding for variables implicitly defined by the regular
// expression such to properly read arguments (that may use these variables).
// At evaluation time the internal 'compiled' expression is processed by our
// matching algorithm.
// At compile time (hidden from this file) the expression is inlined in the
// target code with an optimized substitution from the model defined in this
// file to a claire instruction where the static part of the regular expression
// has been efficiently hard-coded.




// *******************************************************************
// *       Part 1: formatter specification                           *
// *       Part 2: model                                             *
// *       Part 3: printing back formatter                           *
// *       Part 4: reading formatter                                 *
// *       Part 5: building next chain                               *
// *       Part 6: primitive matching                                *
// *       Part 7: matching evaluator                                *
// *       Part 8: reseting loops                                    *
// *       Part 9: evaluation                                        *
// *       Part 10: variable initialization                          *
// *       Part 11: reading lazy arguments                           *
// *******************************************************************




// *******************************************************************
// *       Part 1: formatter specification                           *
// *******************************************************************

//<sb> note : in the following description <arg> denotes an instruction given
// as a scanf argument. Arguments are popped from the argument list as they
// are read in the regex string. Users familiar with grep syntax will find
// similarities.

/*

-------------------------------------------------------------------------
	escapes
-------------------------------------------------------------------------

\aaa					a normal reader escape as for strings
						(e.g. \n, \r, \x12, etc...)

%x						regular escape of char x (i.e. consider x as a
						normal character)

-------------------------------------------------------------------------
	character class
-------------------------------------------------------------------------

~S					matches one of CR, LF, TAB, SP aka \r, \n, \t and space
~E					matches the end of file	condition

[<good>]			character class match
[^<bad>]			exclusive character class match
[<good>^<bad>]		character class match with an exclusion class

	where <good> and <bad> are any character but '^', '-' and ']' unless
	they are escaped by a '%'

	note : at read time '^' toggles the filled buffer to <good> or <bad>, thus
	multiple '^' may occur...

-------------------------------------------------------------------------
	variables (or captures)
-------------------------------------------------------------------------

$x				variable length capture bounded by next static conditions
${xxx}

$ddd>x			variable length capture bounded by static conditions that match
$ddd>{xxx}		and with a length < ddd (where d is a digit)

<exp>:$x		capture the string that matched exp
<exp>:${xxx}

$dddx			fix length capture (d is a digit)
$ddd{xxx}
$~x				<arg> evaluates to the requested length for the capture x
$~{xxx}

	where xxx is used for the name of the claire variable. if the name of the variable
	is 1 char long one can use the curlyless form

-------------------------------------------------------------------------
	item variables (or list captures)
-------------------------------------------------------------------------


$[xxx]			variable length capture where the capture is added in a list named xxx
$ddd[xxx]		fix length capture (d is a digit) added to a list
$~[xxx]			<arg> evaluates to the requested length for the capture xxx added to a list
<exp>:$[xxx]	capture the string that matched exp and add it in a list named xxx

	notice that the list is never shrinked, the user can however does it in an argument

-------------------------------------------------------------------------
	reference
-------------------------------------------------------------------------

@x			named reference to the value of a variable or a global variable
@{xxx}

~A			references the value that <arg> evaluates

	the following matching rule applies depending on the type
	of the referenced value :
		- string -> princ(<value>)
		- integer -> princ(<value>)    (including the minus sign of a negative value)
		- char -> princ(<value>)
		- bag -> recurse elements and find the longest match

-------------------------------------------------------------------------
	logic
-------------------------------------------------------------------------

<exp>|<exp>		alternative
(<exps>)		grouping

-------------------------------------------------------------------------
	direct use of arguments
-------------------------------------------------------------------------

~I		evaluates <arg>, always matched
~B		not matched if <arg> evaluates to nil or false

-------------------------------------------------------------------------
	loops
-------------------------------------------------------------------------

<exp>?					0 or once
<exp>*					0 or more times
<exp>+					1 or more times
<exp>:{mm}				exactly mm times
<exp>:{mm,}				at least mm times
<exp>:{mm,MM}			at least mm times but no more than MM times
<exp>:{~S}				exactly eval(arg) times
<exp>:{~S,}				at least eval(<arg>) times
<exp>:{~S,~S}			at least eval(<arg>) times but no more than eval(<arg>) times

	where mm and MM are digits

TODO:
	<loop>::$x				capture the loop hit count in a variable x or xxx
	<loop>::${xxx}


-------------------------------------------------------------------------
	reformating (sed)
-------------------------------------------------------------------------

<exp>:(<printf exp>)	if exp matches, evaluates the printf exp

	remainder : in a printf one can use
		~S that evaluates to print(<arg>)
		~A that evaluates to princ(<arg>)
		~I that evaluates to <arg>
	additionnaly :
		@x and @{xxx} is supported as the princ of the variable or
		global variable x

*/

// *******************************************************************
// *       Part 2: model                                             *
// *******************************************************************

char_interval <: object(arg1:char, arg2:char)

scanf_match <: object
scanf_match <: object(next:scanf_match)
	alternative_match <: scanf_match(args:list[scanf_match])
	group_match <: scanf_match(args:list[scanf_match])
	loop_match <: scanf_match(arg:scanf_match, hit:integer = 0, reenter?:boolean = false, minoccur:any = 0, maxoccur:any, maxismin?:boolean = false)
	reformat_match <: scanf_match(arg:scanf_match, reformat:list[any])
	variable_match <: scanf_match(name:string, max_length:integer, value:blob, previous:port, var:Variable, reformated?:boolean = false)
	variable_item_match <: variable_match()
	at_match <: scanf_match(name:string, var:(Variable U global_variable))
	static_match <: scanf_match()
		fixlength_match <: scanf_match(name:string, length:any, value:string, var:Variable)
		fixlength_item_match <: fixlength_match()
		assign_match <: scanf_match(name:string, arg:scanf_match, value:string, var:Variable)
		assign_item_match <: assign_match()
		~S_match <: static_match()
		string_match <: static_match(arg:string)
		char_match <: static_match(good:list[any], bad:list[any])
		eof_match <: scanf_match()
		~_match <: static_match(arg:any)
			~A_match <: ~_match()
			~I_match <: ~_match()
			~B_match <: ~_match()

//<sb> the end of the 'next chain' is terminated by an 'end_of_match' pattern
// which would raise a 'match_successful' exception. This way the whole exploration
// stack (due to recursive implementation) is efficiently terminated (short cut of
// the normal recursive epilogue of each call of the stack). The scanf evaluator is
// responsible to catch the special 'match_successful' exception :
match_successful <: exception()
MATCH_SUCCESSFUL :: mClaire/new!(match_successful) //<sb> use a single instance

end_of_match :: scanf_match()

valid_match :: scanf_match()

//<sb> a special variable used when no current variable
no_var :: variable_match(name = "no-var")


//<sb> we need special instances used for lazy argument initialization
// that will be substituted at read time (i.e. after language variable
// binding) by the corresponding scanf argument
lazy_arg :: thing()
lazy_princ :: thing()
lazy_print :: thing()


// *******************************************************************
// *       Part 3: printing back formatter                           *
// *******************************************************************


self_print(self:string_match) : void -> princ(self.arg)

self_print(self:char_match) : void ->
	printf("``GREEN[~I~I]",
		for c in self.good
			(case c
				(char_interval printf("``GREEN~A-~A", c.arg1, c.arg2),
				char princ(c))),
		(if self.bad
			(printf("``GREEN^"),
			for c in self.bad
				(case c
					(char_interval printf("``GREEN~A-~A", c.arg1, c.arg2),
					char princ(c))))))

[self_print(self:eof_match) : void -> princ("~E")]

[self_print(self:group_match) : void ->
	for x in self.args print(x)]

[self_print(self:alternative_match) : void ->
	let f? := true
	in printf("``BLACK(~I)",
		for x in self.args
			printf("~I~S",
				(if f? f? := false else princ("|")),
				x))]

[self_print(self:loop_match) : void ->
	if (self.minoccur = 0 & unknown?(maxoccur, self))
		printf("`RED(~S)*", self.arg)
	else if (self.minoccur = 0 & self.maxoccur = 1)
			printf("`RED(~S)?", self.arg)
	else if (self.minoccur = 1 & unknown?(maxoccur, self))
			printf("`RED(~S)+", self.arg)
	else printf("`RED(~S):{~S~I}", self.arg,
		self.minoccur,
		(if (known?(maxoccur, self) & not(self.maxismin?))
			printf(",~S", self.maxoccur)))]

self_print(self:~S_match) : void -> princ("~S")

self_print(self:~_match) : void ->
	printf("{~S}", self.arg)

self_print(self:variable_match) : void ->
	printf("`BLUE$~I{~A}",
			(if known?(max_length, self) printf("`BLUE~S>", self.max_length)),
			self.name)

self_print(self:fixlength_match) : void ->
	printf("`BLUE$(~S){~A}", self.length, self.name)

self_print(self:assign_match) : void ->
	printf("`BLUE(~S):${~A}", self.arg, self.name)

self_print(self:at_match) : void ->
	printf("`BLUE@{~A}", self.name)

self_print(self:reformat_match) : void ->
	printf("(~S):(~A)", self.arg, self.reformat)


// *******************************************************************
// *       Part 4: reading formatter                                 *
// *******************************************************************

[formater!(self:string) : scanf_match ->
	let a := alternative_match()
	in (read_alternative(blob!(self), a),
		build_next_chain(a),
		a)]


[read_char(self:blob) : char_match ->
	let res := char_match(),
		cur := res.good
	in (while not(eof?(self))
			let c := getc(self)
			in case c
				({'^'} cur := (if (cur = res.good) res.bad else res.good),
				{']'} break(),
				{'-'}
					(c := getc(self),
					if cur
						let prev := last(cur)
						in (rmlast(cur),
							cur add char_interval(arg1 = prev, arg2 = c))),
				{'%'} cur add getc(self),
				any cur add c),
		res)]

[read_at(self:blob) : at_match ->
	let c := fread(self, 1)
	in at_match(name = (if (c = "{") freadline(self, "}") else c))]

[read_assign(self:blob) : assign_match ->
	let item? := false,
		c := fread(self, 1),
		nm := (case c
				({"{"} freadline(self, "}"),
				{"["} (item? := true, freadline(self, "]")),
				any c))
	in (if item?
			assign_item_match(name = nm)
		else
			assign_match(name = nm))]
	

[read_var(self:blob) : scanf_match ->
	let c := fread(self, 1),
		n := 0
	in (if (c = "~")
			(c := fread(self, 1),
			let item? := false,
				nm := (case c
						({"{"} freadline(self, "}"),
						{"["} (item? := true, freadline(self, "]")),
						any c))
			in (if item?
					fixlength_item_match(name = nm, length = lazy_arg)
				else
					fixlength_match(name = nm, length = lazy_arg)))
		else
			(while (c % {"0","1","2","3","4","5","6","7","8","9"})
				(n := 10 * n + integer!(c),
				c := fread(self, 1)),
			if (c = ">")
				(if eof?(self)
					error("premature end of formatter near ...$~S", n),
				c := fread(self, 1),
				let item? := false,
					nm := (case c
							({"{"} freadline(self, "}"),
							{"["} (item? := true, freadline(self, "]")),
							any c))
				in (if item? variable_item_match(name = nm, max_length = n)
					else variable_match(name = nm, max_length = n)))
			else let item? := false,
					nm := (case c ({"{"} freadline(self, "}"), 
									{"["} (item? := true,
											freadline(self, "]")),
									any c))
				in (if (n = 0)
						(if item? variable_item_match(name = nm)
						else variable_match(name = nm))
					else if item? fixlength_item_match(name = nm, length = n)
					else fixlength_match(name = nm, length = n))))]
	

[read_reformat(self:blob, cur:reformat_match) : reformat_match ->
	while not(eof?(self))
		let (data, e) :=
			freadline(self, {"~S", "~A", "~I", ")", "@"}, true, '%')
		in (if (length(data) > 0)
				cur.reformat add Call(princ, list(data)),
			case e
				({"~S"} cur.reformat add lazy_print,
				{"~A"} cur.reformat add lazy_princ,
				{"~I"} cur.reformat add lazy_arg,
				{"@"} let c := fread(self, 1)
						in cur.reformat add (case c ({"{"} freadline(self, "}"), any c)),
				{")"} break())), cur]

[read_occur(self:blob, cur:loop_match) : loop_match ->
	let (data, e) := freadline(self, {"}"}),
		l := explode(data, ",")
	in (if (length(l) >= 1)
			case l[1]
				({"~S"} cur.minoccur := lazy_arg,
				any cur.minoccur := integer!(l[1])),
		if (length(l) >= 2)
			case l[2]
				({"~S"} cur.maxoccur := lazy_arg,
				any cur.maxoccur := integer!(l[2]))
		else cur.maxismin? := true,
		cur)]

ALTERNATIVE_SEPS :: {"$",":$","@",":(", ":{", "[","*","+","?","(",")","|","~S","~A","~I","~E","~B"}

//<sb> read a formatter alternative
[read_alternative(self:blob, alt:alternative_match) : alternative_match ->
	let cur := group_match()
	in (alt.args add cur,
		while not(eof?(self))
			let (data, e) :=
				freadline(self, ALTERNATIVE_SEPS, true, '%')
			in (if (length(data) > 0) cur.args add string_match(arg = data),
				case e
					({"["} cur.args add read_char(self),
					{"("} let a := alternative_match()
						in cur.args add read_alternative(self, a),
					{"*"} let l := cur.args, len := length(l)
						in (if (len = 0) error("Misplaced * sign in a scanf expression"),
							l[len] := loop_match(arg = l[len])),
					{"+"} let l := cur.args, len := length(l)
						in (if (len = 0) error("Misplaced + sign in a scanf expression"),
							l[len] := loop_match(arg = l[len], minoccur = 1)),
					{":{"} let l := cur.args, len := length(l)
						in (if (len = 0) error("Misplaced :{ sign in a scanf expression"),
							l[len] := read_occur(self, loop_match(arg = l[len]))),
					{"?"} let l := cur.args, len := length(l)
						in (if (len = 0) error("Misplaced ? sign in a scanf expression"),
							l[len] := loop_match(arg = l[len], maxoccur = 1)),
					{"|"} (cur := group_match(), alt.args add cur),
					{")"} break(),
					{":("} let l := cur.args, len := length(l)
							in (if (len = 0) error("Misplaced :( sign in a scanf expression"),
								l[len] := read_reformat(self, reformat_match(arg = l[len]))),
					{"$"} cur.args add read_var(self),
					{":$"} let l := cur.args, len := length(l),
								c := read_assign(self)
						in (if (len = 0) error("Misplaced :$ sign in a scanf expression"),
							c.arg := l[len],
							l[len] := c), 
					{"@"} cur.args add read_at(self),
					{"~S"} cur.args add ~S_match(),
					{"~E"} cur.args add eof_match(),
					{"~A"} cur.args add ~A_match(arg = lazy_arg),
					{"~I"} cur.args add ~I_match(arg = lazy_arg),
					{"~B"} cur.args add ~B_match(arg = lazy_arg))),
		alt)]

// *******************************************************************
// *       Part 5: building next chain                               *
// *******************************************************************

[build_next_chain(self:scanf_match, candidate:scanf_match) : void ->
	self.next := candidate]

[build_next_chain(self:group_match, candidate:scanf_match) : void ->
	let i := 1,
		l := self.args,
		len := length(l)
	in while (i <= len)
		(if (i = len)
			build_next_chain(l[i], candidate)
		else build_next_chain(l[i], l[i + 1]),
		i :+ 1)]

[build_next_chain(self:alternative_match, candidate:scanf_match) : void ->
	for x in self.args
		build_next_chain(x, candidate)]

[build_next_chain(self:loop_match, candidate:scanf_match) : void ->
	self.next := candidate,
	build_next_chain(self.arg, self)]

[build_next_chain(self:alternative_match) : void ->
	build_next_chain(self, end_of_match)]

[build_next_chain(self:reformat_match, candidate:scanf_match) : void ->
	self.next := candidate,
	build_next_chain(self.arg, valid_match)]

[build_next_chain(self:assign_match, candidate:scanf_match) : void ->
	self.next := candidate,
	build_next_chain(self.arg, valid_match)]



// *******************************************************************
// *       Part 7: matching evaluator                                *
// *******************************************************************

match? :: property(open = 3, range = boolean)

[match?(self:scanf_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	update_variable(avar),
	if (self = valid_match) true
	else close(MATCH_SUCCESSFUL)] //<sb> should be end_of_match

(interface(match?))

INDENT:integer := 0

[debug_match?(self:scanf_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	let res := false
	in (if (verbose() > 2)
			printf(ctrace(), "~I``BLACK>>>[~A~I~I]>>> [~S] next[~S]\n~I\\\\\\~A\n",
					for i in (0 .. INDENT) printf("~S ", i),
					replace(owner(self).name.name, "_match", ""),
					(case self
						(loop_match printf(ctrace(), " ``BLUEhit ~S", self.hit))),
					(if (avar != no_var) printf(ctrace(), "``RED (~S)", avar)),
					self,
					self.next,
					for i in (0 .. INDENT) printf("~S ", i),
					p),
		INDENT :+ 1,
		res := match?(self, p, avar),
		INDENT :- 1,
		if (verbose() > 2)
			printf(ctrace(), "~I``BLACK<<<[~A~I]<<< [~S] next[~S] ~I\n",
					for i in (0 .. INDENT) printf("~S ", i),
					replace(owner(self).name.name, "_match", ""),
					(case self
						(loop_match printf(ctrace(), " ``BLUEhit ~S", self.hit))),
					self,
					self.next,
					(if res printf(ctrace(), "``GREENOK")
					else printf(ctrace(), "``REDBAD"))),
		res)]


[match?(self:eof_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	let i := get_index(p),
		n := fskip(p,1)
	in (if (n = 0)
			debug_match?(self.next, p, update_variable(avar))
		else
			(set_index(p, i),
			false))]

[match?(self:string_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	Core/buffer_basic_match?(p, self.arg) &
		(if (self.next % static_match) debug_match?(self.next, p, avar)
		else debug_match?(self.next, p, update_variable(avar)))]

[match?(self:char_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	let c := getc(p)
 	in (if ((not(self.good) | //<sb> if good is empty, only check the negative part (exclusive)
				exists(x in self.good |
					(case x
						(char_interval (x.arg1 <= c & c <= x.arg2),
						any c = x)))) &
				not(exists(x in self.bad |
						(case x
							(char_interval (x.arg1 <= c & c <= x.arg2),
							any c = x)))))
			(if (self.next % static_match) debug_match?(self.next, p, avar)
			else debug_match?(self.next, p, update_variable(avar)))
		else false)]

[match?(self:at_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	if Core/buffer_match?(eval(self.var), p)
		(if (self.next % static_match) debug_match?(self.next, p, avar)
		else debug_match?(self.next, p, update_variable(avar)))
	else false]
//	avar := update_variable(avar),
//	Core/buffer_match?(eval(self.var), p) & debug_match?(self.next, p, avar)]

[match?(self:fixlength_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	let n := eval(self.length)
	in (case n
			(integer self.value := fread(p, n),
			string self.value := fread(p, integer!(n)),
			any error("scanf: ~S should evaluate to an integer or a string instead of ~S",
							self.length, n)),
		if (length(self.value) = (case n (integer n, string integer!(n))))
			(if (self % fixlength_item_match)
				eval(self.var) 	add self.value
			else Language/write_value(self.var, self.value),
			if (self.next % static_match) debug_match?(self.next, p, avar)
			else debug_match?(self.next, p, update_variable(avar)))
		else false)]

[match?(self:assign_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	let i := get_index(p)
	in (if debug_match?(self.arg, p, avar)
			(self.value := substring(p.Core/pending, i + 1, get_index(p)),
			if (self % assign_item_match)
				eval(self.var) add self.value
			else
				Language/write_value(self.var, self.value),
			if (self.next % static_match) debug_match?(self.next, p, avar)
			else debug_match?(self.next, p, update_variable(avar)))
		else false)]

[match?(self:~S_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	let c := getc(p)
	in (c % {' ', '\t', '\n', '\r'} &
			(if (self.next % static_match) debug_match?(self.next, p, avar)
			else debug_match?(self.next, p, update_variable(avar))))]

[match?(self:~A_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	//avar := update_variable(avar),
	Core/buffer_match?(eval(self.arg), p) &
			(if (self.next % static_match) debug_match?(self.next, p, avar)
			else debug_match?(self.next, p, update_variable(avar)))]
//		debug_match?(self.next, p, avar)]


[match?(self:~I_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	avar := update_variable(avar),
	eval(self.arg),
	debug_match?(self.next, p, avar)]

[match?(self:~B_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	avar := update_variable(avar),
	eval(self.arg) & debug_match?(self.next, p, avar)]


[match?(self:reformat_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	let res := false,
		i := get_index(p)
	in (if debug_match?(self.arg, p, no_var)
			(res := true,
			avar.reformated? := true,
			for x in self.reformat
				eval(x))
		else (set_index(p, i), res := (avar != no_var)),
		res & debug_match?(self.next, p, avar))]


[match?(self:group_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	debug_match?(self.args[1], p, avar)]

[match?(self:alternative_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	let i := get_index(p),
		j := (if (avar != no_var) get_index(avar.value)
				else -1)
	in exists(x in self.args |
			(set_index(p, i),
			if (j != -1) set_index(avar.value, j),
			debug_match?(x, p, avar)))]

[match?(self:variable_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	if unknown?(value, self) self.value := blob!(),
	set_length(self.value, 0),
	self.previous := use_as_output(self.value), // become the current output
	let res := false,
		i0 := get_index(p),
		i := i0,
		waseof? := false
	in (while true // accumulation loop
			(self.reformated? := false,
			if (debug_match?(self.next, p, self) & // become the current variable
					not(self.reformated?))
				(res := true,
				break()),
			if not(self.reformated?)
				(set_index(p, i),
				let c := getc(p)
				in (if (verbose() > 2)
						printf(ctrace(), "~I``RED~S :/+ ~S\n",
								for i in (0 .. INDENT) printf("~S ", i),
								self,
								c),
					if (cout() != self.value |
							waseof? & not(self.next % eof_match) |
							length(self.value) >= self.max_length)
						(use_as_output(self.previous),
						set_index(p, i0),
						set_length(self.value, 0),
						res := false,
						break()),
					waseof? := eof?(p),
					i :+ 1,
					putc(c, self.value))) else i := get_index(p)),
		res)]

update_variable(avar:variable_match) : variable_match ->
	(if (avar != no_var)
		(if (avar % variable_item_match)
			eval(avar.var) add string!(avar.value)
		else
			Language/write_value(avar.var, string!(avar.value)),
		use_as_output(avar.previous),
		if (verbose() > 2)
			printf(ctrace(), "~I``GREENMATCH : ~S := ~S\n",
						for i in (0 .. INDENT) printf("~S ", i),
						avar,
						eval(avar.var)),
		no_var)
	else avar)


reenter_loop <: exception(var:variable_match)
REENTER_LOOP :: mClaire/new!(reenter_loop)

[match?(self:loop_match, p:Core/scanf_buffer, avar:variable_match) : boolean ->
	if self.reenter? (REENTER_LOOP.var := avar, close(REENTER_LOOP), true)
	else
		(self.reenter? := true,
		self.hit := 0,
		let m := eval(self.minoccur),
			M := (if self.maxismin? m
				else if known?(maxoccur, self) eval(self.maxoccur)
				else unknown)
		in (while (unknown?(M) | self.hit < M)
				let i := get_index(p)
				in (try
						(debug_match?(self.arg, p, avar),
						set_index(p, i),
						break())
					catch reenter_loop
						(if (get_index(p) = i) break(),
						self.hit :+ 1,
						avar := exception!().var)),
			self.reenter? := false,
			if (self.hit < m) false
			else debug_match?(self.next, p, avar)))]


// *******************************************************************
// *       Part 8: reseting loops                                    *
// *******************************************************************

loop_reset :: property(open = 3)

[loop_reset(self:scanf_match) : void -> none]

(interface(loop_reset))

[loop_reset(self:variable_match) : void ->
	if known?(value, self)
		set_length(self.value, 0),
	if (self % variable_item_match)
		Language/write_value(self.var, list<string>())
	else Language/write_value(self.var, "")]

[loop_reset(self:fixlength_match) : void ->
	if (self % fixlength_item_match)
		Language/write_value(self.var, list<string>())
	else Language/write_value(self.var, "")]

[loop_reset(self:assign_match) : void ->
	if (self % assign_item_match)
		Language/write_value(self.var, list<string>())
	else Language/write_value(self.var, ""),
	loop_reset(self.arg)]

[loop_reset(self:group_match) : void ->
	for x in self.args
		loop_reset(x)]

[loop_reset(self:reformat_match) : void ->
	loop_reset(self.arg)]

[loop_reset(self:alternative_match) : void ->
	for x in self.args
		loop_reset(x)]

[loop_reset(self:loop_match) : void ->
	self.hit := 0,
	self.reenter? := false,
	loop_reset(self.arg)]


// *******************************************************************
// *       Part 9: evaluation                                        *
// *******************************************************************

//<sb> reads a single scanf argument
nextscanf(r:meta_reader) : any
 -> (if (firstc(r) = #/))
		(error("Missing scanf argument"),
		nil)  // <yc:v0.01>
    else let x := nexts(r, none) in
           (if (firstc(r) = 10 & r.toplevel) skipc(r),         // v3.2.22
            if (firstc(r) = #/)) x
            else if (firstc(r) = #/,) (cnext(r), x)
            else Serror(171, "Read the character ~S inside a scanf sequence", list(char!(firstc(r))))))

//<sb> reader callback for reading a scanf instruction, 'scanf(' has
// been read already
[iClaire/scanf!(r:meta_reader) : Scanf ->
	let p := nextscanf(cnext(r)),
		frmt := nextscanf(r)
	in (if not(frmt % string) error("Wrongly typed scanf formatter ~S", frmt),
		let m := formater!(frmt), //<sb> read the regex
			bindings := list<any>(),
			sc := Scanf(args = list<any>(p, frmt), formater = m)
		in (init_scanf_variables(m, sc.vars), //<sb> would create implicit variables
			for v in sc.vars //<sb> bind vars to the lexical environment
				bindings add Reader/bind!(reader, v),
			read_scanf_arguments(m, sc, sc.vars),
			while (skipc(r) != #/))
				(//<sb> tell that the scanf result evaluates to the last argument
				sc.iClaire/uselastarg? := true, 
				sc.args add nextscanf(r)),
			next(r), //<sb> skip the ')'
			for b in bindings Reader/unbind!(reader, b),
			sc))]

//<sb> evaluator callback
[iClaire/scanfexpand(self:Scanf) : any ->
	let old := (let l := list<any>()
				in (push_reantrance_stack(self.iClaire/formater, l),
					l)),
		p := eval(self.args[1]),
		idnt := INDENT
	in (for v in self.vars
			Language/write_value(v, ""),
		let sp :=
			(case p //<sb> check that the input evaluates to a string or port
				(string Core/scanf_buffer!(blob!(p)),
				port Core/scanf_buffer!(p),
				any error("Wrongly typed scanf input ~S", self.args[1]))),
			i0 := get_index(sp),
			res := unknown
		in (INDENT := 0,
			loop_reset(self.iClaire/formater),
			try //<sb> does the match
				res := match?(self.iClaire/formater, sp, no_var)
			catch any
				(if not(exception!() % match_successful)
					(fclose(sp),
					close(exception!())),
				res := true),
			fclose(sp),
			INDENT := idnt,
			//[3] scanf result ~S // res,
			res := (if (res & self.iClaire/uselastarg?) eval(last(self.args))
					else res),
			pop_reantrance_stack(self.iClaire/formater, old),
			res))]

// *******************************************************************
// *       Part 10: variable initialization                          *
// *******************************************************************

push_reantrance_stack :: property(open = 3)
pop_reantrance_stack :: property(open = 3)


push_reantrance_stack(self:scanf_match, l:list[any]) : void -> none
pop_reantrance_stack(self:scanf_match, l:list[any]) : void -> none

(interface(push_reantrance_stack))
(interface(pop_reantrance_stack))

push_reantrance_stack(self:loop_match, l:list[any]) : void ->
	(l add self.hit,
	l add self.reenter?,
	push_reantrance_stack(self.arg, l))
pop_reantrance_stack(self:loop_match, l:list[any]) : void ->
	(self.hit := l[1],
	self.reenter? := l[2],
	l << 2,
	pop_reantrance_stack(self.arg, l))

push_reantrance_stack(self:alternative_match, l:list[any]) : void ->
	(for x in self.args push_reantrance_stack(x, l))
pop_reantrance_stack(self:alternative_match, l:list[any]) : void ->
	(for x in self.args pop_reantrance_stack(x, l))

push_reantrance_stack(self:group_match, l:list[any]) : void ->
	(for x in self.args push_reantrance_stack(x, l))
pop_reantrance_stack(self:group_match, l:list[any]) : void ->
	(for x in self.args pop_reantrance_stack(x, l))

push_reantrance_stack(self:reformat_match, l:list[any]) : void -> push_reantrance_stack(self.arg, l)
pop_reantrance_stack(self:reformat_match, l:list[any]) : void -> pop_reantrance_stack(self.arg, l)

push_reantrance_stack(self:variable_match, l:list[any]) : void ->
	(l add get(value, self),
	l add eval(self.var),
	l add get(previous, self))
pop_reantrance_stack(self:variable_match, l:list[any]) : void ->
	(put(value, self, l[1]),
	Language/write_value(self.var, l[2]),
	put(previous, self, l[3]),
	l << 3)

push_reantrance_stack(self:assign_match, l:list[any]) : void ->
	(l add eval(self.var),
	push_reantrance_stack(self.arg, l))
pop_reantrance_stack(self:assign_match, l:list[any]) : void ->
	(Language/write_value(self.var, l[1]),
	l << 1,
	pop_reantrance_stack(self.arg, l))



// *******************************************************************
// *       Part 10: variable initialization                          *
// *******************************************************************

[init_scanf_variables(self:scanf_match, lvars:list[Variable]) : void ->
	none]

[init_scanf_variables(self:variable_match, lvars:list[Variable]) : void ->
	when v := some(v in lvars|v.mClaire/pname.name = self.name)
	in self.var := v
	else (self.var := Variable(mClaire/pname = symbol!(self.name)),
		lvars add self.var)]

[init_scanf_variables(self:assign_match, lvars:list[Variable]) : void ->
	when v := some(v in lvars|v.mClaire/pname.name = self.name)
	in self.var := v
	else (self.var := Variable(mClaire/pname = symbol!(self.name)),
		lvars add self.var),
	init_scanf_variables(self.arg, lvars)]


[init_scanf_variables(self:fixlength_match, lvars:list[Variable]) : void ->
	when v := some(v in lvars|v.mClaire/pname.name = self.name)
	in self.var := v
	else (self.var := Variable(mClaire/pname = symbol!(self.name)),
		lvars add self.var)]


[init_scanf_variables(self:alternative_match, lvars:list[Variable]) : void ->
	for x in self.args
		init_scanf_variables(x, lvars)]

[init_scanf_variables(self:group_match, lvars:list[Variable]) : void ->
	for x in self.args
		init_scanf_variables(x, lvars)]

[init_scanf_variables(self:loop_match, lvars:list[Variable]) : void ->
	init_scanf_variables(self.arg, lvars)]

[init_scanf_variables(self:reformat_match, lvars:list[Variable]) : void ->
	init_scanf_variables(self.arg, lvars)]

// *******************************************************************
// *       Part 11: reading lazy arguments                           *
// *******************************************************************

[read_scanf_arguments(self:scanf_match, sc:Scanf, lvars:list[Variable]) : void ->
	none]

[read_scanf_arguments(self:at_match, sc:Scanf, lvars:list[Variable]) : void ->
 	let v := get_value(self.name)
	in (case v
			((Variable U global_variable)
				self.var := v,
			any error("scanf error, ~S is unbound", self)))]

[read_scanf_arguments(self:~_match, sc:Scanf, lvars:list[Variable]) : void ->
	if (self.arg = lazy_arg)
		(self.arg := nextscanf(reader),
		sc.args add self.arg)]

[read_scanf_arguments(self:assign_match, sc:Scanf, lvars:list[Variable]) : void ->
	read_scanf_arguments(self.arg, sc, lvars)]

[read_scanf_arguments(self:fixlength_match, sc:Scanf, lvars:list[Variable]) : void ->
	if (self.length = lazy_arg)
		(self.length := nextscanf(reader),
		sc.args add self.length)]

[read_scanf_arguments(self:alternative_match, sc:Scanf, lvars:list[Variable]) : void ->
	for x in self.args
		read_scanf_arguments(x, sc, lvars)]

[read_scanf_arguments(self:reformat_match, sc:Scanf, lvars:list[Variable]) : void ->
	read_scanf_arguments(self.arg, sc, lvars),
	for i in (1 .. length(self.reformat))
		let x := self.reformat[i]
		in (if (x % string)
				let v := get_value(x)
				in (case v
						((Variable U global_variable)
							let y := Call(princ, list(v))
							in (self.reformat[i] := y,
								sc.args add y),
						any error("scanf error, ~S is unbound", self)))
			else if (x = lazy_arg)
				let y := nextscanf(reader)
				in (self.reformat[i] := y,
					sc.args add y)
			else if (x = lazy_princ)
				let y := Call(princ, list(nextscanf(reader)))
				in (self.reformat[i] := y,
					sc.args add y)
			else if (x = lazy_print)
				let y := Call(print, list(nextscanf(reader)))
				in (self.reformat[i] := y,
					sc.args add y))]

[read_scanf_arguments(self:group_match, sc:Scanf, lvars:list[Variable]) : void ->
	for x in self.args
		read_scanf_arguments(x, sc, lvars)]

[read_scanf_arguments(self:loop_match, sc:Scanf, lvars:list[Variable]) : void ->
	if (self.minoccur = lazy_arg) self.minoccur := nextscanf(reader),
	if (get(maxoccur, self) = lazy_arg) self.maxoccur := nextscanf(reader),
	read_scanf_arguments(self.arg, sc, lvars)]
