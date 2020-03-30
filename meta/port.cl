
// *********************************************************************
// * CLAIRE                                            Sylvain Benilan *
// * port.cl                                                           *
// * Copyright (C) 2005 xl. All Rights Reserved                        *
// *********************************************************************


// In XL CLAIRE port are implemented in claire and are
// compatible with CLAIRE 3 (<ycs>) C++ implementation.
// In this implementation ports are organized into an extensible hierarchy
// of objects (instead of a primitive in <ycs>).
// Two sorts are defined, on the one hand device that are 'physical' port
// like a descriptor or a blob that may be handled through a chain of filter
// and on the other hand filters that are port that may analyze and/or
// transform and/or collect read and/or written data like a buffer, a line
// counter or even a MIME decoder or any kind embedded protocols.

// ***************************************************************************
// * part 1: low level char*                                                 *
// * part 1: model                                                           *
// * part 2: default interface                                               *
// * part 3: API                                                             *
// * part 4: null port                                                       *
// * part 4: blob                                                            *
// * part 5: buffer                                                          *
// * part 6: line_buffer                                                     *
// * part 7: byte_counter                                                    *
// * part 8: line_counter                                                    *
// * part 9: descriptor                                                      *
// * part 10: disk_file                                                      *
// * part 11: pipe                                                           *
// * part 12: socket                                                         *
// ***************************************************************************

// ***************************************************************************
// * part 1: low level char*                                                 *
// ***************************************************************************

//<sb> @doc @xl port
// read_port and write_port operate on a given buffer of a given size. these
// buffers are char* imported from C, this way we have an interface
// similar to read(2) and write(2)
claire/char* <: import()


//<sb> @doc @xl port
// translate the char* pointer self with an offset of n bytes
+(self:char*, n:integer) : char* -> externC("(self + n)", char*)

//<sb> Warning: no bound check on char*

//<sb> @doc @xl port
// get the char at position n in self (n is a 1 based index).\n
// \b Warning \/b : there is no bound check !
nth(self:char*, n:integer) : char -> char!(externC("((unsigned char)(self[n-1]))", integer))

//<sb> @doc @xl port
// sets the n\sup th\/sup char in self with c (n is a 1 based index).\n
// \b Warning \/b : there is no bound check !
nth=(self:char*, n:integer, c:char) : void -> externC("self[n-1] = (char)c->ascii")

//<sb> @doc @xl port
// make a new string of length len from a char*
string!(self:char*, len:integer) : string ->
	let s := make_string(len)
	in (externC("memcpy(s, self, len)"), s)

//<sb> @doc @xl port
// acquire the memory address of a string.
claire/char*!(self:string) : char* -> externC("self", char*)

//<sb> do not protect arguments in char* tools
(write(Core/status, + @ char*, ^2(SAFE_GC) + ^2(SAFE_RESULT)))
(write(Core/status, nth @ char*, ^2(SAFE_GC) + ^2(SAFE_RESULT)))
(write(Core/status, nth= @ char*, ^2(SAFE_GC)))
(write(Core/status, string! @ char*, ^2(SAFE_GC) + ^2(NEW_ALLOC)))


// ***************************************************************************
// * part 1: model                                                           *
// ***************************************************************************

//<sb> port inherit from freeable_object, this way we can
// catch an instance deallocation (for instance to close an
// open descriptor).

// note: the class port is defined in the kernel, some slots
// needs to be added by hand :
(#if compiler.loading?
	(add_slot(port, firstc, integer, integer!(' '), 3),
	add_slot(port, closed?, boolean, false, 4)))


	claire/device <: port
	claire/filter <: port

	//<sb> @doc @xl port
	// physical port like a descriptor or a blob that may be handled
	// through a chain of filter
	device <: port(filters:list[filter])
	
	//<sb> @doc @xl port
	// port that may analyze and/or transform and/or collect read
	// and/or written data like a buffer, a line counter or even a
	// MIME decoder or any kind embedded protocols.
	filter <: port(dev:device, claire/target:port, close_target?:boolean = false)

	(inverse(dev) := filters)

		claire/null_port <: device
		claire/blob <: device
		claire/descriptor <: device
			claire/disk_file <: descriptor
			claire/pipe <: descriptor
			claire/socket <: descriptor
				claire/listener <: socket
	
		claire/buffer <: filter
		claire/line_buffer <: filter
		claire/line_counter <: filter
		claire/byte_counter <: filter

get_top_most(self:port) : port ->
	(case self
		(device
			(if self.filters last(self.filters)
			else self),
		filter last(self.dev.filters),
		any self))

get_device(self:port) : device ->
	(case self
		(filter self.dev,
		device self,
		any error("~S is not a device", self) as device))

//<sb> @doc @xl port
// filter! should be used by filter constructors, it ensures
// the good shape of the inner relations (i.e. between the filter
// and its device)
claire/filter!(self:filter, p:port) : type[self] ->
	(if p.closed?
		error("Attempt to add filter ~S to ~S that is already closed"),
	let d := (case p (device p, filter p.dev)),
		fs := d.filters,
		p := (if fs last(fs) else d)
	in (self.dev := d,
		self.target := p,
		self))

//<sb> @doc @xl port
// tell that the filter should close its target when it is
// itself closed (cascading close)
claire/close_target!(self:filter) : type[self] ->
	(self.close_target? := true,
	self)



inner_print(self:device) : void -> princ(self)
inner_print(self:filter) : void ->
	(if unknown?(dev, self)
		printf("unconneted ~S", owner(self))
	else printf("~A(~I)", self, inner_print(self.target)))

self_print(self:filter) : void ->
	(if unknown?(dev, self)
		printf("<unconneted ~S>", owner(self))
	else printf("<~I>", inner_print(self)))


self_print(self:device) : void ->
	printf("<~A>", self)


princ(self:port) : void -> princ(owner(self).name.name)


// ***************************************************************************
// * part 2: default interface                                               *
// ***************************************************************************

// The port interface :
//	- eof_port? : check the end-of-file
//	- read_port : read n bytes
//	- unget_port : gives a chance for the port to unget data
//	- write_port : write n bytes
//	- flush_port : gives a chance for the port to write out any pending
//		datas (buffer)
//	- close_port : gives a chance for the port to clean internal data



//<sb> @doc @xl port
// interface to check the end-of-file condition on a given port :
// \code
// eof_port?(self:my_port) : boolean ->
// 	...
// \/code
claire/eof_port? :: property(open = 3, range = boolean)

//<sb> @doc @xl port
// interface to read a chunk of data :
// \code
// read_port(self:my_port, buf:data*, len:integer) : integer ->
// 	...
// \/code
// the returned value should be the amount of bytes that were
// actually read
claire/read_port :: property(open = 3, range = integer)

//<sb> @doc @xl port
// interface to unget a chunk of data :
// \code
// unget_port(self:my_port, buf:data*, len:integer) : void ->
// 	...
// \/code
claire/unget_port :: property(open = 3, range = void)

//<sb> @doc @xl port
// interface to write a chunk of data
// \code
// write_port(self:my_port, buf:data*, len:integer) : integer ->
// 	...
// \/code
// the returned value should be the amount of bytes that were
// actualy written
claire/write_port :: property(open = 3, range = integer)

//<sb> @doc @xl port
// interface to flush pending buffered data
// \code
// flush_port(self:my_port) : void ->
// 	...
// \/code
claire/flush_port :: property(open = 3, range = void)

//<sb> @doc @xl port
// interface to close the port :
// \code
// close_port(self:my_port) : void ->
// 	...
// \/code
claire/close_port :: property(open = 3, range = void)


write_port(self:port, buf:char*, len:integer) : integer ->
	let c := owner(self),
		r := (write_port @ c)
	in (if (r & r.domain[1] = c)
			//<sb> interpreted message
			apply(r as method, list(self, buf, len)) as integer
		else if (self % filter)
			//<sb> filter default : relay message
			write_port(self.target, buf, len)
		else
			//<sb> device default : error !
			(error("write_port @ ~S not implemented", owner(self)),
			0))

read_port(self:port, buf:char*, len:integer) : integer ->
	let c := owner(self),
		r := (read_port @ c)
	in (if (r & r.domain[1] = c)
			//<sb> interpreted message
			apply(r as method, list(self, buf, len)) as integer
		else if (self % filter)
			//<sb> filter default : relay message
			read_port(self.target, buf, len)
		else
			//<sb> device default : error !
			(error("read_port @ ~S not implemented", owner(self)),
			0))

unget_port(self:port, buf:char*, len:integer) : void ->
	let c := owner(self),
		r := (unget_port @ c)
	in (if (r & r.domain[1] = c)
			//<sb> interpreted message
			apply(r as method, list(self, buf, len)) as integer
		else if (self % filter)
			//<sb> filter default : relay message
			unget_port(self.target, buf, len)
		else
			//<sb> device default : error !
			(error("unget_port @ ~S not implemented", owner(self)),
			0))

eof_port?(self:port) : boolean ->
	let c := owner(self),
		r := (eof_port? @ c)
	in (if (r & r.domain[1] = c)
			//<sb> interpreted message
			apply(r as method, list(self))  as boolean
		else if (self % filter)
			//<sb> filter default : relay message
			eof_port?(self.target)
		else
			//<sb> device default : error !
			(error("eof_port? @ ~S not implemented", owner(self)),
			0))

flush_port(self:port) : void ->
	let c := owner(self),
		r := (flush_port @ c)
	in (if (r & r.domain[1] = c)
			//<sb> interpreted message
			apply(r as method, list(self))
		else if (self % filter)
			//<sb> filter default : relay message
			flush_port(self.target)
		//<sb> device default : nothing
		else none)

close_port(self:port) : void ->
	let c := owner(self),
		r := (close_port @ c)
	in (if (r & r.domain[1] = c)
			//<sb> interpreted message
			apply(r as method, list(self))
		else none)

//<sb> activate fast dispatch on port interface
// Note: interpreted messages won't be handled automatically since the
// interface for port uses fast dispatch. In default handlers we try to
// dispatch the message by hand. This is a limited support of dynamic
// dispatch, it will only work with interpreted code if it is based on
// default handlers (i.e. with domain port). The dynamic dispatch is safe
// on interpreted classes derived from device or filter whereas, for
// instance, an attempt to write on a port derived from descriptor will
// fail.

(interface(eof_port?))
(interface(read_port))
(interface(unget_port))
(interface(write_port))
(interface(close_port))
(interface(flush_port))



// ***************************************************************************
// * part 3: API                                                             *
// ***************************************************************************

//<sb> @doc @xl port
// check whether the end-of-file condition has been reached
claire/eof?(self:port) : boolean -> eof_port?(self)

//<sb> @doc @xl port
// read a string of n bytes on self
// the length of the returned string may be
// lower than n if an eof condition is reached
// on self
claire/fread(self:port, n:integer) : string ->
	let s := make_string(n)
	in (shrink(s, read_port(self, externC("s", char*), n)),
		s)

//<sb> @doc @xl port
// read inside an existing string, this overwrites
// the string content and may modify the string length
// if an eof condition is reached on self. the amount
// of queried bytes is the length of the input string
claire/fread(self:port, s:string) : integer ->
	let n := length(s),
		on := read_port(self, externC("s", char*), n)
	in (shrink(s, on),
		on)

//<sb> @doc @xl port
// read all data on self until eof
[claire/fread(self:port) : string ->
	case self
	  (blob
	    let b := self,
	        n := remain_to_read(self),
	        s := make_string(n)
	    in (externC("memcpy(s,b->data,n)"),
	        b.read_index := b.write_index,
	        s),
	  port
    	let b := blob!(4096)
    	in (freadwrite(self,b),
    	    let res := string!(b)
    	    in (fclose(b),
    	        res)),
    any "")]

//<sb> @doc @xl port
// read a single char on self
// reading an EOF char does not mean that
// the end-of-file is reached, one should use
// eof? @ port to check the eof condition
claire/getc(self:port) : char ->
	(externC("char c"),
	if (eof_port?(self) | read_port(self, externC("&c", char*), 1) = 0) EOF
	else externC("_char_(c)", char))


//<sb> @doc @xl port
// unget a string such the next data that can be read is s
claire/unget(self:port, s:string) : void ->
	unget_port(self, externC("s", char*), length(s))

//<sb> @doc @xl port
// unget a string such the next char that can be read is c
claire/unget(self:port, c:char) : void ->
	(externC("char ch = (char)c->ascii"),
	unget_port(self, externC("(&ch)", char*), 1))


//<sb> TODO: read a single UTF-8 sequence
/*claire/getc_utf8(self:port) : integer ->
	(externC("char c0"),
	if (eof?(self) | read_port(self, externC("&c0", char*), 1) = 0) integer!(EOF)
	else if externC("(c0 & 128 ? CTRUE : CFALSE)", boolean)
		(externC("char c8 = 0"),
		if (read_port(self, externC("&c8", char*), 1) = 0)
			error("Premature end-of-file on ~S while reading an UTF8 sequence", self),
		externC("(c << 8) | c8", integer))
	else externC("(unsigned char)c", integer))

claire/putc_utf8(self:integer, p:port) : void ->
	(externC("unsigned CL_INT c = (unsigned)self"),
	externC("unsigned char ch"),
	if externC("(c < 0x80 ? CTRUE : CFALSE)", boolean)
		write_port(p, externC("(ch = c, &ch)", char*), 1)
	else if externC("(c < 0x800 ? CTRUE : CFALSE)", boolean)
		(write_port(p, externC("(ch = 0xC0 | c>>6, &ch)", char*), 1),
		write_port(p, externC("(ch = 0x80 | c & 0x3F, &ch)", char*), 1))
	else if externC("(c < 0x10000 ? CTRUE : CFALSE)", boolean)
		(write_port(p, externC("(ch = 0xE0 | c>>12, &ch)", char*), 1),
		write_port(p, externC("(ch = 0x80 | c>>6 & 0x3F, &ch)", char*), 1),
		write_port(p, externC("(ch = 0x80 | c & 0x3F, &ch)", char*), 1))
	else if externC("(c < 0x200000 ? CTRUE : CFALSE)", boolean)
		(write_port(p, externC("(ch = 0xF0 | c>>18, &ch)", char*), 1),
		write_port(p, externC("(ch = 0x80 | c>>12 & 0x3F, &ch)", char*), 1),
		write_port(p, externC("(ch = 0x80 | c>>6 & 0x3F, &ch)", char*), 1),
		write_port(p, externC("(ch = 0x80 | c & 0x3F, &ch)", char*), 1)))
*/

//<sb> @doc port
// flush pending buffers in the filter chain such
// pending data are actually written on the device
claire/flush(self:port) : void ->
	let p := self
	in (while (p % filter)
			(flush_port(p),
			p := p.target), flush_port(p))

//<sb> @doc port
// for compatibility with <ycs> mainly used for stdin
claire/flush(self:port, n:integer) : void -> (self.firstc := n)

//<sb> @doc @xl port
// writes a raw string on the port p
claire/fwrite(self:string, p:port) : integer ->
	write_port(p, externC("self", char*), length(self))


//<sb> @doc port
// writes a single byte on p
claire/putc(self:char, p:port) : void ->
	(externC("char c = (char)self->ascii"),
	write_port(p, externC("&c",char*), 1))


//<sb> @doc @xl port
// read all data from src until eof and write it on trgt
// without performing any allocation. returns the amount of byte
// transfered.
claire/freadwrite(src:port, trgt:port) : integer ->
	(if (src = trgt) error("Attempt to freadwrite ~S on itself !", src),
	externC("char tmp[4096]"),
	let n := 0,
		buf := externC("tmp", char*)
	in (while not(eof_port?(src))
			let m := read_port(src, buf, 4096)
			in (n :+ m,
				write_port(trgt, buf, m)),
		n))

//<sb> @doc @xl port
// read up-to len bytes from src and write them on trgt
// without performing any allocation.
// returns the amount of bytes actually transferred (may be
// lower than len if an eof condition is reached on src)
claire/freadwrite(src:port, trgt:port, len:integer) : integer ->
	(if (src = trgt) error("Attempt to freadwrite ~S on itself !", src),
	externC("char tmp[4096]"),
	let n := 0,
		buf := externC("tmp", char*)
	in (while (not(eof_port?(src)) & len > 0)
			let toread := len min 4096,
				m := read_port(src, buf, toread)
			in (n :+ m,
				len :- m,
				write_port(trgt, buf, m)),
		n))

//<sb> @doc @xl port
// skip n bytes from self (dummy read) without performing
// any allocation and return the amount of bytes actually skipped
// (may be lower than len if an eof condition is reached)
claire/fskip(self:port, len:integer) : integer ->
	(externC("char tmp[256]"),
	let n := 0,
		buf := externC("tmp", char*)
	in (while (not(eof_port?(self)) & len > 0)
			let nread := len min 256,
				m := read_port(self, buf, nread)
			in (n :+ m,
				len :- m), n))
/*
//<sb> @doc @xl port
// close the specified device including the associated
// filter chain
claire/fclose(self:device) : void ->
	(//[1] fclose device ~S:~S // self, Core/Oid(self),
	if not(self.closed?)
		(//[1] not closed, filters ~S // self.filters,
		while self.filters
			let f := last(self.filters)
			in (fclose(f),
				if (self.filters & last(self.filters) = f)
					//[1] failed to close filter ~S // f
				),
		//[1] now flush ~S:~S // self,  Core/Oid(self),
		flush_port(self),
		self.closed? := true,
		close_port(self)),
	if (self = Clib_stdout)
		cout() := null!(),
	if (cout() = self)
		cout() := Clib_stdout,
	if (ctrace() = self)
		ctrace() := Clib_stdout)

//<sb> @doc @xl port
// close the top filter only, unless it has the
// close_target? flag on
claire/fclose(self:filter) : void ->
	(//[1] fclose filter ~S:~S // self, Core/Oid(self),
	when d := get(dev, self)
	in (//[1] filter have device ~S:~S // d, Core/Oid(d),
		if not(self.closed?)
			(if (self = last(d.filters))
				(flush_port(self),
				self.closed? := true,
				close_port(self),
				rmlast(d.filters),
				put(dev, self, unknown),
				if self.close_target?
					fclose(self.target))),
		if (cout() = self)
			cout() := Clib_stdout,
		if (ctrace() = self)
			ctrace() := Clib_stdout))
*/

claire/fclose(self:port) : void ->
	(case self
		(device
			(if not(self.closed?)
				(while self.filters
					let f := last(self.filters)
					in (fclose(f),
						if (self.filters & last(self.filters) = f)
							//[1] failed to close filter ~S // f
						),
				if not(self.closed?)
  				(flush_port(self),
  				self.closed? := true,
  				close_port(self))),
			if (self = Clib_stdout)
				cout() := null!(),
			if (cout() = self)
				cout() := Clib_stdout,
			if (ctrace() = self)
				ctrace() := Clib_stdout),
		filter
			(when d := get(dev, self)
			in (if not(self.closed?)
					(if (self = last(d.filters))
						(try flush_port(self)
						catch any
						  (//[1] failed to flush filter ~S - ignore // self
						    ),
						self.closed? := true,
						close_port(self),
						rmlast(d.filters),
						put(dev, self, unknown),
						if self.close_target?
							fclose(self.target))),
				if (cout() = self)
					cout() := Clib_stdout,
				if (ctrace() = self)
					ctrace() := Clib_stdout))))



claire/get_filter(self:port, c:class) : port ->
	let d := get_device(self),
		fs := d.filters,
		len := length(fs),
		p := self
	in (for i in (1 .. len)
			(if (fs[i] % c)
				(p := fs[i],
				break())), p)
	
//<sb> GC callback raised when the object is freed

prefree!(self:filter) : void ->
	(#if compiler.loading?
		(if not(self.closed?)
			when d := get(dev, self)
			in (while d.filters
  					let f := last(d.filters)
  					in (if (cout() = f)
  							cout() := Clib_stdout,
  						if (ctrace() = f)
  							ctrace() := Clib_stdout,
  						flush_port(f),
  						f.closed? := true,
  						close_port(f),
  						rmlast(d.filters),
  						put(dev, f, unknown)))))

free!(self:device) : void ->
	(#if compiler.loading?
		(if not(self.closed?)
			(if (cout() = self)
				cout() := Clib_stdout,
			if (ctrace() = self)
				ctrace() := Clib_stdout,
			flush_port(self),
			self.closed? := true,
			close_port(self))))

// ***************************************************************************
// * part 4: null port                                                       *
// ***************************************************************************


null_port <: device()
claire/null :: null_port()
claire/null!() : null_port -> null


//<sb> null port does nothing
read_port(self:null_port, buf:char*, len:integer) : integer -> 0
eof_port?(self:null_port) : boolean -> true
write_port(self:null_port, buf:char*, len:integer) : integer -> len
flush_port(self:null_port) : void -> none

//<sb> keep the singleton opened
close_port(self:null_port) : void -> (self.closed? := false)


// ***************************************************************************
// * part 4: blob                                                            *
// ***************************************************************************

// When a new blob is instantiated
// it is important to allocate the container chunk first (the container is
// the claire blob object) and only then the data chunk, as such we always
// have a valid container to hold the mallocated data.

//<sb> @doc @xl port
// blob is a port interface for strings, data are stored in a chunk of
// memory allocated outside claire memory.
blob <: device(
			data:char*,					//<sb> the internal data raw
			alloc_length:integer = 0,	//<sb> the size of the memory chunk
			read_index:integer = 0,		//<sb> index in data of the next byte to read
			write_index:integer = 0)	//<sb> index in data of the next byte to write

claire/clob <: blob()

//<sb> blobs have a pretty printing that shows the content
// of the blob around the reading index
princ(self:blob) : void ->
	(if (self.write_index = 0)
		printf("empty blob")
	else if (self.write_index < 40)
		printf("~S[~S:`BLACK~I``RED|`BLACK~I`BLACK]",
		  owner(self),
			self.write_index,
			(if (self.read_index > 0)
				externC("internal_print_string(self->data, self->read_index)")),
			(if (self.read_index < self.write_index)
				externC("internal_print_string(self->data + self->read_index, self->write_index - self->read_index)")))
	else if (self.read_index < 20)
		printf("~S[~S:`BLACK~I``RED|`BLACK~I`RED...`BLACK]",
		    owner(self),
				self.write_index,
				(if (self.read_index > 0)
					externC("internal_print_string(self->data, self->read_index)")),
				externC("internal_print_string(self->data + self->read_index, 20)"))
	else if (self.read_index + 20 >= self.write_index)
		printf("~S[~S:`RED...`BLACK~I``RED|`BLACK~I`BLACK]",
		    owner(self),
				self.write_index,
				(if (self.read_index > 0)
					externC("internal_print_string(self->data + self->read_index - 20, 20)")),
				externC("internal_print_string(self->data + self->read_index, self->write_index - self->read_index)"))
	else
		printf("~S[~S:`RED...`BLACK~I``RED|`BLACK~I`RED...`BLACK]",
		    owner(self),
				self.write_index,
				externC("internal_print_string(self->data + self->read_index - 20, 20)"),
				externC("internal_print_string(self->data + self->read_index, 20)")))


			

//<sb> ensure that the internal buffer is large enough to
// hold n bytes at the current write index
write_attempt(self:blob, n:integer) : void ->
	(if (remain_for_write(self) < n)
		let len_after := self.write_index + n + 1,
			new_length := 1024
		in (while (new_length < len_after)
				new_length :* 2,
			let new_data:char* := externC("((char*)realloc(self->data, new_length))", char*)
			in (if externC("(new_data == NULL ? CTRUE : CFALSE)", boolean)
					error("failed to allocate external memory for blob ~S", self),
				self.alloc_length := new_length - 1,
				self.data := new_data)))


unget_port(self:blob, buf:char*, len:integer) : void ->
	let room := self.read_index
	in (if (room >= len)
			self.read_index :- len
		else
			let grow := len - room,
				remain := claire/remain_to_read(self)
			in (write_attempt(self, grow),
				if (remain > 0)
					externC("memmove(self->data + self->read_index + grow, self->data + self->read_index, remain)"),
				self.write_index :+ grow,
				self.read_index := 0),
		externC("memcpy(self->data + self->read_index, buf, len)"))


//<sb> @doc @xl port
// allocate an empty blob
claire/blob!() : blob ->
	let b := blob(),
		buf := externC("((char*)malloc(8192))", char*)
	in (if externC("(buf == NULL ? CTRUE : CFALSE)", boolean)
			error("failed to allocate external memory in blob! @ void"),
		b.data := buf,
		b.alloc_length := 8191,
		b)

//<sb> @doc @xl port
// allocate a blob that is a copy of the given blob
claire/blob!(p:blob) : blob ->
	let b := blob(),
		buf := externC("((char*)malloc(p->alloc_length+1))", char*)
	in (if externC("(buf == NULL ? CTRUE : CFALSE)", boolean)
			error("failed to allocate external memory for blob!(~S)", p),
		externC("memcpy(buf, p->data, p->write_index)"),
		b.data := buf,
		b.firstc := p.firstc,
		b.read_index := p.read_index,
		b.write_index := p.write_index,
		b.alloc_length := p.alloc_length,
		b)
	

//<sb> @doc @xl port
// allocate a blob that is filled with all data that can
// be read on p
claire/blob!(p:port) : blob ->
	let b := blob!()
	in (freadwrite(p, b),
		b)

//<sb> @doc @xl port
// allocate a blob with the string self has the initial data
claire/blob!(self:string) : blob ->
	let b := blob(),
		len := length(self),
		alloclen := (if (len = 0) 1 else len),
		buf := externC("((char*)malloc(alloclen+1))", char*)
	in (if externC("(buf == NULL ? CTRUE : CFALSE)", boolean)
			error("failed to allocate external memory for blob!(~S)", self),
		if (len > 0)
		  externC("memcpy(buf, self, len)"),
		b.data := buf,
		b.write_index := len,
		b.alloc_length := alloclen,
		b)
		

//<sb> @doc @xl port
// allocate a blob that can receive at least n bytes
// (i.e. writing more than n bytes may cause further allocation)
claire/blob!(n:integer) : blob ->
	let b := blob(),
		buf := externC("((char*)malloc(n+1))", char*)
	in (if externC("(buf == NULL ? CTRUE : CFALSE)", boolean)
			error("failed to allocate external memory for blob!(~S)", n),
		b.data := buf,
		b.write_index := 0,
		b.alloc_length := n,
		b)

claire/clob!() : clob ->
  let b := blob!()
  in (externC("b->isa = Core._clob"),
      externC("b", clob))

claire/clob!(self:string) : clob ->
  let b := blob!(self)
  in (externC("b->isa = Core._clob"),
      externC("b", clob))

claire/clob!(self:port) : clob ->
  let b := blob!(self) as blob
  in (externC("b->isa = Core._clob"),
      externC("b", clob))

claire/clob!(n:integer) : clob ->
  let b := blob!(n)
  in (externC("b->isa = Core._clob"),
      externC("b", clob))

//<sb> @doc @xl port
// compatibility with <ycs>, one should use blob! instead.
claire/port! :: claire/blob!


//<sb> return the amount of bytes remaining for writing or reading
remain_for_write(self:blob) : integer -> (self.alloc_length - self.write_index)
claire/remain_to_read(self:blob) : integer -> (self.write_index - self.read_index)


eof_port?(self:blob) : boolean ->
	externC("(self->read_index == self->write_index ? CTRUE : CFALSE)", boolean)

read_port(self:blob, buf:char*, len:integer) : integer ->
	let avail := remain_to_read(self) //<sb> can't read more than available !
	in (if (len < avail) avail := len,
		externC("memcpy(buf, self->data + self->read_index, avail)"),
		self.read_index :+ avail,
		avail)

write_port(self:blob, buf:char*, len:integer) : integer ->
	(write_attempt(self, len),
	externC("memcpy(self->data + self->write_index, buf, len)"),
	self.write_index :+ len,
	len)

close_port(self:blob) : void ->
	externC("{if (self->data) {::free(self->data);self->data = NULL;}}")
	
//<sb> @doc @xl port
// string! converts a blob in a string
claire/string!(self:blob) : string ->
	let len := self.write_index,
		s := make_string(len)
	in (externC("memcpy(s, self->data, len)"),
		s)

//<sb> @doc @xl port
// buffer access on the blob
nth(self:blob, n:integer) : char ->
	(n :max 1,
	n :min self.alloc_length,
	if (n = 0) EOF
	else externC("_char_(self->data[n-1])", char))

//<sb> @doc @xl port
// buffer access on the blob
nth=(self:blob, n:integer, c:char) : void ->
	(n :max 1,
	n :min self.alloc_length,
	if (n = 0) error("nth=@blob: the blob ~S is empty", self),
	externC("self->data[n-1] = c->ascii"))

//<sb> @doc @xl port
// return the total amount of bytes contained in the blob,
// string! @ blob will return a string with that length
claire/length(self:blob) : integer -> self.write_index
	
//<sb> @doc @xl port
// sets the amount of bytes contained in the blob, when 0 is given
// a new chunk is reallocated for the internal data
claire/set_length(self:blob, n:integer) : void ->
	(if (n <= 0)
		(//<sb> when n is 0 we perform a free for sanity
		let new_data:char* := externC("((char*)realloc(self->data, 8192))", char*)
		in (if externC("(new_data == NULL ? CTRUE : CFALSE)", boolean)
				error("failed to allocate external memory in set_length(~S, ~S)", self, n),
			self.data := new_data,
			self.alloc_length := 8191,
			self.read_index := 0,
			self.write_index := 0))
	else let maxn := self.alloc_length
		in (if (n > maxn)
				write_attempt(self, n - maxn)
			else 
				(self.write_index :min n,
				self.read_index :min n)))

//<sb> @doc @xl port
// returns a substring of the internal data considered, i and j are
// 1 base indexed
claire/substring(self:blob, i:integer, j:integer) : string ->
	(i :max 1,
	j :max i - 1,
	i :min self.alloc_length,
	j :min self.alloc_length,
	let len := j - i + 1,
		s := make_string(len)
	in (externC("memcpy(s, self->data + i - 1, len)"),
		s))
		

//<sb> @doc @xl port
// returns the current reading index 
claire/get_index(self:blob) : integer -> self.read_index

//<sb> @doc @xl port
// sets the current reading index 
claire/set_index(self:blob, n:integer) : void ->
	let i := (self.write_index min n)
	in (self.read_index := (0 max i))


// ***************************************************************************
// * part 5: reverser                                                        *
// ***************************************************************************

reverser <: filter(left_to_read:integer = 0)

claire/reverser!(self:blob) : reverser ->
	(if (get_top_most(self) != self)
		error("Cannot create a reverser on ~S that is already filtered", self),
	filter!(reverser(left_to_read = self.write_index), self))

eof_port?(self:reverser) : boolean -> (self.left_to_read = 0)

read_port(self:reverser, buf:char*, len:integer) : integer ->
	let bl := (self.target as blob),
		d := bl.data,
		n := 0,
		left_after := (self.left_to_read - len)
	in (if (self.left_to_read > bl.write_index)
			error("dangerous read_port @ reverser since the blob has changed !"),
		left_after :max 0,
		while (self.left_to_read > left_after)
			(externC("*buf = d[self->left_to_read - 1];
						buf++"),
			n :+ 1,
			self.left_to_read :- 1), n)


// ***************************************************************************
// * part 5: buffer                                                          *
// ***************************************************************************

//<sb> @doc @xl port
// a buffer filter performs a single read/write call on its target
// for each data raw of a given size (buffer_length). It comes as
// replacement of the C FILE* buffering capability.
buffer <: filter(
			buffer_length:integer,
			pending_r:blob,
			pending_w:blob)

//<sb> @doc @xl port
// buffer! creates a buffer filter on the port self with an internal
// buffer bufsize bytes long.
claire/buffer!(self:port, bufsize:integer) : buffer ->
	filter!(buffer(buffer_length = bufsize), self)

claire/buffer!(self:buffer, p:port) : buffer ->
	let f := filter!(buffer(buffer_length = self.buffer_length,
							close_target? = self.close_target?,
							firstc = self.firstc), p)
	in (if known?(pending_r, self)
			f.pending_r := blob!(self.pending_r),
		if known?(pending_w, self)
			f.pending_w := blob!(self.pending_w),
		f)


princ(self:buffer) : void ->
	printf("buffer[~I~I~I]",
		(if known?(pending_r, self)
			printf("R<~A>", self.pending_r)),
		(if (known?(pending_r, self) & known?(pending_w, self))
			princ(" ")),
		(if known?(pending_w, self)
			printf("W<~A>", self.pending_w)))
		
	
//<sb> read


claire/reset_buffer(self:port) : void ->
	let p := get_filter(self, buffer)
	in (case p
			(buffer
				(if known?(pending_r, p)
					(p.pending_r.write_index := 0,
					p.pending_r.read_index := 0)),
			any error("~S is not connected to a buffer", self)))



//<sb> the buffer reads its target by chunks of buffer_length bytes
// Note wcl: in order to have a toplevel compatible with wcl
// we have to connect the input to a buffer (wcl reader uses unget),
// the length of such a buffer is 1 such it always reads on the terminal
// input a single char at a time
fill_read_buffer(self:buffer) : void ->
	(if unknown?(pending_r, self)
		self.pending_r := blob!(self.buffer_length),
	let pend := self.pending_r
	in (pend.read_index := 0,
		pend.write_index :=
			read_port(self.target, externC("pend->data", char*), self.buffer_length)))

eof_port?(self:buffer) : boolean ->
	((known?(pending_r, self) &
		remain_to_read(self.pending_r) = 0) &
			eof_port?(self.target))

read_port(self:buffer, buf:char*, len:integer) : integer ->
	(if unknown?(pending_r, self)
		self.pending_r := blob!(self.buffer_length),
	let pend := externC("self->pending_r", blob),
		disp := (pend.write_index - pend.read_index),
		n := 0
	in (while (len > 0)
			let m := disp min len
			in (if (m > 0)
					(externC("memcpy(buf, pend->data + pend->read_index, m)"),
					len :- m,
					n :+ m,
					pend.read_index :+ m,
					buf :+ m),
				disp := (pend.write_index - pend.read_index),
				if (disp = 0)
					(if eof_port?(externC("self->target", port)) break(),
					fill_read_buffer(self),
					disp := remain_to_read(pend))), n))

//<sb> this is our unget interface for stream. the given data
// is copied back in the buffer and the read index is moved
// such the next data to read is s
// Note: the message is not transmitted to the target, a buffer
// always accumulate ungotten data and then return
unget_port(self:buffer, buf:char*, len:integer) : void ->
	(if unknown?(pending_r, self)
		(self.pending_r := blob!(self.buffer_length),
		write_port(self.pending_r, buf, len))
	else unget_port(self.pending_r, buf, len))

//<sb> write

flush_port(self:buffer) : void ->
	(if known?(pending_w, self)
		let pend := self.pending_w
		in (if (pend.write_index > 0)
				write_port(self.target, externC("pend->data", char*), pend.write_index),
			pend.write_index := 0))


write_port(self:buffer, buf:char*, len:integer) : integer ->
	(if unknown?(pending_w, self)
		self.pending_w := blob!(self.buffer_length),
	let pend := externC("self->pending_w", blob),
		blen := self.buffer_length,
		disp := blen - pend.write_index,
		n := 0
	in (while (len > 0)
			let m := disp min len
			in (if (m > 0)
					(externC("memcpy(pend->data + pend->write_index, buf, m)"),
					len :- m,
					n :+ m,
					pend.write_index :+ m,
					buf :+ m),
				disp := blen - pend.write_index,
				if (disp = 0)
					(write_port(externC("self->target", port), externC("pend->data", char*), blen),
					pend.write_index := 0,
					disp := blen)), n))


close_port(self:buffer) : void ->
	(if known?(pending_r, self) fclose(self.pending_r),
	if known?(pending_w, self) fclose(self.pending_w))


// ***************************************************************************
// * part 6: line_buffer                                                     *
// ***************************************************************************


//<sb> @doc @xl port
// line_buffer is a write filter that collects written data
// until a new line character. each line is flushed with a single
// write on the target port. It is mainly used for terminal output
// such to prevent line overlap when multiple process share the same
// terminal output or when a trace file is shared by multiple process.
line_buffer <: filter(pending:blob) //<sb> a pending line


//<sb> @doc @xl port
// line_buffer! creates a new line_buffer filter on the port self.
claire/line_buffer!(self:port) : line_buffer ->
	let lb := filter!(line_buffer(), self)
	in (lb.pending := blob!(),
		lb)

flush_port(self:line_buffer) : void ->
	let pend := self.pending,
		len := remain_to_read(pend)
	in (if (len > 0)
			(write_port(self.target, externC("pend->data", char*), len),
			pend.read_index := 0,
			pend.write_index := 0))

close_port(self:line_buffer) : void -> fclose(self.pending)


write_port(self:line_buffer, buf:char*, len:integer) : integer ->
	let pend := self.pending,
		nl := false,
		n := 0
	in (while (n < len)
			let n0 := n
			in (externC("while (1) {if (buf[n] == '\\n') nl = CTRUE;
									if (n + 1 == len) break;
									n++;}"),
				write_port(pend, buf + n0, n - n0 + 1),
				if nl
					(flush_port(self),
					nl := false),
				n :+ 1),
		len)


// ***************************************************************************
// * part 7: byte_counter                                                    *
// ***************************************************************************

//<sb> @doc @xl port
// byte_counter is a pure filter that count the number of bytes
// transfered in both directions
byte_counter <: filter(
					claire/written_bytes:integer = 0,
					claire/read_bytes:integer = 0)

claire/byte_counter!(self:port) : byte_counter -> filter!(byte_counter(), self)

claire/byte_counter!(self:byte_counter, p:port) : byte_counter ->
	filter!(byte_counter(close_target? = self.close_target?,
						firstc = self.firstc,
						written_bytes = self.written_bytes,
						read_bytes = self.read_bytes), p)


write_port(self:byte_counter, buf:char*, len:integer) : integer ->
	let n := write_port(self.target, buf, len)
	in (self.written_bytes :+ n,
		n)

read_port(self:byte_counter, buf:char*, len:integer) : integer ->
	let n := read_port(self.target, buf, len)
	in (self.read_bytes :+ n,
		n)

eof_port?(self:byte_counter) : boolean -> eof_port?(self.target)

// ***************************************************************************
// * part 8: line_counter                                                    *
// ***************************************************************************

//<sb> @doc @xl port
// line_counter is a pure filter that count the number of lines
// transfered in both directions
line_counter <: filter(
					claire/written_lines:integer = 0,
					claire/line_offset:integer = 0,
					claire/prev_line_offset:integer = 0,
					claire/read_lines:integer = 0)

[princ(self:line_counter) : void ->
  if (self.written_lines > 0) printf("wrote ~S line(s)", self.written_lines),
  if (self.read_lines > 0) printf("read ~S line(s)", self.read_lines)]

claire/line_counter!(self:port) : line_counter ->
	filter!(line_counter(), self)

claire/line_counter!(self:line_counter, p:port) : line_counter ->
	filter!(line_counter(close_target? = self.close_target?,
						firstc = self.firstc,
						written_lines = self.written_lines,
						read_lines = self.read_lines), p)

write_port(self:line_counter, buf:char*, len:integer) : integer ->
	let n := write_port(externC("self->target",port), buf, len),
		slashn := 0,
		i := 0
	in (externC("while (i < n) {if (buf[i++] == '\\n') slashn++;}"),
		self.written_lines :+ slashn,
		n)

read_port(self:line_counter, buf:char*, len:integer) : integer ->
	let n := read_port(externC("self->target",port), buf, len),
		slashn := 0,
		i := 0
	in (externC("while (i < n) {if (buf[i++] == '\\n') slashn++;}"),
		if (slashn = 0)
			self.line_offset :+ len
		else let o := 0
			in (self.prev_line_offset := self.line_offset,
				externC("len--; while (len) {if (buf[len] == '\\n') break; len--; o++;}"),
				self.line_offset := o),
		self.read_lines :+ slashn,
		n)


unget_port(self:line_counter, buf:char*, len:integer) : void ->
	let i := 0,
		slashn := 0
	in (externC("while (i < len) {if (buf[i++] == '\\n') slashn++;}"),
		if (slashn = 0)
			self.line_offset :- len
		else self.line_offset := self.prev_line_offset,	
		self.read_lines :- slashn,
		unget_port(self.target, buf, len))

eof_port?(self:line_counter) : boolean -> eof_port?(self.target)


// ***************************************************************************
// * part 9: descriptor                                                      *
// ***************************************************************************

//<sb> @doc @xl port
// UNIX file descriptor wrapping. we do not use C stream capabilities
// (FILE*) but the descriptor itself, which make the API relying on system
// calls read(2) and write(2), stream interface is provided by filters (buffer)
descriptor <: device(fd:integer = -1, //<sb> invalid descriptor by default
						eof_reached?:boolean = false)

//<sb> wan't write error on closed descriptors
(signal(SIGPIPE, SIG_IGN))

princ(self:descriptor) : void ->
	printf("~S(~S)", owner(self), self.fd)

close_port(self:descriptor) : void ->
	(#if compiler.loading?
		(if (self = Clib_stdout)
			externC("if (LOGO) ::write(1, \"bye...\\n\", 7)"),
		externC("if (self->fd != -1) ::close(self->fd)")))

eof_port?(self:descriptor) : boolean -> self.eof_reached?

read_port(self:descriptor, buf:char*, len:integer) : integer ->
	let r := 0
	in (while (r < len)
			let n := externC("::read(self->fd, buf + r, len - r)", integer)
			in (if (n = 0)
					(self.eof_reached? := true,
					break())
				else if (n = -1 & externC("(errno != EINTR ? CTRUE : CFALSE)", boolean))
					externC("Cerrorno(97, _string_(\"read\"), _oid_(self))")
				else r :+ n),
		r)

[write_port(self:descriptor, buf:char*, len:integer) : integer ->
  if self.closed? len
  else
  	let r := 0, retry := 0
  	in (while (r < len)
  			let n := externC("::write(self->fd, buf + r, len - r)", integer)
  			in (if (n = -1 & externC("(errno != EINTR ? CTRUE : CFALSE)", boolean))
  					  externC("Cerrorno(97, _string_(\"write\"), _oid_(self))")
  				else r :+ n),
  		r)]


//<sb> check whether a descriptor is connected to a terminal device
terminal?(p:port) : boolean ->
	(p := get_device(p),
	case p
		(descriptor
			let self := p
			in (#if compiler.loading?
				externC("
					struct stat sb;
					if(fstat(self->fd, &sb) != -1)
						return ((sb.st_mode) & S_IFMT) != S_IFCHR ? CFALSE : CTRUE;
				"), false), any false))


//<sb> duplicate a descriptor to be used in place of another
// Note : the new descriptor will be set to the lowest available
// descriptor (small int) for the current process.
duplicate(anfd:descriptor) : descriptor ->
	let desc := 0
	in (if anfd.closed?
			error("Attemp to duplicate descriptor ~S that is already closed.", anfd),
		//<sb> closes the given descriptor, it will be removed
		// from the process descriptor table leaving an empty slot
		externC("desc = dup(anfd->fd)"),
		if (desc = -1)
			externC("Cerrorno(97, _string_(\"duplicate\"), _oid_(anfd))"),
		descriptor(fd = desc))


//<sb> here we initialize Clib standard ports by hand assuming that
// the underlying lib defines 0,1,2 respectively standard in,out,err
// program descriptor and already opened.
Clib_stdin :: mClaire/new!(descriptor) //<sb> new! avoid a call to close
Clib_stdout :: mClaire/new!(descriptor)
Clib_stderr :: mClaire/new!(descriptor)

(externC("
	#ifdef CLPC
	_setmode(0, _O_BINARY);
	_setmode(1, _O_BINARY);
	_setmode(2, _O_BINARY);
	#endif
"))


(Clib_stdin.fd := 0,
Clib_stdin.closed? := false,
put(filters,Clib_stdin,list<filter>()))

(Clib_stdout.fd := 1,
Clib_stdout.closed? := false,
put(filters,Clib_stdout,list<filter>()))

(Clib_stderr.fd := 2,
Clib_stderr.closed? := false,
put(filters,Clib_stderr,list<filter>()))

//<sb> here we catch whether a standard port is redirected and update
// our knowledge about Clib standard ports accordingly.
// e.g. closing stdout and dup(2)
close(self:descriptor) : descriptor ->
	(case self
	  ((disk_file U pipe)
    	externC("
    		#ifdef CLPC
    			_setmode(self->fd, _O_BINARY);
    		#endif
    	")),
	case self.fd
		({0} get_value(Core,"Clib_stdin").value := self,
		{1} get_value(Core,"Clib_stdout").value := self,
		{2} get_value(Core,"Clib_stderr").value := self),
	self)

//<sb> here we initialize standard ports and system ports.
// note 1: if something is wrong until there during the meta load
// the behavior is undefined, even error printing cannot be achieved safely
// note 2 : for standard out (intended for write) we check whether
// the actual device is a terminal in which case a line buffer filter is added
// note 3 : stderr is always unbuffered

//<sb> @doc @xl port
// the standard input port
claire/stdin:port := Clib_stdin
//<sb> @doc @xl port
// the standard output port
claire/stdout:port := (#if compiler.loading?
							(if terminal?(Clib_stdout) line_buffer!(Clib_stdout)
							else Clib_stdout) else Clib_stdout)
//<sb> @doc @xl port
// the standard error output port
claire/stderr:port := Clib_stderr

(#if compiler.loading?
	(cout() := stdout,
	ctrace() := stdout))

(#if compiler.loading?
	(put(range,cpretty @ pretty_printer,blob),
	pretty.cpretty := port!()))

//<sb> add color support
// release() should produce a version number
(system.version := Id(RELEASE),
//<sb> add color support
#if compiler.loading? externC("if(LOGO) {"), 
printf("-- CLAIRE run-time library v3.~A [os:~A, C++:~A] --\n",
        Id(RELEASE),Id(compiler.env), Id(compiler.external)),
#if compiler.loading? externC("}"))



//<sb> @xl @doc port
// select?() waits for selected descriptors for a write or read
// condition to occur. This method blocks until a condition occur
// and will always return true as soon as a condition is satisfied.
// selected descriptors are the one for which read! or write! has been
// called first. In order to test whether a condition was satisfied on a
// selected descriptor one should use readable? or writeable?.
claire/select?() : boolean ->
	(externC("
		int rs = fdMaxfd == -1 ? 0 : select(fdMaxfd+1,&readset,&writeset,0,0);
		fdMaxfd = -1"),
	externC("(rs<=0 ? CFALSE : CTRUE)", boolean))


//<sb> @xl @doc port
// select?(ms) is the non-blocking version of select?. It returns true whenever
// a read or write condition is satisfied on a selected descriptor before a timeout
// of ms milliseconds could occur. If the timeout is reached before a condition
// could occur then select?(ms) returns false.\br
// When true is returned a read (resp. write) operation is guaranteed to succeed on
// a descriptor for which readable? (resp. writable?) returns true. If the descriptor
// is a listener socket and readable? returns true then accept is guaranteed to succeed.
// \code
// get_one_char(c:socket) : string ->
// 	(read!(c),
// 	if (select?(10) & readable?(c))
// 		fread(c, 1) // always succeed
// 	else "")
// \/code
select?(ms:integer) : boolean ->
	(externC("
		timeval timeout;
		timeout.tv_sec = ms / 1000;
		timeout.tv_usec = 1000 * (ms % 1000);
		int rs = fdMaxfd == -1 ? 0 : select(fdMaxfd+1,&readset,&writeset,0,&timeout);
		fdMaxfd = -1"),
	externC("(rs<=0 ? CFALSE : CTRUE)", boolean))

get_descriptor(self:port) : descriptor ->
	let p := get_device(self)
	in (if not(p % descriptor)
			error("~S is not a descriptor", self),
		p as descriptor)


//<sb> @xl @doc port
// readable?(self) returns true when self has been selected (see select?)
// and that a read operation is guaranteed to succeed.
claire/readable?(self:port) : boolean ->
	let p := get_descriptor(self)
	in externC("(FD_ISSET(p->fd, &readset) ? CTRUE : CFALSE)", boolean)

claire/readable?(p:descriptor) : boolean ->
	externC("(FD_ISSET(p->fd, &readset) ? CTRUE : CFALSE)", boolean)

//<sb> @xl @doc port
// writable?(self) returns true when self has been selected (see select?)
// and that a write operation is guaranteed to succeed.
claire/writable?(self:port) : boolean ->
	let p := get_descriptor(self)
	in externC("(FD_ISSET(p->fd, &writeset) ? CTRUE : CFALSE)", boolean)

claire/writable?(p:descriptor) : boolean ->
	externC("(FD_ISSET(p->fd, &writeset) ? CTRUE : CFALSE)", boolean)

//<sb> @xl @doc port
// read!(self) put the descriptor self in the selection set used for
// the select? operation
claire/read!(self:port) : void ->
	let p := get_descriptor(self)
	in externC("
		if(fdMaxfd == -1) {FD_ZERO(&readset); FD_ZERO(&writeset);}
		if(p->fd > fdMaxfd) fdMaxfd = p->fd;
		FD_SET(p->fd, &readset);")

claire/read!(p:descriptor) : void ->
	externC("
		if(fdMaxfd == -1) {FD_ZERO(&readset); FD_ZERO(&writeset);}
		if(p->fd > fdMaxfd) fdMaxfd = p->fd;
		FD_SET(p->fd, &readset);")

//<sb> @xl @doc port
// write!(self) put the descriptor self in the selection set used for
// the select? operation
claire/write!(self:port) : void ->
	let p := get_descriptor(self)
	in externC("
		if(fdMaxfd == -1) {FD_ZERO(&readset); FD_ZERO(&writeset);}
		if(p->fd > fdMaxfd) fdMaxfd = p->fd;
		FD_SET(p->fd, &writeset);")

claire/write!(p:descriptor) : void ->
	externC("
		if(fdMaxfd == -1) {FD_ZERO(&readset); FD_ZERO(&writeset);}
		if(p->fd > fdMaxfd) fdMaxfd = p->fd;
		FD_SET(p->fd, &writeset);")


// claire/readwrite!(self:port) : void -> (read!(self), write!(self))


// ***************************************************************************
// * part 10: disk_file                                                      *
// ***************************************************************************


//<sb> @doc @xl port
// disk_file is the interface for file located on the hard drive
disk_file <: descriptor(file_path:string,
						locked?:boolean = false,
						mode:integer)

princ(self:disk_file) : void ->
	printf("~A(~S)",
		let l := explode(self.file_path, *fs*)
		in (if l last(l) else self.file_path),
		self.fd)

OPEN_MODE :: {"r","w","a","rw","wr", "rb", "wb", "ab"}

//<sb> opening a descriptor relies on open(2)
disk_file!(self:string, mod:OPEN_MODE) : disk_file ->
	let desc := (case mod
  			({"r", "rb"} externC("open(self, O_RDONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)", integer),
  			{"rw","wr"} externC("open(self, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)", integer),
  			{"w", "wb"} externC("open(self, O_WRONLY|O_APPEND|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)", integer),
			any externC("open(self, O_WRONLY|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)", integer)))
	in (if (desc = -1)
			externC("Cerrorno(36, _string_(self), 0)"),
		disk_file(file_path = self,
		                   fd = desc,
		                   file_path = realpath(self),
				               mode = (case mod ({"r","rb"} 1, {"w", "wb", "a", "ab"} 0, any 2))))


//<sb> @doc @xl port
// reopen a file for read, the current offset
// of the reopened file is moved at the same place
// if a buffer is present on the filter chain then
// it contents and index are restored
claire/reopen(self:port) : port ->
	let s := get_disk_file(self),
		pos := externC("(CL_INT)lseek(s->fd, (off_t)0, SEEK_CUR)", integer),
		n := disk_file!(s.file_path, "r"),
		t:port := n
	in (n.firstc := s.firstc,
		externC("lseek(n->fd, (off_t)pos, SEEK_SET)"),
		for f in s.filters
			(case f
				(buffer t := buffer!(f, t),
				line_counter t := line_counter!(f, t),
				byte_counter t := byte_counter!(f, t))),
		t)

claire/filepos(self:disk_file) : integer ->
	externC("(CL_INT)lseek(self->fd, (off_t)0, SEEK_CUR)", integer)

claire/setfilepos(self:disk_file, pos:integer) : void ->
	(if (externC("(CL_INT)lseek(self->fd, (off_t)pos, SEEK_SET)", integer) = -1)
		error("lseek(~S, ~S, SEEK_SET) failed", self, pos))

claire/setfileend(self:disk_file) : void ->
	(if (externC("(CL_INT)lseek(self->fd, (off_t)0, SEEK_END)", integer) = -1)
		error("lseek(~S, SEEK_END) failed", self))

//<sb> @doc @xl port
// open a file on disk. the returned port is buffered.
// This is a lib C like fopen API (see man for details).
// note: unlike in C lib there is no support for the 'b'
// mode (binary) i.e. always open in binary mode. For
// instance here is a simple file copy method :
// \code
// file_copy(src:string, cpy:string) : void ->
// 	let fsrc := fopen(src, "r"),
// 		fcpy := fopen(cpy,"w")
// 	in (freadwrite(fsrc, fcpy),
// 		fclose(fsrc),
// 		fclose(fcpy))
// \/code
// Notice this method does not properly set the mode of the copied
// file as done by fcopy.
claire/fopen(self:string, mode:OPEN_MODE) : buffer ->
	let f := disk_file!(self, mode)
	in close_target!(buffer!(f, 8192))


get_disk_file(self:port) : disk_file ->
	let p := get_device(self)
	in (if not(p % disk_file)
			error("~S is not a disk file", self),
		p as disk_file)

claire/flock(self:port) : void ->
	let f := get_disk_file(self)
	in (if not(f.locked?)
		(externC("
			int rc = -1;
			#ifdef CLPC
				long p = _tell(f->fd);
				_lseek(f->fd, 0, SEEK_SET);
				while(rc < 0) {
					rc = _locking(f->fd, _LK_LOCK, 1);
				}
				_lseek(f->fd, p, SEEK_SET);
				p = _tell(f->fd);
			#else 
				#ifdef HAVE_FCNTL
					struct flock lock_it;
					lock_it.l_whence = SEEK_SET;
					lock_it.l_start = 0;
					lock_it.l_len = 0;
					lock_it.l_type = (f->mode == 1 ? F_RDLCK :
										(f->mode == 2 ? (F_WRLCK|F_RDLCK) :
											F_WRLCK));
					lock_it.l_pid = 0;
					while ( ((rc = fcntl(f->fd, F_SETLKW, &lock_it)) < 0) &&
								(errno == EINTR) ) {
						continue;
					}
				#endif
			#endif
			if (rc < 0)
				Cerrorno(94,_oid_(f),0);"),
		f.locked? := true))

funlock(self:port) : void ->
	let f := get_disk_file(self)
	in (if f.locked?
		(externC("
			int rc = 0;
			#ifdef CLPC
				long p = _tell(f->fd);
				_lseek(f->fd, 0, SEEK_SET);
				rc = _locking(f->fd, _LK_UNLCK, 1);
				_lseek(f->fd, p, SEEK_SET);
				p = _tell(f->fd);
			#else 
				#ifdef HAVE_FCNTL
					struct flock unlock_it;
					unlock_it.l_whence = SEEK_SET;
					unlock_it.l_start  = 0;
					unlock_it.l_len    = 0;
					unlock_it.l_type   = F_UNLCK;
					unlock_it.l_pid    = 0;
					rc = fcntl(f->fd, F_SETLKW, &unlock_it);
				#endif
			#endif
			if (rc < 0)
				Cerrorno(95,_oid_(self),0);"),
		f.locked? := false))

islocked?(self:port) : boolean ->
	let l := false,
		f := get_disk_file(self)
	in (externC("
			int rc = 0;
			#ifdef CLPC
				long p = _tell(f->fd);
				_lseek(f->fd, 0, SEEK_SET);
				rc = _locking(f->fd, _LK_NBLCK, 1);
				if (rc == 0) {
					_lseek(f->fd, 0, SEEK_SET);
					_locking(f->fd, _LK_UNLCK, 1);
					_lseek(f->fd, p, SEEK_SET);
					p = _tell(f->fd);
					l = CFALSE;
				} else if (rc > 0) {
					lseek(f->fd, p, SEEK_SET);
					p = _tell(f->fd);
					l = CTRUE;
				}
			#else 
				#ifdef HAVE_FCNTL
					struct flock lock_it;
					lock_it.l_whence = SEEK_SET;
					lock_it.l_start = 0;
					lock_it.l_len = 0;
					lock_it.l_type = f->mode == 1 ? F_RDLCK : F_WRLCK;
					lock_it.l_pid = 0;
					rc = fcntl(f->fd, F_GETLK, &lock_it);
					l = (lock_it.l_type != F_UNLCK) ? CTRUE : CFALSE;
				#endif
			#endif
			if (rc < 0)
				Cerrorno(94,_oid_(self),0);"),
		l)


// ***************************************************************************
// * part 11: pipe                                                           *
// ***************************************************************************

//<sb> @doc @xl port
// interface for UNIX pipes
pipe <: descriptor()

//<sb> @doc @xl port
// create a pair of unidirectional pipe connected to each other.
// The first one is intended for read and the second one for write.
// note: some system may return bi-directional pipes...
pipe!() : tuple(pipe, pipe) ->
	(externC("int fds[2]"),
	if (externC("::pipe(fds)", integer) = -1)
		externC("Cerrorno(98, 0, 0)"),
	tuple(pipe(fd = externC("*fds")), pipe(fd = externC("*(fds+1)"))))

princ(self:pipe) : void -> printf("pipe(~S)", self.fd)

// ***************************************************************************
// * part 12: socket                                                         *
// ***************************************************************************


//<sb> @doc @xl port
// the interface for UNIX stream oriented sockets, sockets are two
// way communication ports connected to a remote client.
socket <: descriptor(address:string = "localhost", tcpport:integer = -1)

//<sb> @doc @xl port
// the interface for listening sockets. such socket are
// used with accept to handle new connections.
listener <: socket()

princ(self:socket) : void ->
	printf("~A:~S(~S)",
			self.address, self.tcpport, 
			self.fd)

close_port(self:socket) : void ->
	(externC("
	#ifdef CLPC
		closesocket(self->fd);
	#else
		::close(self->fd)
	#endif
	"))

//<sb> @doc @xl port
// unlink the UNIX domain socket file associated with the given
// listener socket
unlink(self:listener) : void ->
	unlink(self.address)
	

//<sb> @doc @xl port
// returns the name of the host running CLAIRE
claire/gethostname() : string ->
	(externC("char tmp[500]"),
	if externC("(gethostname(tmp, 500) == 0 ? CTRUE : CFALSE)", boolean)
		copy(externC("tmp", string))
	else "unknown host name")

//<sb> @doc @xl port
// creates a connected socket at the address "addr:p", addr
// may be a numeric IP or a server name and p is the TCP port on
// which the connection should be made. For instance we could
// implement a simple HTTP GET :
// \code
// httpget(addr:string, f:string) : string ->
// 	let c := client!(addr, 80)
// 	in (printf(c, "GET /~A HTTP/1.0\r\n\r\n", f),
// 		let response := fread(c)
// 		in (fclose(c), response))
// \/code
[claire/client!(addr:string, p:integer) : socket ->
  if (length(addr) = "") addr := "127.0.0.1",
  socket(address = addr, tcpport = p, fd = connect(addr, p))]

//<sb> @doc @xl port
// creates a UNIX domain connected socket on the UNIX domain
// server at file addr
[claire/client!(addr:string) : socket ->
  let sad := "",
      spt := "",
      pt := -1
  in (if match_wildcard?(addr, "*:*")
        ((sad, spt) := explode_wildcard(addr, "*:*"),
        if digit?(spt) pt := integer!(spt))
      else if digit?(addr)
        pt := integer!(addr)
      else sad := addr,
      if (pt = -1 & length(spt) > 0)
        externC("{
            struct servent *p;
            p = getservbyname(spt, \"tcp\");
            if (p) pt = ntohs(p->s_port);
            }"),
      if (sad = "") sad := "127.0.0.1",
	    socket(address = sad, tcpport = pt, fd = connect(sad, pt)))]

connect(addr:string, p:integer) : integer ->
	(externC("
		int sock;
		int unix_domain = 0;
		#ifdef CLPC
			struct sockaddr_in inAddr;
		#else
			struct sockaddr_in inAddr;
			struct sockaddr_un unAddr;
			unix_domain = (strlen(addr) > 0 && addr[0] == '/');
		#endif
		if((sock = socket(unix_domain ? AF_UNIX : AF_INET, SOCK_STREAM, 0)) < 0)
			Cerrorno(74,_string_(\"connect @ string\"),0);
		if (unix_domain) {
			#ifndef CLPC
			strcpy(unAddr.sun_path, addr);
			#endif
		} else if((addr[0] >= '0' && addr[0] <= '9') || *addr == 0) {
			if(*addr == 0) inAddr.sin_addr.s_addr = inet_addr(\"127.0.0.1\");
			else inAddr.sin_addr.s_addr = inet_addr(addr);
		} else {
			struct hostent *servent;
			if((servent = gethostbyname(addr)) == 0) {
				#ifdef CLPC
					closesocket(sock);
				#else
					::close(sock);
				#endif
				Cerrorno(74,_string_(\"connect @ string\"),0);
			}
			memcpy(&inAddr.sin_addr, servent->h_addr, servent->h_length);
		}
		if (unix_domain) {
			#ifndef CLPC
			unAddr.sun_family = AF_UNIX;
			#endif
		} else {
			inAddr.sin_family = AF_INET;
			inAddr.sin_port = htons(p);
		}
		#ifdef CLPC
		if((connect(sock, (sockaddr*)&inAddr, sizeof(inAddr))) != 0) {
		#else
		if( (unix_domain && connect(sock, (sockaddr*)&unAddr, sizeof(unAddr)) != 0) ||
			(unix_domain == 0 && connect(sock, (sockaddr*)&inAddr, sizeof(inAddr))) != 0) {
		#endif
			#ifdef CLPC
				closesocket(sock);
			#else
				::close(sock);
			#endif
			Cerrorno(74,_string_(\"connect @ string\"),0);
		}"),
		externC("sock", integer))


//<sb> @doc @xl port
// creates a UNIX domain listener socket. addr is the \b absolute\/b path (i.e. must start with '/')
// to a file that will be used by the subsystem as listener descriptor.
claire/server!(addr:string) : listener ->
  (if digit?(addr) server!("", integer!(addr), 5)
  else
    let pt := -1
    in (externC("
          struct servent *p;
          p = getservbyname(addr, \"tcp\");
          if (p) pt = ntohs(p->s_port);
          "),
        if (pt = -1) server!(addr, -1, 5)
        else server!("", pt, 5)))

//<sb> @doc @xl port
// creates a INET domain listener socket listening on the port p. For instance
// here is a basic HTTP server :
// \code
// http_server(n:integer) : void ->
// 	let s := server!(n)
// 	in (while true
// 			let c := accept(s)
// 			in serve_client(c))
//
// serve_client(c:socket) : void ->
// 	(printf(c, "Hello world\n"),
// 	fclose(c))
//
// (http_server(80))
// \/code
claire/server!(p:integer) : listener -> server!("", p, 5)


//<sb> @doc @xl port
// creates a INET domain listener socket listening on the port p
// with an internal queue of qlen connections.
server!(addr:string, p:integer, qlen:integer) : listener ->
	(externC("
		int sock;
		int unix_domain = 0;
		#ifdef CLPC
			struct sockaddr_in inAddr;
		#else
			struct sockaddr_in inAddr;
			struct sockaddr_un unAddr;
			unix_domain = (strlen(addr) > 0 && addr[0] == '/');
		#endif
		if((sock = socket(unix_domain ? AF_UNIX : AF_INET, SOCK_STREAM, 0)) == 0) {
			#ifdef CLPC
				closesocket(sock);
			#else
				::close(sock);
			#endif
			Cerrorno(74,_string_(\"server! @ string\"),0);
		}
		int val = 1;
		setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&val, sizeof(val));
		// ensure a previously used socket won't prevent to call to succeed
		val = 1;
		setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&val,sizeof(val));
		#ifdef SO_REUSEPORT
		val = 1;
		setsockopt(sock,SOL_SOCKET,SO_REUSEPORT,(char*)&val,sizeof(val));
		#endif
		#if !defined(CLPC)
		if(fcntl(sock, F_GETFL, 0) == -1) {
			::close(sock);
			Cerrorno(74,_string_(\"server! @ string\"),0);
		}
		#endif
		if (unix_domain) {
			#ifndef CLPC
			strcpy(unAddr.sun_path, addr);
			#endif
		} else if(strlen(addr)==0) inAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		else inAddr.sin_addr.s_addr = inet_addr(addr);
		if (unix_domain) {
			#ifndef CLPC
			unAddr.sun_family = unix_domain ? AF_UNIX : AF_INET;
			#endif
		} else {
			inAddr.sin_family = unix_domain ? AF_UNIX : AF_INET;
			inAddr.sin_port = p < 0 ? htons((unsigned short)0) : htons(p);
		}
		#ifdef CLPC
		if( (bind(sock, (sockaddr*)&inAddr, sizeof(inAddr)) != 0)) {
		#else
		if( (unix_domain && bind(sock, (sockaddr*)&unAddr, sizeof(unAddr)) != 0) ||
			(unix_domain == 0 && bind(sock, (sockaddr*)&inAddr, sizeof(inAddr)) != 0)) {
		#endif
			#ifdef CLPC
				closesocket(sock);
			#else
				::close(sock);
			#endif
			Cerrorno(74,_string_(\"server! @ string\"),0);
		}
		if (p < 0) {
		  #ifdef CLPC
		  CL_INT len;
		  #else
		  GETPEERNAME_ARG3 len;
		  #endif
		  len = sizeof(struct sockaddr_in);
		  getsockname(sock, (sockaddr*)&inAddr, &len);
		  p = ntohs(inAddr.sin_port);
		}
		if(listen(sock, qlen) != 0) {
			#ifdef CLPC
				closesocket(sock);
			#else
				::close(sock);
			#endif
			Cerrorno(74,_string_(\"server! @ string\"),0);
		}"),
		let s := listener(fd = externC("sock", integer))
		in (if (addr[1] = '/') s.address := addr
    		else
    			(s.address := gethostname(),
    			s.tcpport := p),
    		s))

//<sb> doc
// close a single communication way on the given socket.
claire/shutdown(self:socket, mod:{"r","w"}) : void ->
	(if (mod = "r")
		(externC("{
		#if defined(CLPC)
			::shutdown(self->fd, SD_RECEIVE);
		#else 
			::shutdown(self->fd, SHUT_RD);
		#endif
		}"), none)
	else (externC("{
		#if defined(CLPC)
			::shutdown(self->fd, SD_SEND);
		#else 
			::shutdown(self->fd, SHUT_WR);
		#endif
		}"), none))
			
		
//<sb> @doc @xl port
// since socket are bi-channel communication ports a simple
// close (i.e. the two channel at once) may cause the client to
// miss information already sent on the socket but still unsent
// from the underlying system point of view. This is the purpose
// of the linger that will ensure that what is sent is actually
// received: first, the write channel is closed then we wait for
// the read channel to be closed by the remote part. For sanity
// this operation has a timeout of 3 seconds
claire/linger(self:socket) : void ->
	(flush(self),
	externC("
		#if defined(CLPC)
			int how = SD_SEND;
		#else 
			int how = SHUT_WR;
		#endif
		if(!::shutdown(self->fd, how)) {
			int t = 0;
			do {
				fd_set fdset;
				struct timeval tv;
				tv.tv_sec = 1;
				tv.tv_usec = 0;
				FD_ZERO(&fdset);
				FD_SET(self->fd, &fdset);
				if(select(self->fd+1, &fdset, NULL, NULL, &tv) > 0) {
					char dummy[4096];
					if (recv(self->fd,dummy,4096,0) <= 0)
						break;
				}
				t++;
			} while(t < 5);
		}"),
	fclose(self))


//<sb> doc
// accept a new connection on a listener port. the returned
// socket can be handle like a normal socket.
claire/accept(self:listener) : socket ->
	let c := socket(tcpport = self.tcpport)
	in (externC("
		int s;
		#ifdef CLPC
			struct sockaddr_in inAddr;
			int sin_size = sizeof(struct sockaddr_in);
			s = accept(self->fd, (struct sockaddr*)(&inAddr), &sin_size);
			if(s == INVALID_SOCKET) {
				Cerrorno(74,_string_(\"accept @ listener\"),0);
			}
		#else
			struct sockaddr_in inAddr;
			GETPEERNAME_ARG3 sin_size = (GETPEERNAME_ARG3)sizeof(struct sockaddr_in);
			s = accept(self->fd, (struct sockaddr*)(&inAddr), &sin_size);
			if(s == -1) {
				Cerrorno(74,_string_(\"accept @ listener\"),0);
			}
		#endif
		"),
		c.fd := externC("s", integer),
		c.address := copy(externC("inet_ntoa(inAddr.sin_addr)", string)),
		c)


//<sb> @doc @xl port
// return a pair of inter-connected socket
claire/socketpair() : tuple(socket, socket) ->
	let s1 := socket(),
		s2 := socket(),
		res := tuple(s1,s2)
	in (externC("
		#if defined(CLPC) || !defined(HAVE_SOCKETPAIR)
			Cerror(75,_string_(\"socketpair\"),0);
		#else
			int socks[2];
			if(socketpair(AF_UNIX, SOCK_STREAM, 0, socks) < 0) {
				Cerrorno(74,_string_(\"socketpair @ void\"),0);
			}
			s1->fd = socks[0];
			s2->fd = socks[1];
		#endif
		"), res)

read_port(self:socket, buf:char*, len:integer) : integer ->
	let r := 0
	in (//externC("\n#ifdef CLPC\n"),
		externC("\n#if 1\n"),
			while (r < len)
				let n := externC("::recv(self->fd, buf + r, len - r,0)", integer)
				in (if (n = 0)
						(self.eof_reached? := true,
						break())
					else if (n = -1 & externC("(errno != EINTR ? CTRUE : CFALSE)", boolean))
						externC("Cerrorno(97, _string_(\"read\"), _oid_(self))")
					else r :+ n),
		externC("\n#else\n"),
			while (r < len)
				let n := externC("::read(self->fd, buf + r, len - r)", integer)
				in (if (n = 0)
						(self.eof_reached? := true,
						break())
					else if (n = -1 & externC("(errno != EINTR ? CTRUE : CFALSE)", boolean))
						externC("Cerrorno(97, _string_(\"read\"), _oid_(self))")
					else r :+ n),
		externC("\n#endif\n"),
		r)

write_port(self:socket, buf:char*, len:integer) : integer ->
	let r := 0
	in (//externC("\n#ifdef CLPC\n"),
		externC("\n#if 1\n"),
			while (r < len)
				let n := externC("::send(self->fd, buf + r, len - r,0)", integer)
				in (if (n = -1 & externC("(errno != EINTR ? CTRUE : CFALSE)", boolean))
						externC("Cerrorno(97, _string_(\"write\"), _oid_(self))")
					else r :+ n),
		externC("\n#else\n"),
			while (r < len)
				let n := externC("::write(self->fd, buf + r, len - r)", integer)
				in (if (n = -1 & externC("(errno != EINTR ? CTRUE : CFALSE)", boolean))
						externC("Cerrorno(97, _string_(\"write\"), _oid_(self))")
					else r :+ n),
		externC("\n#endif\n"),
		r)



// ***************************************************************************
// * part 13: source location                                                *
// ***************************************************************************

//<sb> print the location associated with the current state
// of the given port without issuing a dynamic message (debug proof).
// mainly used to print "<file>:<line>"
print_source_location(self:port) : void ->
	let line := 0
	in (while (self % filter)
			(if (owner(self) = line_counter)
				(line := 1 + (self as line_counter).read_lines),
			self := self.target),
		let d := self as device
		in (case d
				(disk_file princ(d.file_path),
				socket princ(d.address /+ string!(d.tcpport)),
				descriptor princ("descriptor " /+ string!(d.fd)),
				any princ(owner(d).name.name)),
			if (line > 0)
				(princ(":"),
				princ(line))))

//<sb> return the current file and position in that file
// in the form of tuple(<filename>, <line>, <offset in the line>)
get_location(self:port) : tuple(string, integer, integer) ->
	let line := 0,
		off := 0
	in (while (self % filter)
			(if (owner(self) = line_counter)
				(line := 1 + (self as line_counter).read_lines,
				off := self.line_offset + 1),
			self := self.target),
		let d := self as device
		in tuple((case d
				(disk_file d.file_path,
				socket d.address /+ string!(d.tcpport),
				descriptor "descriptor " /+ string!(d.fd),
				any owner(d).name.name)), line, off))

// ***************************************************************************
// * part 5: popen                                                           *
// ***************************************************************************

//<sb> our only C FILE* interface: redirected process

FILE* <: import()

(c_interface(FILE*, "FILE*"))


popen_device <: device(child_comm:FILE*, exitcode:integer = 0)

eof_port?(self:popen_device) : boolean ->
	externC("(feof(self->child_comm) ? CTRUE : CFALSE)", boolean)

close_port(self:popen_device) : void ->
	externC("
	  self->exitcode = ::pclose(self->child_comm);
	  #ifndef CLPC
      if (WIFEXITED(self->exitcode)) {
        self->exitcode = WEXITSTATUS(self->exitcode);
      } else {
        self->exitcode = 1;
      }
    #endif
    ")

read_port(self:popen_device, buf:char*, len:integer) : integer ->
	let rc := externC("::fread(buf,1,len,self->child_comm)", integer)
	in (if externC("(ferror(self->child_comm) ? CTRUE : CFALSE)", boolean)
			externC("Cerrorno(74,_string_(\"read_port @ popen_device\"),0)"),
		rc)

flush_port(self:popen_device) : void -> externC("::fflush(self->child_comm)")

write_port(self:popen_device, buf:char*, len:integer) : integer ->
	let rc := externC("::fwrite(buf,1,len,self->child_comm)", integer)
	in (if externC("(ferror(self->child_comm) ? CTRUE : CFALSE)", boolean)
			externC("Cerrorno(74,_string_(\"write_port @ popen_device\"),0)"),
		rc)

//<sb> @doc @xl port
// popen creates a new process with a redirected input ("r")
// or output (w).
// popen may be a two way communication device, this
// is system dependent
claire/popen(file:string, mod:{"r", "w", "rw"}) : popen_device ->
	let m := (if unix?() mod else mod /+ "b"),
	    f := externC("::popen(file, m)", FILE*)
	in (if externC("(f == NULL ? CTRUE : CFALSE)", boolean)
			externC("Cerrorno(74,_string_(\"popen @ string\"),0)"),
		popen_device(child_comm = f))


//<sb> @doc @xl port
// perform a back-quote expansion of the system command s.
// subexpressions enclosed by '`' are substituted by the
// output generated by the corresponding command
// ex: bexpand("`ls`") returns the result of an ls command
[claire/bqexpand(s:string) : string ->
	let subs := explode(s, "`"), res := ""
	in (while subs
			(res :/+ subs[1],
			subs :<< 1,
			if subs
				let p := popen(subs[1],"r"), tmp := ""
				in (while not(eof?(p)) tmp :/+ fread(p, 1024),
					res :/+ trim(tmp),
					subs :<< 1,
					fclose(p))), res)]
