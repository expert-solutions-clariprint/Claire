
//<sb> This file is a fake intended for the documentation only
// it defines Kernel restrictions and associated comments used
// by the documentation generator. The language part of the
// document "Introduction to CLAIRE programming language" has
// been also dumped such the documentation generator can make
// a up-to date navigable document.

// @presentation
// The CLAIRE documentation that describe the CLAIRE language.
// Mainly issued from "Introduction to the CLAIRE Programming
// Language version 3.3" by Yves Caseau. It also contains a
// description of features that are exclusively present in the
// CLAIRE version provided by eXpert soLutions.
// @presentation


// @author Yves CASEAU
// @author Sylvain BENILAN

// @copyright Copyright (C) 1994-2006 Yves Caseau. All Rights Reserved.
// @copyright Copyright (C) 2000-2006 XL. All Rights Reserved.

// @preamble
// This documentation is mainly issued from the document by Yves Caseau
// "Introduction to the CLAIRE Programming Language version 3.3". It has
// been included in the source files of XL CLAIRE such to be used with the XL
// code documentation generator.
// In this documentation XL specific stuffs are denoted by an \xl mark.
// @preamble


// @cat What is CLAIRE ?
// @section Introduction
// CLAIRE is a high-level, portable, functional and object-oriented language with advanced
// rule processing capabilities. It is intended to allow the programmer to express complex
// algorithms with fewer lines and in an elegant and readable manner.\br
// To provide a high degree of expressivity, CLAIRE uses :
// \ul
// \li a rich type system including type intervals and second-order types (with static/dynamic typing),
// \li parametric classes and methods,
// \li propagation rules based on events,
// \li dynamic versioning that supports easy exploration of search spaces.
// \/ul
// To achieve its goal of readability, CLAIRE uses :
// \ul
// \li set-based programming with an intuitive syntax,
// \li simple-minded object-oriented programming,
// \li truly polymorphic and parametric functional programming,
// \li an entity-relation approach with explicit relations, inverses and unknown values.
// \/ul
// @cat


// @cat Design
// @section Introduction
// CLAIRE was designed for advanced applications that involve complex data modeling, rule processing
// and problem solving. CLAIRE was meant to be used in a C++ environment, either as a satellite
// (linking CLAIRE programs to C++ programs is straightforward) or as an upper layer (importing
// C++ programs is also easy). The key set of features that distinguishes CLAIRE from other
// programming languages has been dictated by our experience in solving complex optimization problems.
// Of particular interest are two features that distinguish CLAIRE from procedural languages such as
// C++ or Java :
// \ul
// \li \i Versioning \/i : CLAIRE supports versioning of a user-selected view of the entire system.
// The view can be made as large (for expressiveness) or as small (for efficiency) as is necessary.
// Versions are created linearly and can be viewed as a stack of snapshots of the system. CLAIRE
// supports very efficient creation/rollback of versions, which constitutes the basis for powerful
// backtracking, a key feature for problem solving. Unlike most logic programming languages, this
// type of backtracking covers any user-defined structure, not simply a set of logic variables.
// \li \i Production rules \/i : CLAIRE supports rules that bind a CLAIRE expression (the conclusion) to
// the combination of an event and a logical condition. Whenever this event occurs, if the condition
// is verified, then the conclusion is evaluated. The emphasis on events is a natural evolution from
// rule-based inference engines and is well suited to the description of reactive algorithms such as
// constraint propagation.
// \/ul
// @cat

// @cat Features
// @section Introduction
// CLAIRE provides automatic memory allocation/de-allocation, which would have prevented an easy
// implementation as a C++ library. Also, set-oriented programming is much easier with a set-oriented
// language like CLAIRE than with libraries. CLAIRE is about ten years old and the current version
// reaches a new level of maturity.\br
// CLAIRE is a high-level language that can be used as a complete development language, since it is
// a general purpose language, but also as a pre-processor to C++ or Java, since a CLAIRE program
// can be naturally translated into a C++ program (We continue to use C++ as our target language of
// choice, but the reader may now substitute Java to C++ in the rest of this document). CLAIRE is a
// set-oriented language in the sense that sets are first-class objects, typing is based on sets
// and control structures for manipulating sets are parts of the language kernel. Similarly,
// CLAIRE makes manipulating lists easy since lists are also first-class objects. Sets and lists
// may be typed to provide a more robust and expressive framework. CLAIRE can also be seen as a
// functional programming language, with full support for lambda abstraction, where functions can
// be passed as parameters and returned as values, and with powerful parametric polymorphism.\br
// CLAIRE is an object-oriented language with single inheritance. As in SMALLTALK, everything
// that exists in CLAIRE is an object. Each object belongs to a unique class and has a unique
// identity. Classes are the corner stones of the language, from which methods (procedures),
// slots and tables (relations) are defined. Classes belong themselves to a single inheritance
// hierarchy. However, classes may be grouped using set union operators, and these unions may be
// used in most places where a class would be used, which offers an alternative to multiple
// inheritance. In a way similar to Modula-3, CLAIRE is a modular language that provides
// recursively embedded modules with associated namespaces. Module decomposition can either be
// parallel to the class organization (mimicking C++ encapsulation) or orthogonal
// (e.g., encapsulating one service among multiple classes).\br
// CLAIRE is a typed language, with full inclusion polymorphism. This implies that one can
// use CLAIRE with a variety of type disciplines ranging from weak typing in a manner that is
// close to SMALLTALK up to a more rigid manner close to C++. This flexibility is useful to
// capture programming styles ranging from prototyping to production code development. The more
// typing information available, the more CLAIRE's compiler will behave like a statically typed
// language compiler. This is achieved with a rich type system, based on sets, that goes beyond
// types in C++. This type system provides functional types (second-order types) similar to ML,
// parametric types associated to parametric classes and many useful type constructors such as
// unions or intervals. Therefore, the same type system supports the naive user who simply
// wishes to use classes as types and the utility library developer who needs a powerful
// interface description language.\br
// \xl Starting with XL CLAIRE, CLAIRE is intended to cover various aspects of web oriented
// application (running in a CGI like environment), that is to serve dynamic content over
// the web. The Wcl syntax is introduced as new method of printing, in a similar way to
// printf but closer to the HTML syntax. The development of a web oriented agent would
// however require the module Wcl, not included in the standard XL CLAIRE distribution.
// @cat




// @cat Inspirations
// @section Introduction
// As the reader will notice, CLAIRE draws its inspiration from a large number of existing languages.
// A non-exhaustive list would include SMALLTALK for the object-oriented aspects, SETL for the set
// programming aspects, OPS5 for the production rules, LISP for the reflection and the functional
// programming aspects, ML for the polymorphism and C for the general programming philosophy. As far
// as its ancestors are concerned, CLAIRE is very much influenced by LORE, a language developed in
// the mid 80s for knowledge representation. It was also influenced by LAURE but is much smaller and
// does not retain the original features of LAURE such as constraints or deductive rules. CLAIRE is
// also closer to C in its spirit and its syntax than LAURE was.
// @cat



// @cat Integers and Floats
// @section Primitives
// @alias integer float integers floats number numbers
// Both floats and integers are CLAIRE primitives.
// integers are represented using 30 bits (which is required for the OID model)
// and are always signed. Floats are represented as C double precision floating point
// numbers.\br
// Arithmetic between integers and float can be handled using conversion method integer! and
// float! :
// \code
// 1 + 2 -> 3
// 1 + 2. -> error
// 1 + integer!(2.) -> 3
// float!(1) + 2. -> 3.
// \/code
// @cat




// @cat @xl Dates and Times
// @section Primitives
// @alias date time dates times epoch utc
// Dates and times are represented using floats containing an UNIX C time that is
// the time in seconds since the Epoch (00:00:00 UTC, January 1, 1970). The use of
// float is required since CLAIRE integer are coded on 30 bits and times on 32 bits.\br
// Internally, CLAIRE always handles dates represented in UTC.
// Times are referenced on the Epoch such the arithmetic between date and time can
// be made with the standard float arithmetic.\br
// Two kind of timer are also supported, one that account time in the
// process time (time_set/time_get) and one that count in real time (timer!/elapsed).
// @cat


// @cat Chars
// @section Primitives
// @alias char chars
// In CLAIRE chars are true object (i.e. not primitive) that hold an 8 bit value, one can
// obtain this value with integer!(c:char) and make a char from an integer i with char!(i:integer).\br
// \xl Starting with XL CLAIRE the internal 8 bit value is stored as an unsigned char (vs. signed char
// in CLAIRE 3) such the composition char!(integer!()) is actually the identity for all possible
// existing char in the system. If their is no char that hold a given value n then char!(n)
// will produce an error.
// @cat




// @cat Strings
// @section Primitives
// @alias string strings
// In CLAIRE strings are represented using a C char*, that is a sequence of 8 bit characters.
// The length of a string is computed by the general method length @ string :
// \code
// length("toto") -> 4
// \/code
// \xl Starting with XL CLAIRE strings may contain null char under certain restriction.
// Indeed XL CLAIRE makes difference between strings that are dynamically allocated and
// strings that are are statically compiled :
// \code
// s0 :: "a static string" // would compile as a static string
// s1 :: ("a string" /+ string!('\0') /+ "another string") // dynamically built string
// \/code
// In the above example s0 would be compiled statically, that is the string content would
// be allocated outside claire memory (e.g. in the data space of the program). In addition
// s1 is allocated dynamically and stored in a chunk of the claire memory. The important 
// difference between these two string is the handling of their length :
// \ul
// \li \b static\/b : the length is computed with strlen, so that a static string cannot
// contain a null character.
// \li \b dynamic\/b : the length is a property of the string stored outside the string content
// (like Pascal string handling) which allow arbitrary content including null character.
// \/ul
// Notice that inside the interpreter all strings are dynamically allocated which can give
// different behavior between the interpreted and the compiled code, for instance :
// \code
// s :: "a\0b" // dangerous !!! static string that contain a null
// (printf("~S\n", length(s)))
// \/code
// In the interpreter this code would print 3 whereas the compiled code would print 1. Indeed
// s would be compiled statically (outside claire memory) and its length would handled by
// strlen.\br
// As a general rule, any method that returns a new string returns a dynamic string. This is
// especially true for the port interface (fread and friends) which is particularly convenient
// to handle binary streams without having to deal with the null.
// @cat





// @cat Objects and Entities
// @section Objects, Classes and Slots
// @alias object objects entity entities
// A program in CLAIRE is a collection of entities (everything in CLAIRE is an entity).
// Some entities are pre-defined, we call them primitive entities, and some others may be
// created when writing a program, we call them objects. The set (a class) of all entities is
// called any and the set (a class also) of all objects is called object.\br
// \xl In XL CLAIRE port are not imported entity but implemented an extensible class vs. primitive (see port).\br
// Primitive entities consist of integers, floats, symbols, strings and
// functions. The most common operations on them are already built in, but you can add yours.
// You may also add your own entity classes using the import mechanism.\br
// Objects can be seen as "records", with named fields (called slots) and unique identifiers.
// Two objects are distinct even if they represent the same record. The data record structure and
// the associated slot names are represented by a class. An object is uniquely an instance of a class,
// which describes the record structure (ordered list of slots). CLAIRE comes with a collection of
// structures (classes) as well as with a collection of objects (instances).
// \def A class is a generator of objects, which are called its instances. Classes are organized into
// an inclusion hierarchy (a tree), so a class can also be seen as an extensible set of objects,
// which is the set of instances of the class itself and all its subclasses. A class has one
// unique father in the inclusion hierarchy (also called the inheritance hierarchy), called its
// superclass. It is a subclass of its superclass. \/def
// Each entity in CLAIRE belongs to a special class called its owner, which is the smallest
// class to which the entity belongs. The owner relationship is the extension to any of the
// traditional isa relationship between objects and classes, which implies that for any object x,
// x.isa = owner(x).\br
// Thus the focus on entities in CLAIRE can be summarized as follows: everything is an entity,
// but not everything is an object. An entity is described by its owner class, like an object, but 
// objects are "instantiated" from their classes and new instances can be made, while entities are
// (virtually) already there and their associated (primitive) classes don't need to be instantiated.
// A corollary is that the list of instances for a primitive class is never available.
// @cat





// @cat Classes
// @section Objects, Classes and Slots
// @alias class classes
// Classes are organized into a tree, each class being the subclass of another one, called its
// superclass. This relation of being a subclass (inheritance) corresponds to set inclusion: each
// class denotes a subset of its superclass. So, in order to identify instances of a class as objects
// of its superclass, there has to be some correspondence between the structures of both classes: all
// slots of a class must be present in all its subclasses. Subclasses are said to inherit the
// structure (slots) of their superclass (while refining it with other slots). The root of the
// class tree is the class any since it is the set of all entities. Formally, a class is defined by
// its superclass and a list of additional slots. Two types of classes can be created: those whose
// instances will have a name and those whose instances will be unnamed. Named objects must inherit
// (not directly, but they must be descendents) of the class thing. A named object is an object that
// has a name, which is a symbol that is used to designate the object and to print it. A named object
// is usually created with the x :: C() syntax but can also be created with
// new(C, name).\br
// Each slot is given as <name>:<range>=<default>. The range is a type and the optional default value
// is an object which type is included in <range>. The range must be defined before it is used, thus
// recursive class definitions use a forward definition principle (e.g., person).
// \code
// person <: thing // forward definition
// person <: thing(age:integer = 0, father:person)
// woman <: person // another forward definition
// man <: person(wife:woman)
// woman <: person(husband:man)
// child <: person(school:string)
// complex <: object(re:float, im:float)
// \/code
// A class inherits from all the slots of its super-classes, so they need not be recalled in the
// definition of the class. For instance, here, the class child contains the slots age and father,
// because it inherited them from person.\br
// A default value is used to place in the object slot during the instantiation (creation of
// a new instance) if no explicit value is supplied. The default value must belong to the range
// and will trigger rules or inverses in the same way an explicit value would. The only exception
// is the "unknown" value, which represents the absence of value. unknown is used when no default
// value is given (the default default value). Note that the default value is a real entity that is
// shared by all instances and not an expression that would be evaluated for each instantiation. The
// proper management of default values, or their absence through unknown,
// is a key feature of CLAIRE.\br
// From a set-oriented perspective, a class is the set union of all the instances of its
// descendents (itself, its subclasses, the subclasses of its subclasses, etc.). In some cases,
// it may be useful to "freeze" the data representation at some point: for this, two mechanisms are
// offered: abstract and final. First, a class c can be declared to have no instances with abstract(c)
// such as in the following :
// \code
// abstract(person)
// \/code
// An abstract class is not an empty set, it contains the instances of its descendents. Second, a
// class can also be declared to have no more new descendents using final as follows :
// \code
// final(colors)
// \/code
// It is a good practice to declare final classes that are leaves in the class hierarchy and that
// are not meant to receive subclasses in the future. This will enable further optimizations from
// the compiler. A class can be declared to instantiate ephemeral objects, in which case its extension
// (the list of its instances) is not kept. An important consequence is that ephemeral objects may be
// garbage collected when they are no longer used. For this behavior, the class must be declared with
// ephemeral or inherit from ephemeral_object :
// \code 
// action <: object(on:any, performed_by:object)
// ephemeral(action)
//
// action <: ephemeral_object(on:any, performed_by:object)
// \/code
// A class definition can be executed only once, even if it is left unchanged. On the other hand, 
// CLAIRE supports the notion of a class forward definition. A forward definition contains no slots
// and no parentheses. It simply tells the position of the class in the class hierarchy. A forward
// definition must be followed by a complete definition (with the same parent class !) before the
// class can be instantiated. Attempts to instantiate a class that has been defined only with a
// forward definition will produce an error. A forward definition is necessary in the case of
// recursive class definitions. Here is a simple example :
// \code 
// parent <: thing
// child <: thing(father:parent)
// parent <: thing(son:child)
// \/code 
// Although the father of a child is a parent (in the previous example), creating an instance of
// child does not create an implicit instance of parent that would be stored in the father slot. 
// Once an instance of child is created, it is your responsibility to fill out the relevant slots
// of the objects. There exists a way to perform this task automatically, using the close method.
// This method is the CLAIRE equivalent to the notion of a constructor(in a C++ or Java sense).
// CLAIRE does not support class constructors since its instantiation control structure may be
// seen as a generic constructor for all classes. However, there are cases when
// additional operations must be performed on a newly created object. To take this into account,
// the close method is called automatically when an instantiation is done if a relevant definition
// is found. Remember that the close method must always return the newly create object, since the
// result of the instantiation is the result of the close method. Here is an example that shows how
// to create a parent for each new child object :
// \code
// close(x:child) -> (x.father := parent(), x)
// \/code
// Slots can be mono- or multi-valued. A multi-valued slot contains multiple values that are
// represented by a list (ordered) or a set (without duplicates). CLAIRE assumes by default that
// a slot with range list or set is multi-valued. However, the multi-valuation is defined at the
// property level. This is logical, since the difference between a mono-valued and a multi-valued
// slot only occurs when inversion or rules are concerned, which are both defined at the property
// level. This means that CLAIRE cannot accept slots for two classes with the
// same name and different multi-valuation status. For instance, the following program will cause
// an error :
// \code 
// A <: thing(x:set[integer]) // forces CLAIRE to consider x as multi-valued
// B <: thing(x:stack[integer]) // conflict: x cannot be multi-valued
// \/code
// On the other hand, it is possible to explicitly tell CLAIRE that a slot with range list or set
// is mono-valued, as in the following correct example :
// \code
// A <: thing(x:set[integer])
// x.multivalued? := false // x is from A U B -> (set[integer] U stack[integer])
// B <: thing(x:stack[integer])
// \/code
// It is sometimes advisable to set up manually the multi-valuation status of the property
// before creating the slots, in order to make sure that this status cannot be forced by the
// creation of another class with a mono-valued slot with the same name (this could happen within
// a many-authors project who share a namespace). This is achieved simply by creating the property
// explicitly :
// \code
// x :: property(multivalued? = true) // creates the property
// // ... whatever happens will not change x's multi-valuation
// B <: thing(x:set[integer]) // safe definition of a multi-valued slot
// \/code
// @cat



// @cat @xl Free-able objects
// @section Objects, Classes and Slots
// Starting with XL CLAIRE, a class can inherit from freeable_object that are special kind of
// ephemeral objects regarding the Garbage collector (GC). We can define two GC callbacks (prefree!
// and free!) for such object that will be called when the GC attempt to free an object giving a
// chance for such object to perform a cleanup operation :
// \ul
// \li prefree! is called by the GC once for each object that will be freed in a short time. It
// is the handler of choice to perform synchronization between objects that are going to be
// freed (like flushing temporary data in a buffer filter).
// \li free! is called by the GC once for each object before it is actual freed (like freeing
// memory allocated outside CLAIRE memory or closing a descriptor). The body of a free! handler
// should make no assumption that the relations between the object and the database are valid.
// If we need to use object's relation then the prefree! handler should be used instead.
// \/ul
// As an illustration we could define the following long_double class that import from C++ the
// 'long double' data type :\br
// \code
// long_double* <: import()
// long_double <: freeable_object(value:long_double*)
// (c_interface(long_double*, "long double*"))
// 
// close(self:long_double) : long_double ->
// 	(self.value := externC("(long double*)::malloc(sizeof(long double))", long_double*),
// 	self)
// 
// free!(self:long_double) : void -> externC("::free(self->value)")
// \/code
// @cat

// @cat parametric class
// @section Objects, Classes and Slots
// @alias parametric
// A class can be parameterized by a subset of its slots. This means that subsets of the class
// that are defined by the value of their parameters can be used as types. This feature is useful
// to describe parallel structures that only differ by a few points: parametrization helps describing
// the common kernel, provides a unified treatment and avoids redundancy.\br
// A parameterized class is defined by giving the list of slot names into brackets. Parameters can
// be inherited slots, and include necessarily inherited parameters.
// \code
// stack[of] <: object(of:type,
// 					content:list[any],
// 					index:integer = 0)
// complex[re,im] <: object(re:float = 0.0, im:float = 0.0)
// \/code
// CLAIRE includes a type system that contains parametric class selections. For instance,
// the set of real numbers can be defined as a subset of complex with the additional constraint
// that the imaginary part is 0.0. This is expressed in CLAIRE as follows :
// \code
// complex[re:float, im:{0.0}]
// \/code
// In the previous example with stacks, parametric sub-types can be used to designate typed stacks.
// We can either specify the precise range of the stack (i.e., the value of the of parameter) or say
// that the range must be a sub-type of another type. For instance, the set of stacks with range
// integer and the set of stacks which contain integers are respectively :
// \code
// stack[of:{integer}]
// stack[of:subtype[integer]]
// \/code
// @cat





// @cat Calls and Slot Access
// @section Objects, Classes and Slots
// @alias slot slots call calls
// Calls are the basic building blocks of a CLAIRE program. A call is a polymorphic function
// call (a message) with the usual syntax : a selector followed by a list of arguments between
// parentheses. A call is used to invoke a method.\br
// When the selector is an operation, such as +, -, %, etc... (% denotes set membership) an infix
// syntax is allowed (with explicit precedence rules) :
// \code
// eval(x), f(x,y,z), x.price, y.name
// \/code
// If a slot is read before being defined (its value being unknown), an error is raised. This only
// occurs if the default value is unknown. To read a slot that may not be defined, one must use the
// get(r:property,x:object) method :
// \code
// John.father // may provoke an error if John.father is unknown
// get(father,john) // may return unknown
// \/code
// When the selector is an operation, such as +,-,%,etc... (% denotes set membership) an infix
// syntax is allowed (with explicit precedence rules). Hence the following expressions are valid :
// \code
// 1 + 2
// 1 + 2 * 3
// \/code
// Note that new operations may be defined. This syntax extends to boolean operations
// (and:& and or:|). However, the evaluation follows the usual semantic for boolean expression
// (e.g., (x & y) does not evaluate y if x evaluates to false) :
// \code
// (x = 1) & ((y = 2) | (y > 2)) & (z = 3)
// \/code
// The values that are combined with and/or do not need to be boolean values (although boolean
// expressions always return the boolean values true or false). Following a philosophy borrowed from
// LISP, all values are assimilated to true, except for false, empty lists and empty sets. The special
// treatment for the empty lists and the empty sets yields a simpler
// programming style when dealing with lists or sets. Notice that in CLAIRE 3.0, contrary to previous
// releases, there are many empty lists since empty lists can be typed (list<integer>(),
// list<string>(), ... are all different).\br
// A dynamic functional call where the selector is evaluated can be obtained using the call method.
// For instance, call(+,1,2) is equivalent to +(1,2) and call(show,x) is equivalent to show(x). The
// difference is that the first parameter to call can be any expression. This is the key for writing
// parametric methods using the inline capabilities of CLAIRE. This also means that
// using call is not a safe way to force dynamic binding, this should be done using the property
// abstract. An abstract property is a property that can be re-defined at any time and, therefore,
// relies on dynamic binding. Notice that call takes a variable number of arguments. A similar method
// named apply can be used to apply a property to an explicit list of arguments.\br
// Since the use of call is somehow tedious, CLAIRE supports the use of variables (local or global)
// as selectors in a function call and re-introduce the call implicitly. For instance :
// \code
// compose(f:property, g:property, x:any) : any
// 	=> f(g(x))
// \/code
// is equivalent to :
// \code
// compose(f:property, g:property, x:any)
// 	=> call(f, call(g,x))
// \/code
// @cat

// @cat Updates
// @section Objects, Classes and Slots
// @alias update updates
// Assigning a value to a variable is always done with the operator :=. This applies to local
// variables but also to the slots of an object. The value returned by the assignment is always
// the value that was assigned :
// \code
// x.age := 10, John.father := mary
// \/code
// When the assignment depends on the former value of the variable, an implicit syntax ":op"
// can be used to combine the previous value with a new one using the operation op. This can be
// done with any (built-in or user-defined) operation (an operation is a function with arity 2
// that has been explicitly declared as an operation) :
// \code
// x.age :+ 1, John.friends :add mary, x.price :min 100
// \/code
// Note that the use of :op is pure syntactical sugar: x.A :op y is equivalent to x.A := (x.A op y).
// The receiving expression should not, therefore, contain side-effects as in the dangerous following
// example :
// \code
// A(x :+ 1) :+ 1
// \/code
// @cat


// @cat Lists, Sets and Tuples
// @section Lists, Sets and Instructions
// @alias bag bags list lists set sets tuple tuples
// CLAIRE provides two easy means of manipulating collections of objects: sets and lists.
// Lists are ordered, possibly heterogeneous, collections. To create a list, one must use
// the list(...) instruction : it admits any number of arguments and returns the list of its
// arguments. Each argument to the list(...) constructor is evaluated.\br
// \code
// list(a, b, c, d) list(1, 2 + 3), list()
// \/code
// Sets are collections without order and without duplicates. Sets are created similarly
// with the set(...) constructor :
// \code
// set(a,b,c) set(1,2 + 3)
// \/code
// The major novelty in CLAIRE 3.2 is the fact that lists or sets may be typed. This means
// that each bag (set or list) may have a type slot named of, which contains a type to which
// all members of the list must belong. This type is optional, as is illustrated by the previous
// examples, where no typing was given for the lists or sets. To designate a type for a new list
// or a new set, we use a slightly different syntax :
// \code
// list<thing>(a,b,c,d) list<integer>(1,2 + 3) list<float>()
// set<thing>(a,b,c) set<integer>(1, 2 + 3)
// \/code
// Typing a list or a set is a way to ensure that adding new values to them will not violate
// typing assumptions, which could happen in earlier versions of CLAIRE. Insertion is now always
// a destructive operation (add(l,x) returns the list l, that has been augmented with the value x
// at its end).\br
// Since typing is mandatory in order to assume type-safe updates onto a list or a set, if no
// type is provided, CLAIRE will forbid any future update: the list or the set is then a "read-only"
// structure. This is the major novelty in CLAIRE 3.2: there is a difference between:
// \code
// list(a,b,c,d) set(1,2 + 3) list{i | i in (1 .. 2)}
// \/code
// which are read-only structures, and :
// \code
// list<thing>(a, b) set<integer>(1, 2 + 3)
// list<integer>{i | i in (1 .. 2)}
// \/code
// which are structures that can be updated.\br
// List or set types can be arbitrarily complex, to represent complex list types such as
// list of lists of integers. However, it is recommended to use a global constant
// to represent a complex type that is used as a list type, as follows :
// \code
// MyList :: list<integer>
// set<MyList>(list<integer>(1), list<integer>(2, 3))
// \/code
// Constant sets are valid CLAIRE types and can be built using the following syntax :
// \code
// {a,b,c,d} {3, 8}
// \/code
// The expressions inside a constant set expression are not evaluated and should be primitive
// entities, such as integers or strings, named objects or global constants. Constant sets are 
// constant, which means that inserting a new value is forbidden and will provoke an error.\br
// A set can also be formed by selection. The result can either be a set with {x in a | P(x)}, or
// a list with list{x in a | P(x)}, when one wants to preserve the order of a and keep the duplicates
// if a was a list. Similarly, one may decide to create a typed or an un-typed list or set, by adding
// the additional type information between angular brackets. For instance, here are two samples with
// and without typing :
// \code
// {x in class | (thing % x.ancestors)}
// list{x in (0 .. 14) | x mod 2 = 0}
// set<class>{x in class | (thing % x.ancestors)}
// list<integer>{x in (0 .. 14) | x mod 2 = 0}
// \/code
// When does one need to add typing information to a list or a set ? A type is needed when new
// insertions need to be made, for instance when the list or set is meant to be stored in an
// object's slot which is itself typed.\br
// Also, the imageof a set via a function can be formed. Here again, the result can either be a set
// with {f(x)|x in a} or a list with list{f(x) | x in a}, when one wants to preserve the order of a
// and the duplicates :
// \code
// {(x ^ 2) | x in (0 .. 10)}
// list<integer>{size(x.slots) | x in class}
// \/code
// For example, we have the traditional average_salary method :
// \code
// average_salary(s:set[man]) : float
// 	-> (sum(list{m.sal | m in s}) / size(s))
// \/code
// Last, two usual constructions are offered in CLAIRE to check a boolean expression universally
// (forall) or existentially (exists). A member of a set that satisfies a condition can be extracted
// (a non-deterministic choice) using the some construct: some(x in a | f(x)). For instance, we can write :
// \code
// exists(x in (1 .. 10) | x > 2) // returns true
// some(x in (1 .. 10) | x > 2) // returns 3 in most implementations
// exists(x in class | length(x.ancestors) > 10)
// \/code
// The difference between exists and some is that the first always returns a boolean, whereas the
// second returns one of the objects that satisfy the condition (if there exists one) and unknown
// otherwise. It is very often used in conjunction with when, as in the following example :
// \code
// when x := some(x in man | rich?(x))
// in (borrow_from(x,1000), ...)
// else printf("There is no one from whom to borrow!")
// \/code
// Conversely, the boolean expression forall(x in a | f(x)) returns true if and only if f(x) is
// true for all members of the set a. The two following examples returns false (because of 1):
// \code
// forall(x in (1 .. 10) | x > 2)
// forall(x in (1 .. n) | exists(y in (1 .. x) | y * y > x))
// \/code
// \def A list is an ordered collection of objects that is organized into an extensible array,
// with an indexed access to its members. A list may contain duplicates, which are multiple
// occurrence of the same object. A set is a collection of objects without duplicates and without
// any user-defined order. The existence of a system-dependent order is language-dependent and
// should not be abused. The concept of bag in CLAIRE is the unifier between lists and sets : a
// collection of objects with possible duplicates and without order. \/def
// A read-only (untyped) list can also be thought as tuples of values. For upward compatibility reasons,
// the expression tuple(a1,...,an) is equivalent to list(a1,...,an) :
// \code
// tuple(1,2,3), tuple(1,2.0,"this is heterogeneous")
// \/code
// Since it is a read-only list, a tuple cannot be changed once it is created, neither through addition
// of a new member (using the method add) or through the exchange of a given member (using the nth=
// method). CLAIRE offers an associated data type. For instance, the
// following expressions are true :
// \code
// tuple(1,2,3) % tuple(integer,integer,integer)
// tuple(1,2,3) % tuple(0 .. 1, 0 .. 10, 0 .. 100)
// tuple(1,2.0,"this is heterogeneous") % tuple(any,any,any)
// \/code
// Typed tuples are used to return multiple values from a method. Because a tuple
// is a bag, it supports membership, iteration and indexed access operations. However, there is yet
// another data structure in CLAIRE for homogeneous arrays of fixed length, called arrays. Arrays are
// similar to lists but their size is fixed once they are created and they must be assigned a subtype
// (a type for the members of the array) that cannot change. Because of these strong constraints, 
// CLAIRE can provide an implementation that is more efficient (memory usage and access time) than
// the implementation of bags. However, the use of arrays is considered an advanced feature of CLAIRE
// since everything that is done with an array may also be done with a list.
// @cat





// @cat Blocks
// @section Lists, Sets and Instructions
// @alias block blocks
// Parentheses can be used to group a sequence of instructions into one. In this case, the returned
// value is the value of the last instruction :
// \code
// (x := 3, x := 5)
// \/code
// Parentheses can also be used to explicitly build an expression. In the case of boolean evaluation
// (for example in an if), any expression is considered as true except false, empty sets and empty
// lists :
// \code
// (1 + 2) * 3
// if (x = 2 & l)
// \/code
// Local variables can be introduced in a block with the let construct. These variables can be typed,
// but it is not mandatory (CLAIRE will use type inference to provide with a reasonable type). On
// the other hand, unlike languages such as C++, you always must provide an initialization value
// when you define a variable. A let instruction contains a sequence of variable definitions and,
// following the in keyword, a body (another instruction). The scope of the local variable is exactly
// that body and the value of the let instruction is the value returned by this body.
// \code
// let x := 1, y := 3 in (z := x + y, y := 0)
// \/code
// Notice that CLAIRE uses := to represent assignment and = to represent equality.
// The compiler will issue a warning if a statement (x = y) is used where an assignment was
// probably meant (this is the case when the value of the assignment is not needed, such as
// in x := 1, y = 3, z := 4).\br
// The value of local variables can be changed with the same syntax as an update to an object:
// the syntax :op is allowed for all operations op :
// \code
// x := x + 1, x :+ 1, x :/ 2, x :^ 2
// \/code
// The name of a local variable can be any identifier, including the name of an existing object
// or variable. In that case, the new variable overrides the older definition within the scope
// of the let. While this may prove useful in a few cases, it should be used sparingly since it
// yields to code that is hard to read. A rule of thumb is to avoid mixing the name of variables
// and the name of properties since it often produces errors that are hard to catch (the property
// cannot be accessed any more once a variable with the same name is defined). The control
// structure when is a special form of let, which only evaluates the body if the value of the
// local variable (unique) is not unknown (otherwise, the returned value is unknown). This is
// convenient to use slots that are not necessarily defined as in the following example :
// \code
// when f := get(father,x)
// in printf("his father is ~S\n", f)
// \/code
// The default behavior when the value is unknown can be specified using the else keyword.
// The statement following the else keyword will be evaluated and its value will be returned
// when the value of the local variable is unknown :
// \code
// when f := get(father,x)
// in printf("his father is ~S\n", f)
// else printf("his father is not known at the present time\n")
// \/code
// Local variables can also be introduced as a pattern, that is a tuple of variables. In that
// case, the initial value must be a tuple of the right length. For instance, one could write :
// \code
// let (x, y, z) := tuple(1, 2, 3) in x + y + z
// \/code
// The tuple of variable is simply introduced as a sequence of variables surrounded by two 
// parentheses. The most common use of this form is to assign the multiple values returned
// by a function with range tuple, as we shall see in the next section. If we suppose that f
// is a method that returns a tuple with arity 2, then the two following forms are equivalent:
// \code
// let (x1,x2) := f() in ...
//
// let l := f(), x1 := l[1], x2 := l[2] in ...
// \/code
// \xl In XL CLAIRE, as a syntactical shortcut, we can define in a single let statement both
// tuple assigment and normal variable assigment as in :
// \code
// let (x1,x2) := f(),
// 	x3 := g() in ...
// \/code
// Tuples of variables can also be assigned directly within a block as in the following example :
// \code
// (x1, x2) := tuple(x2, x1)
// \/code
// Although this mostly used for assigning the result of tuple-valued functions without any useless
// allocation, it is interesting to note that the previous example will be compiled into a nice
// value-exchange interaction without any allocation (the compiler is smart enough to determine
// that the list "list(x2,x1)" is not used as such).\br
// The key principle of lexical variables is that they are local to the "let" in which they are
// defined. CLAIRE supports another similar type of block, which is called a temporary slot
// assignment. The idea is to change the value of a slot but only locally, within a given expression.
// This is done as follows:
// \code
// let x.r := y in e
// \/code
// changes the value of r(x) to y, executes e and then restore r(x) to its previous value. It is
// strictly equivalent to
// \code
// let old_v := x.r
// in (x.r := y,
// 	let result := e
// 	in (x.r := old_v, result))
// \/code
// CLAIRE provides automatic type inference for variables that are defined in a let so that explicit
// typing is not necessary in most of the cases. Here are a few rules to help you decide if you need
// to add an explicit type to your variable or even cast a special type for the value that is
// assigned to the variable :
// \ol
// \li (a) Type inference will provide a type to a Let variable only if they do not have one already.
// \li (b) when you provide a type in let x:t := y, the compiler will check that the value y belong
// to t and will issue a warning and/or insert a run-time type-check accordingly.
// \li (c) if you want to force the type that is inferred to something smaller than what CLAIRE thinks
// for y, you must use a cast :
// \code
// let x := (y as t2) in ...
// \/code
// \/ol
// To summarize :
// \ul
// \li in most cases CLAIRE range inference works, so you write let x := y in ...
// \li you use let x:t := y to weaken the type inference, mostly because you want to put 
// something of a different type later
// \li you use let x := (y as t) to narrow the type inferred by CLAIRE.
// \/ul
// @cat




// @cat Conditionals
// @section Lists, Sets and Instructions
// if statements have the usual syntax (if <test> x else y) with implicit nestings (else if).
// The <test> expression is evaluated and the instruction x is evaluated if the value is
// different from false, nil or {}. Otherwise, the instruction y is evaluated,
// or the default value false is returned if no else part was provided.
// \code
// if (x = 1) x := f(x,y)
// else if (x > 1) x := g(x,y)
// else (x := 3, f(x,y))
//
// if (let y := 3 in x + y > 4 / x) print(x)
// \/code
// If statements must be inside a block, which means that if they are not inside a sequence
// surrounded by parenthesis they must be themselves surrounded by parenthesis
// (thus forming a block).\br
// case is a set-based switch instruction: CLAIRE tests the branching sets one after another,
// executes the instruction associated with the first set that contains the object and exits the
// case instruction without any further testing. Hence, the default branch is associated with the
// set any. As for an if, the returned value is nil if no branch of the case is relevant :
// \code
// case x ({1} x + 1, {2,3} x + 2, any x + 3)
// case x (integer (x := 3, print(x)),
// 		any error("~I is no good\n",x))
// \/code
// Note that the compiler will not accept a modification of the variable that is not consistent
// with the branch of the case (such as case x ({1} x := 2)). The expression on which the switching
// is performed is usually a variable, but can be any expression. However, it should not produce any
// side effect since it will be evaluated many times.\br
// Starting with CLAIRE 3.3, only boolean expressions should be used in the <test> expression of a
// conditional statement. The implicit coercion of any expression into a Boolean is still supported,
// but should not be used any longer. The compiler will issue a warning if a non-boolean expression
// is used in an If.
// @cat




// @cat Loops
// @section Lists, Sets and Instructions
// CLAIRE supports two types of loops: iteration and conditional loops (while and until).
// Iteration is uniquely performed with the for statement, it can be performed on any collection :
// \code
// for x in (1 .. 3) a[x] := a[x + 3]
// for x in list{x in class | size(x.ancestors) >= 4}
// 	printf("~S \n", x)
// \/code
// A collection here is taken in a very general sense, i.e., an object that can be seen as a set
// through the enumeration method set!. This includes all CLAIRE types but is not restricted since
// this method can be defined on new user classes that inherit from the collection root. For instance,
// set!(n:integer) returns the subset of (0 .. 29) that is represented by the integer n taken as
// a bit-vector. To tell CLAIRE that her new class is a collection, the user must define it as a
// subclass of collection. If x is a collection, then :
// \code
// for z in x ...
//
// (z % x)
// \/code
// are supported. When defining a new subclass of collection, the methods set! and % must be
// defined for this new class, and it is also advisable to define size and iterate to get compiler
// speed-ups (if size is not defined, an implicit call to set! is made). Other collection handling
// methods, such as add, delete, etc may be defined freely if needed.\br
// Notice that it is possible that the expression being evaluated inside the loop modifies the
// set itself, such as in :
// \code
// for x in {y in S | P(y)} P(x) := false
// \/code
// Because the CLAIRE compiler tries to optimize iteration using lazy evaluation, there is no
// guarantee about the result of the previous statement. In this case, it is necessary to use an
// explicit copy as follows :
// \code
// for x in copy({y in S | P(y)}) P(x) := false
// \/code
// The iteration control structure plays a major role in CLAIRE. It is possible to optimize its
// behavior by telling CLAIRE how to iterate a new subclass (C) of collection. This is done through
// adding a new restriction of the property iterate for this class C, which tells how to apply a given
// expression to all members of an instance of C. This may avoid the explicit construction of the
// equivalent set which is performed through the set! method.\br
// Conditional loops are also standard (the exiting condition is executed before each loop in a while
// and after each loop in a until),
// \code
// while (x > 0) x :+ 1
// until (x = 12) x :+ 1
// while not(i = size(l))
// 	(l[i] := 1, i :+ 1)
// \/code
// The value of a loop is false. However, loops can be exited with the break(x) instruction, in which
// case the return value is the value of x :
// \code
// for x in class (if (x % subtype[integer]) break(x))
// \/code
// There is one restriction with the use of break: it cannot be used to escape from a try ... catch
// block. This situation will provoke an error at compile-time.
// @cat



// @cat Instantiation
// @section Lists, Sets and Instructions
// Instantiation is the mechanism of creating a new object of a given class;
// instantiation is done by using the class as a selector and by giving a list of
// "<slot> = <value>" pairs as arguments :
// \code
// complex(re = 0.0, im = 1.0)
// person(age = 0, father = john)
// \/code
// Recall that the list of instances of a given class is only kept for non-ephemeral classes
// (a class is ephemeral if has been declared as such or if it inherits from the
// ephemeral_object class). The creation of a new instance of a class yields to a function
// call to the method close. Objects with a name are represented by the class thing, hence
// descendents of thing (classes that inherit from thing) can be given a name with the
// definition operation ::. These named objects can later be accessed with their name,
// while objects with no name offer no handle to manipulate them after their creation outside
// of their block (objects with no name are usually attached to a local variable with a let
// whenever any other operation other than the creation itself is needed) :
// \code
// paul :: person(age = 10, father = peter)
// \/code
// Notice that the identifier used as the name of an object is a constant that cannot be
// changed. Thus, it is different from creating a global variable that would contain an
// object as in :
// \code
// aGoodGuy:person :: person(age = 10, father = peter)
// \/code
// Additionally, there is a simpler way of instantiating parameterized classes by dropping
// the slot names. All values of the parameter slots must be provided in the exact order that
// was used to declare the list of parameters. For instance, we could use :
// \code
// complex(0.0,1.0), stack(integer)
// \/code
// The previously mentioned instantiation form only applies to a parameterized class. It is
// possible to instantiate a class that is given as a parameter (say, the variable v) using
// the new method. New(v) creates an instance of the class v and new(v,s) creates a named
// instance of the class v (assumed to be a subclass of thing) with the name s.
// @cat




// @cat Exception Handling
// @section Lists, Sets and Instructions
// @alias exception exceptions error errors
// Exceptions are a useful feature of software development: they are used to describe an exceptional
// or wrong behavior of a block. Exception can be raised, to signal this behavior and are caught by
// exception handlers that surround the code where the exceptional behavior happened. Exceptions are
// CLAIRE objects (a descendent from the class exception) and can contain information in slots.
// The class exception is an "ephemeral" class, so the list of instances is not kept. In fact,
// raising an exception e is achieved by creating an instance of the class e. Then, the method
// close is called: the normal flow of execution is aborted and the control is passed to the
// previously set dynamic handler. A handler is created with the following instruction :
// \code
// try <expression> catch <class> <expression>
// \/code
// For instance we could write :
// \code
// try 1 / x
// catch any (printf("1/~A does not exists", x), 0)
// \/code
// A handler "try e catch c f", associated with a class c, will catch all exceptions that may occur
// during the evaluation of e as long as they belong to c. Otherwise the exception will be passed
// to the previous dynamic handler (and so on). When a handler "catches" an exception, it evaluates
// the "f" part and its value is returned. The last exception that was raised can be accessed
// directly with the exception!() method. Also, as noticed previously, the body of a handler
// cannot contain a break statement that refers to a loop defined outside the handler.\br
// The most common exceptions are errors and there is a standard way to create an error in CLAIRE
// using the error(s:string, l:listargs) instruction. This instruction creates an error object
// that will be printed using the string s and the arguments in l, as in a printf statement.
// Here are a few examples :
// \code
// error("stop here")
// error("the value of price(~S) is ~S !", x, price(x))
// \/code
// Another very useful type of exception is contradiction. CLAIRE provides a class contradiction
// and a method contradiction!() for creating new contradictions. This is very commonly used for
// hypothetical reasoning with forms like :
// \code
// try (choice(), // create a new world
// 	...)       // performs an update that may cause a contradiction
// catch contradiction
// 	(backtrack(), // return to previous world
// 	...)
// \/code
// In fact, this is such a common pattern that CLAIRE provides a special instruction, branch(x),
// which evaluates an expression inside a temporary world and returns a boolean value, while
// detecting possible contradiction. The statement branch(x) is equivalent to :
// \code
// try (choice(),
// 	if x true else (backtrack(), false))
// catch contradiction (backtrack(), false)
// \/code
// If we want to find a value for the slot x.r among a set x.possible that does not cause a
// contradiction (through rule propagation) we can simply write :
// \code
// when y := some(y in x.possible | branch(x.r = y))
// in x.r := y
// else contradiction!()
// \/code
// @cat



// @cat array
// @section Lists, Sets and Instructions
// @alias array arrays
// An array can be seen as a fixed-size list, with a member type (the slot name is of),
// which tells the type of all the members of the array. Because of the fixed size, the
// compiler is able to generate faster code than when using lists, so lists should be used
// when the collection shrinks and grows, and an array may be used otherwise. This is especially
// true for arrays of floats, which are handled in a special (and efficient) way by the compiler.\br
// Arrays are simpler than lists, and only a few operations are supported. Therefore, more complex
// operations such as append often require a cast to list (list!). An array is created explicitly
// with the make_array property :
// \code
// let l := make_array(10,float,0.0)
// in l[1] := l[3] + l[4]
// \/code
// Operations on arrays include copying, casting a bag into an array (array!), defeasible update
// on arrays using store, and returning the length of the array with length. An array can also be
// made from a list using array!, which is necessary to create arrays that contain complex objects
// (such as arrays of arrays).
// @cat



// @cat Methods
// @section Methods and Types
// @alias method methods
// A method is the definition of a property for a given signature. A method is defined by the
// following pattern : a selector (the name of the property represented by the method), a list
// of typed parameters (the list of their types forms the domain of the method), a range expression
// and a body (an expression or a let statement introduced by -> or =>).
// \code
// <selector>(<typed parameters>) : <range>\sup opt\/sup  < -> | => > <body>
//
// fact(n:{0}) : integer -> 1
// fact(n:integer) : integer -> (n * fact(n - 1))
// print_test() : void
// 	-> (print("Hello"),
// 		print("world\n")
// \/code
// \def A signature is a Cartesian product of types that always contains the extension of the function.
// More precisely, a signature A\sub 1\/sub * A\sub 2\/sub * ... * A\sub n\/sub , also represented as list(A\sub 1\/sub , ...,A\sub n\/sub ) or
// A\sub 1\/sub * A\sub 2\/sub * ... * A\sub n-1\/sub  -> A\sub n\/sub , is associated to a method definition f(...) : A\sub n\/sub  -> ... for two
// purposes: it says that the definition of the property f is only valid for input arguments
// (x\sub 1\/sub , x\sub 2\/sub , ..., x\sub n-1\/sub ) in A\sub 1\/sub * A\sub 2\/sub * ... * A\sub n-1\/sub  and it says that the result of f(x\sub 1\/sub , x\sub 2\/sub , ..., x\sub n-1\/sub )
// must belong to A\sub n\/sub . The property f is also called an overloaded function and a method m is called its restriction
// to A\sub 1\/sub * A\sub 2\/sub * ... * A\sub n-1\/sub .
// \/def
// If two methods have intersecting signatures and the property is called on objects in both signatures,
// the definition of the method with the smaller domain is taken into account. If the two domains have a
// non-empty intersection but are not comparable, a warning is issued and the result is
// implementation-dependent. The set of methods that apply for a given class or return results in
// another can be found conveniently with methods.\br
// The range declaration can only be omitted if the range is void. In particular, this is convenient
// when using the interpreter :
// \code
// loadMM()
// -> (begin(my_module),
// 	load("f1"),
// 	load("f2"),
// 	end(my_module))
// \/code
// If the range is void (unspecified), the result cannot be used inside another expression
// (a type-checking error will be detected at compilation). A method's range must be declared
// void if it does not return a value (for instance, if its last statement is, recursively, a call
// to another method with range void). It is important not to mix restrictions with void range with
// other regular methods that do return a value, since the compiler will generate an error when
// compiling a call unless it can guarantee that the void methods will not be used.\br
// The default range was changed to void in the version 3.3 of CLAIRE, in an effort to encourage
// proper typing of methods: "no range" means that the method does not return a value. This is an
// important change when migrating code from earlier versions of CLAIRE.
// CLAIRE supports methods with a variable number of arguments using the listargs keyword. The
// arguments are put in a list, which is passed to the (unique) argument of type listargs. For
// instance, if we define :
// \code
// [f(x:integer,y:listargs) -> x + size(y)]
// \/code
// A call f(1,2,3,4) will produce the binding x = 1 and y = list(2,3,4) and will return 4.\br
// CLAIRE also supports functions that return multiple values using tuples. If you need a function
// that returns n values v1,v2,...,vn of respective types t1,t2,...,tn, you simply declare its range
// as tuple(t1,t2,...,tn) and return tuple(v1,v2,...,vn) in the body of the function. For instance the
// following method returns the maximum value of a list and the "regret" which is the difference
// between the best and the second-best value :
// \code
// [my_max(l:list[integer]) : tuple(integer,integer)
// -> let x1 := 1000000000, x2 := 1000000000
// 	in (for y in l
// 		(if (y < x1) (x2 := x1, x1 := y)
// 		else if (y < x2) x2 := y),
// 		tuple(x1,x2))]
// \/code
// The tuple produced by a tuple-valued method can be used in any way, but the preferred way is to
// use a tuple-assignment in a let. For instance, here is how we would use the max2 method :
// \code
// let (a,b) := my_max(list{f(i) | i in (1 .. 10)})
// in ...
// \/code
// Each time you use a tuple-assignment for a tuple-method, the compiler uses an optimization
// technique to use the tuple virtually without any allocation. This makes using tuple-valued
// methods a safe and elegant programming technique.\br
// The body of a method is either a CLAIRE expression (the most common case) or an external (C++)
// function. In the first case, the method can be seen as defined by a lambda abstraction. This
// lambda can be created directly through the following :
// \code
// lambda[(<typed parameters>), <body>]
// \/code
// Defining a method with an external function is the standard way to import a C/C++ function
// in CLAIRE. This is done with the function!(...) constructor, as in the following :
// \code
// f(x:integer,y:integer) -> function!(my_version_of_f)
// cos(x:float) -> function!(cos_for_claire)
// \/code
// It is important to notice that in CLAIRE, methods can have at most 20 parameters. Methods with
// 40 or more parameters that exist in some C++ libraries are very hard to maintain. It is advised
// to use parameter objects in this situation.\br
// CLAIRE also provides inline methods, that are defined using the => keyword before the body
// instead of ->. An inline method behaves exactly like a regular method. The only difference is
// that the compiler will use in-line substitution in its generated code instead of a function call
// when it seems more appropriate. Inline methods can be seen as polymorphic macros, and are
// quite powerful because of the combination of parametric function calls (using call(...))
// and parametric iteration (using for). Let us consider the two following examples, where
// subtype[integer] is the type of everything that represents a set of integers :
// \code
// sum(s:subtype[integer]) : integer
// 	=> let x := 0 in (for y in s x :+ y, x)
//
// min(s:subtype[integer], f:property) : integer
// 	=> let x := 0, empty := true
// 		in (for y in s
// 			(if empty (x := y, empty := false)
// 			else if call(f,y,x) x := y),
// 			x)
// \/code
// For each call to these methods, the compiler performs the substitution and optimizes the result.
// For instance, the optimized code generated for sum({x.age | x in person}) and for
// min({x in 1 .. 10 | f(x) > 0}, >) will be :
// \code
// let x := 0
// in (for %v in person.instances
// 		let y := %v.age in x :+ y, x)
//
// let x := 0, empty := true, y := 1, max := 10
// in (while (y <= max)
// 		(if (f(y) > 0)
// 			(if empty (x := y, empty := false)
// 			else if (y > x) x := y),
// 		y :+ 1),
// 	x)
// \/code
// Notice that, in these two cases, the construction of temporary sets is totally avoided. The
// combined use of inline methods and functional parameters provides an easy way to produce generic
// algorithms that can be instantiated as follows :
// \code
// mymin(l:list[integer]) : integer -> min(l, my_order)
// \/code
// The code generated for the definition of mymin @ list[integer] will use a direct call to
// my_order (with static binding) and the efficient iteration pattern for lists, because min is
// an inline method. In that case, the previous definition of min may be seen as a pattern of
// algorithms.\br
// \ul \li \b CAVEAT : \/b \i A recursive macro will cause an endless loop that may be
// painful to detect and debug. \/i \/li \/ul
// For upward compatibility reasons (from release 1.0), CLAIRE still supports the use of external
// brackets around method definitions. The brackets are there to represent boxes around methods
// (and are pretty-printed as such with advanced printing tools). For instance, one can write :
// \code
// [mymin(l:list[integer]) : integer -> min(l, my_order)]
// \/code
// Brackets have been found useful by some users because one can search for the definition of the
// method m by looking for occurrences of '[mmm'. They also transform a method definition into a
// closed syntactical unit that may be easier to manipulate (e.g., cut-and-paste).\br
// When a new property is created, it is most often implicitly with the definition of a new method
// or a new slot, although a direct instantiation is possible. Each property has an extensibility
// status that may be one of :
// \ul
// \li open, which means that new restrictions may be added at any time. The compiler will
// generate the proper code so that extensibility is guaranteed.
// \li undefined, which is the default status under the interpreter, means that the status may
// evolve to open or to closed in the future.
// \li closed, which means that no new restriction may be added if it provokes an
// inheritance conflict with an existing restriction. An inheritance conflict in CLAIRE
// is properly defined by the non-empty intersection of the two domains (Cartesian products)
// of the methods.
// \/ul
// The compiler will automatically change the status from undefined to closed, unless the status
// is forced with the abstract declaration :
// \code
// abstract(p)
// \/code
// Conversely, the final declaration :
// \code
// final(p)
// \/code
// may be used to force the status to closed, in the interpreted mode. Note that these two
// declarations have obviously an impact on performance: an open property will be compiled with the
// systematic used of dynamic calls, which ensures the extensibility of the compiled code, but at a
// price. On the contrary, a final property will enable the compiler to use as much static binding as
// possible, yielding faster call executions. Notice that the interface(p) declaration has been
// introduced to support dynamic dispatch in a efficient manner, as long as the property is uniform.
// @cat





// @cat Types
// @section Methods and Types
// @alias type types
// CLAIRE uses an extended type system that is built on top of the set of classes.
// Like a class, a type denotes a set of objects, but it can be much more precise than a class.
// Since methods are attached to types (by their signature), this allows attaching methods to
// complex sets of objects.\br
// \def A (data) type is an expression that represents a set of objects.
// Types offer a finer-granularity partition of the object world than classes. They are used
// to describe objects (range of slots), variables and methods (through their signatures). An
// object that belongs to a type will always belong to the set represented by the type.
// \/def
// Any class (even parameterized) is a type. A parameterized class type is obtained by
// filtering a subset of the class parameters with other types to which the parameters must
// belong. For instance, we saw previously that complex[im:{0.0}] is a parametrized type that
// represent the real number subset of the complex number class. This also applies to typed lists
// or sets which use the of parameter. For instance, list[of:{integer}] is the set of list whose
// of parameter is precisely integer. Since these are common patterns, CLAIRE offers two shortcuts
// for parameterized type expressions. First, it accepts the expression C[p = v] as a shortcut for
// C[p:{v}]. Second, it accepts the expression C<X> as a shortcut for C[of = X]. This applies to any
// class with a type-valued parameter named of;
// Thus, stack<integer> is the set of stacks whose parameter "of" is exactly integer, whereas
// stack[of:subtype[integer]] is the set of stacks whose parameter (a type) is a subset of integer.\br
// Finite constant sets of objects can also be used as types. For example, {john, jack, mary} and
// {1,4,9} are types. Intervals can be used as types; the only kind of intervals supported by
// CLAIRE 3.0 is integer intervals. Types may also formed using the two intersection (^) and union (U)
// operations. For example, integer U float denotes the set of numbers and (1 .. 100) ^ (-2 .. 5)
// denotes the intersection of both integer intervals, i.e. (1 .. 5).\br
// Subtypes are also as type expressions. First, because types are also objects, CLAIRE introduces
// subtype[t] to represent the set of all type expressions that are included in t. This type can be
// intersected with any other type, but there are two cases which are more useful than other, namely
// subtypes of the list and set classes. Thus, CLAIRE uses set[t] as a shortcut for set ^ subtype[t]
// and list[t] as a shortcut for list ^ subtype[t]. Because of the semantics of lists, one may see
// that list[t] is the union of two kinds of lists :
// \ul
// \li "read-only" lists (i.e., without type) that contains objects of type t.
// \li typed list from list<X>, where X is a subtype of t.
// \/ul
// Therefore, there is a clear difference between
// \ul
// \li list<t>, which only contains types lists, whose type parameter (of) must be exactly t.
// \li list[t], which contains both typed lists and un-typed lists.
// \/ul
// Obviously, we have list<t> <= list[t]. When should you use one or the other form of
// typed lists or sets ?
// \ol
// \li use list[t] to type lists that will only be used by accessing their content. A
// method that uses l:list[t] in its signature will be polymorphic, but updates on l will
// rely on dynamic (run-time) typing. 
// \li use list<t> to type lists that need to be updated. A method that uses l:list<t> in
// its signature will be monomorphic (i.e., will not work for l:list<t'> with t' <= t), but
// updates will be statically type-checked (at compile time).
// \/ol
// Last, CLAIRE uses tuple and array types. The array type t[] represents arrays whose member
// type is t (i.e., all members of the array belong to t). Tuples are used to represent type of
// tuples in a very simple manner: tuple(t1,t2,...,tn) represents the set of tuples
// tuple(v1,v2, ... ,vn) such that vi belong to ti for all i in (1 .. n). For instance, tuple(integer, char)
// denotes the set of pair tuples with an integer as first element and a character as second. Also
// you will notice that tuple(class,any,type) belongs to itself, since class is a class and type is
// a type.\br
// Classes are sorted with the inheritance order. This order can be extended to types with the same
// intuitive meaning that a type t1 is a subtype of a type t2 if the set represented by t1 is a
// subset of that represented by t2. The relation "t1 is a subtype of a type t2" is noted t1 <= t2.
// This order supports the introduction of the " subtype " constructor: subtype[t] is the type of all
// types that are less than t.
// @cat



// @cat Polymorphism
// @section Methods and Types
// @alias polymorphism
// In addition to the traditional "objet-oriented" polymorphism, CLAIRE also offers two forms of
// parametric polymorphism, which can be skipped by a novice reader.\br
// \b (1) \/b There often exists a relation between the types of the arguments of a method.
// Capturing such a relation is made possible in CLAIRE through the notion of an
// "extended signature". For instance, if we want to define the operation "push" on a
// stack, we would like to check that the argument y that is being pushed on the stack s belongs
// to the type of(s), that we know to be a parameter of s. The value of this parameter can be
// introduced as a variable and reused for the typing of the remaining variables (or the range)
// as follows :
// \code
// push(s:stack<X>, y:X) -> (s.content :add y, s.index :+ 1)
// \/code
// The declaration s:stack<X> introduced X as a type variable with value s.of,
// since stack[of] was defined as a parameterized class. Using X in y:X simply means that
// y must belong to the type s.of. Such intermediate type variables must be free identifiers
// (the symbol is not used as the name of an object) and must be introduced with the following
// template :
// \code
// <class>[pi=vi, ...]
// \/code
// The use of type variables in the signature can be compared to pattern matching.
// The first step is to bind the type variable. If (p = V) is used in c[ ...] instead of p:t,
// it means that we do not put any restriction on the parameter p but that we want to bind its
// value to V for further use. Note that this is only interesting if the value of the parameter
// is a type itself. Once a type variable V is defined, it can be used to form a pattern
// (called a <type with var> in the CLAIRE syntax) as follows:\br
// \code
// <type with var> = <type> | <var> | {<var>} |
// 	tuple(<type with var>\sup seq+\/sup ) |
// 	<class>[< <var>:<type with var> | <var>=<var> >\sup seq+\/sup ]
// \/code
// \b (2) \/b The second advanced typing feature of CLAIRE is designed to capture the fine
// relationship between the type of the output result and the types of the input arguments.
// When such a relationship can be described with a CLAIRE expression e(x1,...,xn),
// where x1, ..., xn are the types of the input parameters, CLAIRE allows to substitute
// type[e] to the range declaration. It means that the result of the evaluation of the method
// should belong to e(t1,...,tn) for any types t1,...,tn that contain the input parameters.\br
// For instance, the identity function is known to return a result of the same type as its
// input argument (by definition !). Therefore, it can be described in CLAIRE as follows :
// \code
// id(x:any) : type[x] -> x
// \/code
// In the expression that we introduce with the type[e] construct, we can use the types of
// the input variables directly through the variables themselves. For instance, in the
// "type[x]" definition of the id example, the "x" refers to the type of the input variable.
// Notice that the types of the input variables are not uniquely defined. Therefore, the user
// must ensure that her "prediction" e of the output type is valid for any valid types t1, ..., tn
// of the input arguments.\br
// The expression e may use the extra type variables that were introduced earlier.
// For instance, we could define the "top" method for stacks as follows :
// \code
// top(s:stack<X>) : type[X] -> s.content[s.index]
// \/code
// The "second-order type" e (second-order means that we type the method, which is a
// function on objects, with another function on types) is built using the basic CLAIRE
// operators on types such as U, ^ and some useful operations such as "member". If c is a type,
// member(c) is the minimal type that contains all possible members of c. For instance,
// member({c}) = c by definition. This is useful to describe the range of the enumeration
// method set!. This method returns a set, whose members belong to the input class c by definition.
// Thus, we know that they must belong to the type member(X) for any type X to whom c belongs
// (cf. definition of member). This translates into the following CLAIRE definition :
// \code
// set!(c:class) : type[set[member(c)]] -> c.instances
// \/code
// For instance, if c belongs to subtype[B] then set!(c) belongs to set[B].\br
// To summarize, here is a more precise description of the syntax for defining a method :
// \code
// <function>(<vi>:<ti>\sup i E (1 .. n)\/sup ) : <range> -> <exp>
// \/code
// Each type ti for the variable vi is an "extended type" that may use type variables
// introduced by the previous extended types t1, t2 ... ti-1 . An extended type is
// defined as follows :
// \code
// <et> = <class> | <set> | <var> | (<et> ^ | U <et>) | (<integer> .. <integer>) |
// 	set[<et>] | list[<et>] | <et>[] | tuple(<et>\sup seq\/sup ) |
// 	<class>[< <var>:<et> | <var>=< <var> | <const> > >\sup seq+\/sup ]
// \/code
// The <range> expression is either a regular type or a "second order type",
// which is a CLAIRE expression e introduced with the type[e] syntactical construct :
// \code
// <range> = <type> | type[<expression>]
// \/code
// @cat




// @cat Escaping Types
// @section Methods and Types
// @alias escape escaped
// There are two ways to escape type checking in CLAIRE. The first one is casting, which means
// giving an explicit type to an expression. The syntax is quite explicit :
// \code
// <cast> = (<expression> as <type>)
// \/code
// This will tell the compiler that <expression> should be considered as having type <type>.
// Casting is ignored by the interpreter and should only be used as a compiler optimization.
// There is, however, one convenient exception to this rule, which is the casting into a list
// parametric type. When an untyped list is casted into a typed list, the value of its of
// parameter is actually modified by the interpreter, once the correct typing of all members
// has been verified. For instance, the two following expressions are equivalent :
// \code
// list<integer>(1,2,3,4)
// list(1,2,3,4) as list<integer>
// \/code
// The second type escaping mechanism is the non-polymorphic method call, where we tell what
// method we want to use by forcing the type of the first argument. This is equivalent to the
// supermessage passing facilities of many object-oriented languages.
// \code
// <super> = <selector>@<type>(<exp>seq)
// \/code
// The instruction f@c(...) will force CLAIRE to use the method that it would use for
// f(...) if the first argument was of type c (CLAIRE only checks that this first argument
// actually belongs to c).\br
// A language is type-safe if the compiler can use type inference to check all type constraints
// (ranges) at compile-time and ensure that there will be no type checking errors at run-time.
// CLAIRE is not type-safe because it admits expressions for which type inference is not possible
// such as read(p) + read(p). On the other hand, most expressions in CLAIRE may be statically
// type-checked and the CLAIRE compiler uses this property to generate code that is very similar
// to what would be produced with a C++ compiler. A major difference between CLAIRE 3.0 and earlier
// versions is the fact that lists may be explicitly typed, which removes the problems that could
// happen earlier with dynamic types. Lists and sets subtypes support inclusion polymorphism, which
// means that if A is a subtype of B, list[A] is a subtype of list[B];
// for instance list[(0 .. 1)] <= list[integer]. Thus only read operations can be statically
// type-checked w.r.t. such type information. On the other hand, array subtypes, as well as
// list or set parametric subtypes, are monomorphic, since A[] is not the set of arrays which
// contain members of A, but the set of arrays whose member type (the of slot) contains the
// value A. Thus if A is different from B, A[] is not comparable with B[], and list<A> is not
// comparable with list<B>. This enables the static type-checking of read and write operations on
// lists. The fact that CLAIRE supports all styles of type disciplines is granted by the combination
// of a rich dynamic type system coupled with a powerful type inference mechanism within the
// compiler, and is a key feature of CLAIRE.
// @cat



// @cat Selectors, Properties and Operations
// @section Methods and Types
// @alias selector property properties operation operations inverse inversion
// As we said previously, CLAIRE supports two syntaxes for using selectors, f(...) and
// (.... f ....). The choice only exists when the associated methods have exactly two arguments.
// The ability to be used with an infix syntax is attached to the property f :
// \code
// f :: operation()
// \/code
// Once f has been declared as an operation, CLAIRE will check that it is used as such
// subsequently. Restrictions of f can then be defined with the usual syntax :
// \code
// f(x:integer, y:integer) : ... 
// \/code
// Note that declaring f as an operation can only be done when no restriction of f is known.
// If the first appearance of f is in the declaration of a method, f is considered as a normal
// selector and its status cannot be changed thereafter. Each operation is an object (inherits
// from property) with a precedence slot that is used by the reader to produce the proper syntax
// tree from expressions without parentheses.
// \code
// gcd :: operation(precedence = precedence(/))
// 12 + 3 gcd 4 // same as 12 + (3 gcd 4)
// \/code
// So far we have assumed that any method definition is allowed, provided that inheritance
// conflict may cause warning. Once a property is compiled, CLAIRE uses a more restrictive
// approach since only new methods that have an empty intersection with existing methods (for
// a given property) are allowed. This allows the compiler to generate efficient code. It is
// possible to keep the "open" status of a property when it is compiled through the
// abstract declaration.
// \code
// abstract(f)
// \/code
// Such a statement will force CLAIRE to consider f as an "abstract" parameter of the program
// that can be changed at any time. In that case, any re-definition of f (any new method) will
// be allowed. When defining a property parameter, one should keep in mind that another user
// may redefine the behavior of the property freely in the future.\br
// It is sometimes useful to model a system with redundant information. This can be done by
// considering pairs of relations inverse one of another. In this case the system maintains the
// soundness of the database by propagating updates on one of the relations onto the other. For
// example if husband is a relation from the class man onto the class woman and wife a relation
// from woman to man, if moreover husband and wife have been declared inverse one of another,
// each modification (addition or retrieval of information) on the relation husband will be
// propagated onto wife. For example husband(mary) := john will automatically generate the update
// wife(john) := mary. Syntactically, relations are declared inverses one of another with
// the declaration :
// \code
// inverse(husband) := wife
// \/code
// This can be done for any relation: slots and tables. Inverses introduce an important distinction
// between multi-valued relations and mono-valued relations. A relation is multi-valued in CLAIRE
// when its range is a subset of bag (i.e. a set or a list). In that case the slot multivalued? of
// the relation is set to true and the set associated with an object x is supposed to be the set
// of values associated with x through the relation.\br
// This has the following impact on inversion. If r and s are two mono-valued relations inverse one
// of another, we have the following equivalence :
// \code
// s(x) = y <=> r(y) = x
// \/code
// In addition, the range of r needs to be included in the domain of s and conversely. The
// meaning of inversion is different if r is multi-valued since the inverse declaration now means :
// \code
// s(x) = y <=> x E r(y)
// \/code
// Two multi-valued relations can indeed be declared inverses one of another. For example, if
// parents and children are two relations from person to set[person] and if inverse(children) =
// parents, then :
// \code
// children(x) = {y in person | x % parents(y)}
// \/code
// Modifications to the inverse relation are triggered by updates (with :=) and creations of
// objects (with filled slots). Since the explicit inverse of a relation is activated only upon
// modifications to the database (it is not retroactive), one should always set the declaration
// of an inverse as soon as the relation itself is declared, before the relation is applied on
// objects. This will ensure the soundness of the database. To escape the triggering of updates
// to inverse relations, the solution is to fill the relation with the method put instead of :=.
// For example, the following declaration :
// \code
// let john := person() in (put(wife,john,mary), john)
// \/code
// does the same as :
// \code
// john :: person(wife = mary)
// \/code
// without triggering the update husband(mary) := john.
// @cat




// @cat Iterations
// @section Methods and Types
// @alias iterate iterations
// We just saw that CLAIRE will produce in-line substitution for some methods. This is
// especially powerful when combined with parametric function calls (using call(...))
// taking advantage of the fact that CLAIRE is a functional language. There is another
// form of code substitution supported by CLAIRE that is also extremely useful, namely
// the iteration of set data structure.\br
// Any object s that understands the set! method can be iterated over. That means that
// the construction for x in s e(x) can be used. The actual iteration over the set
// represented by s is done by constructing explicitly the set extension. However,
// there often exists a way to iterate the set structure without constructing the set
// extension. The simplest example is the integer interval structure that is iterated
// with a while loop and a counter.\br
// It is possible to define iteration in CLAIRE through code substitution. This is done
// by defining a new inline restriction of the property iterate, with signature
// (x:X,v:Variable,e:any). The principle is that CLAIRE will replace any occurrence of
// (for v in x e) by the body of the inline method as soon as the type of the expression
// x matches with X (v is assumed to be a free variable in the expression e). For instance,
// here is the definition of iterate over integer intervals :
// \code
// iterate(x:interval[min:integer,max:integer],v:Variable,e:any) =>
// 	let v := min(x), %max := max(x)
// 	in (while (v <= %max) (e, v :+ 1))
// \/code
// Here is a more interesting example. We can define hash tables as follows. A table is
// defined with a list (of size 2n - 3, which is the largest size for which a chunk of size
// 2n is allocated), which is full of "unknown" except for these objects that belong to the
// set. Each object is inserted at the next available place in the table, starting at a point
// given by the hashing function (a generic hashing function provided by CLAIRE: hash) :
// \code
// htable <: object(count:integer = 0,
// 				index:integer = 4,
// 				arg:list<any> = list<any>())
//
// set!(x:htable) : set -> {y in x.arg | known?(y)}
//
// insert(x:htable, y:any) ->
// 	let l := x.arg
// 	in (if (x.count >= length(l) / 2)
// 		(x.arg := make_list(^2(x.index - 3), unknown),
// 		x.index :+ 1, x.count := 0,
// 		for z in {y in l | known?(y)} insert(x,z),
// 			insert(x,y))
// 	else let i := hash(l,y)
// 		in (until (l[i] = unknown | l[i] = y)
// 				(if (i = length(l)) i := 1 else i :+ 1),
// 				if (l[i] = unknown)
// 					(x.count :+ 1, l[i] := y)))
// \/code
// Note that CLAIRE provides a few other functions for hashing that would allow an even
// simpler, though less self-contained, solution. To iterate over such hash tables without
// computing set!(x) we define :
// \code
// iterate(s:htable, v:Variable, e:any)
// 	=> (for v in s.arg (if known?(v) e))
// \/code
// Thus, CLAIRE will replace :
// \code
// let s:htable := ... in sum(s)
// \/code
// by :
// \code
// let s:htable := ... in
// 	(let x := 0
// 	in (for v in s.arg
// 		(if known?(v) x :+ v),
// 		x))
// \/code
// The use of iterate will only be taken into account in the compiled code unless one uses
// oload, which calls the optimizer for each new method. iterate is a convenient way to
// extend the set of CLAIRE data structure that represent sets with the optimal efficiency.
// Notice that, for a compiled program, we could have defined set! as follows (this definition
// would be valid for any new type of set) :
// \code
// set!(s:htable) -> {x | x in s}
// \/code
// When defining a restriction of iterate, one must not forget the handling of values
// returned by a break statement. In most cases, the code produce by iterate is itself a loop
// (a for or a while), thus this handling is implicit. However, there may be multiples loops,
// or the final value may be distinct from the loop itself, in which case an explicit handling
// is necessary. Here is an example taken from class iteration :
// \code
// iterate(x:class, v:Variable, e:any) : any
// 	=> (for %v_1 in x.descendents
// 		let %v_2 := (for v in %v_1.instances e) // catch inner break
// 		in (if %v_2 break(%v_2)))  // transmit the value
// \/code
// Notice that it is always possible to introduce a loop to handle breaks if none are present;
// we may replace the expression e by :
// \code
// while true (e, break(nil))
// \/code
// Last, we need to address the issue of parametric polymorphism, or how to define new kinds
// of type sets. The previous example of hash-sets is incomplete, because it only describes
// generic hash-sets that may contain any element. If we want to introduce typed hash-sets,
// we need to follow these three steps. First we add a type parameter to the htable class :
// \code
// htable[of] <: object(of:type = any, count:integer = 0, ...)
// \/code
// Second, we use a parametric signature to use the type parameter appropriately :
// \code
// insert(x:htable<X>, y:X) -> ...
// \/code
// Last, we need to tell the compiler that an instance from htable[X] only contains
// objects from X. This is accomplished by extending the member function which is used by
// the compiler to find a valid type for all members of a given set. If x is a type,
// member(x) is a valid type for any y that will belong to a set s of type x. If T is a
// new type of sets, we may introduce a method member(x :T, t :type) that tells how to
// compute member(t) if t is included in T. For instance, here is a valid definition for
// our htable example :
// \code
// member(x:htable,t:type) -> member(t @ of)
// \/code
// This last part may be difficult to grasp (do not worry, this is an advanced feature).
// First, recall that if t is a type and p a property, (t @ p) is a valid type for x.p
// when x is of type t. Suppose that we now have an expression e, with type t1, that
// represents a htable (thus t1 <= htable). When the compiler calls member(t1), the previous
// method is invoked (x is bound to a system-dependent value that should not be used and t is
// bound to t1). The first step is to compute (t1 @ of), which is a type that contains all
// possible values for y.of, where y is a possible result of evaluating e. Thus,
// member(t1 @ of) is a type that contains all possible values of y, since they must belong
// to y.of by construction. This type is, therefore, used by the compiler as the type of the
// element variable v inside the loop generated by iterate.
// @cat




// @cat Tables
// @section Tables, Rules and Hypothetical Reasoning
// @alias table tables 
// Named arrays, called tables, can be defined in CLAIRE with the following syntax :
// \code
// <name>[var:<domain>] : <type> := <expression(var)>
// \/code
// The <type> is the range of the table and <expression> is an expression that is used to
// fill the table. This expression may either be a constant or a function of the variables
// of the table (i.e., an expression in which the variables appear). If the expression is a
// constant, it is implicitly considered as a default value, the domain of the table may thus
// be infinite. If the default expression is a function, then the table is filled when it is
// created, so the domain needs to be finite. When one wants to represent incomplete information,
// one should fill this spot with the value unknown. For instance, we can define :
// \code
// square[x:(0 .. 20)] : integer := (x * x)
// creator[x:class] : string := "who created that class"
// maximum[x:set[0 .. 10]] : integer := (if x min(x,> @ integer) else 0)
// \/code
// Tables can be accessed through square brackets and can be modified with assignment expressions
// like for local variables :
// \code
// square[1], square[2] := 4, square[4] :+ 5
// \/code
// We can also define two-dimensional tables such as :
// \code
// distance[x:tuple(city,city)] : integer := 0
// cost[x:tuple(1 .. 10, 1 .. 10)] : integer := 0
// \/code
// The proper way to use such a table is distance[list(denver,miami)] but CLAIRE also supports
// distance[denver,miami]. CLAIRE also supports a more straightforward declaration such as :
// \code
// cost[x:(1 .. 10), y:(1 .. 10)] : integer := 0
// \/code
// Last, tables can be defined in an unamed fashion through the method make_table, such unamed
// can be collected by the GC :
// \code
// let square := make_table((1 .. 10), integer, 0)
// in (for n in (1 .. 10))
// 		square[n] := n * n,
// 	...)
// \/code
// @cat





// @cat Rules
// @section Tables, Rules and Hypothetical Reasoning
// @alias rule rules
// A rule in CLAIRE is made by associating an event condition to an expression.
// The rule is attached to a set of free variables of given types: each time that an event
// that matches the condition becomes occurs for a given binding of the variables (i.e.,
// association of one value to each variable), the expression will be evaluated with this
// binding. The interest of rules is to attach an expression not to a functional call (as
// with methods) but to an event, with a binding that is more flexible (many rules can be
// combined for one event) and more incremental.
// \def
// A rule is an object that binds a condition to an action, called its conclusion. Each time
// the condition becomes true for a set of objects because of a new event, the conclusion is
// executed. The condition is expressed as a logic formula on one or more free variables that
// represent objects to which the rule applies. The conclusion is a CLAIRE expression that uses
// the same free variables. An event is an update on these objects, either the change of a slot or
// a table value, or the instantiation of a class. A rule condition is checked if and only if an
// event has occurred.
// \/def
// A novelty in CLAIRE 3.0 is the introduction of event logic. There are two events that can be
// matched precisely: the update of a slot or a table, and the instantiation of a class. CLAIRE
// 3.2 use expressions called event pattern to specify which kind of events the rule is associated
// with. For instance, the expression x.r := y is an event expression that says both that x.r = y
// and that the last event is actually the update of x.r from a previous value. More precisely,
// here are the events that are supported :
// \ul
// \li x.r := y, where r is a slot of x.
// \li a[x] := y, where a is a.
// \li x.r :add y, where r is a multi-valued slot of x (with range bag).
// \li a[x] :add y, where a is a multi-valued table.
// \/ul
// Note that an update of the type x.r :delete y (resp. a[x] :delete y), where r is a slot of x
// (resp. a is a table), will never be considered as an event if r is multi-valued. However, one
// can always replace this declaration by x.r := delete(x.r, y) which is an event, but which costs
// a memory allocation for the creation of the new x.r.\br
// In addition, a new event pattern was introduced in CLAIRE 3.0 to capture the transition from
// an old to a new value. This is achieved with the expression x.r := (z <- y) which says that
// the last event is the update of x.r from z to y. For instance, here is the event expression
// that states that x.salary crossed the 100000 limit :
// \code
// x.salary := (y <- z) & y < 100000 & z >= 100000
// \/code
// In CLAIRE 3.2 we introduce the notion of a "pure" event. If a property p has no restrictions,
// then p(x,y) represents a virtual call to p with parameters x and y. This event may be used in
// a rule in a way similar to x.p := y, with the difference that it does not correspond to an
// update. Virtual events are very generic since one of the parameter may be arbitrarily complex
// (a list, a set, a tuple ...). The event filter associated to a virtual event is simply the
// expression "p(x,y)". To create such an event, one simply calls p(x,y), once a rule using such
// an event has been defined. As a matter of fact, the definition of a rule using p(x,y) as an
// event pattern will provoke the creation of a generic method p that creates the event.\br
// Virtual event may be used for many purposes. The creation of a virtual event requires no
// time nor memory; thus, it is a convenient technique to capture state transition in your
// object system. For instance, we can create an event signaling the instantiation of a class
// as follows :
// \code
// instantiation :: property(domain = myClass, range = string)
//
// [close(x:MyClass) : MyClass -> instantiation(x,date!(1)), x]
//
// controlRule() :: rule(instantiation(x,s) => printf("--- create ~S at ~A \n",x,s))
// \/code
// To define a rule, we must indeed define :
// \ul
// \li a condition, which is the combination of an event pattern and a CLAIRE Boolean expression using the same variables
// \li a conclusion that is preceded by =>.
// \/ul
// Here is a classical transitive closure example :
// \code
// r1() :: rule(x.friends :add y => for z in y.friend x.friends :add z)
// \/code
// Rules are named (for easier debugging) and can use any CLAIRE expression as a conclusion,
// using the event parameters as variables. Rule triggering can be traced using trace(if_write).
// Notice that a rule definition in CLAIRE 3.2 has no parameters; rules
// with parameters require the presence of the ClaireRules library, which is no longer available.\br
// For instance, let us define the following rule to fill the table fib with the Fibonacci sequence :
// \code
// r3() :: rule(y := fib[x] & x % (0 .. 100)
// 		=> when z := get(fib,x - 1) in fib[x + 1] := y + z)
//
// (fib[0] := 1, fib[1] := 1)
// \/code
// @cat





// @cat Hypothetical Reasoning
// @section Tables, Rules and Hypothetical Reasoning
// @alias hypothetical reasoning versioning world worlds
// In addition to rules, CLAIRE also provides the ability to do some hypothetical reasoning.
// It is indeed possible to make hypotheses on part of the knowledge (the database of relations)
// of CLAIRE, and to change them whenever we come to a dead-end. This possibility to store
// successive versions of the database and to come back to a previous one is called the world
// mechanism (each version is called a world). The slots or tables x on which hypothetical
// reasoning will be done need to be specified with the declaration store(x). For instance :
// \code
// store(age,friends,fib) <=> store(age), store(friends), store(fib)
// \/code
// Each time we ask CLAIRE to create a new world, CLAIRE saves the status of tables and slots
// declared with the store command. Worlds are represented with numbers, and creating a new world
// is done with choice(). Returning to the previous world is done with backtrack(). Returning to
// a previous world n is done with backtrack(n). Worlds are organized into a stack (sorry, you
// cannot explore two worlds at the same time) so that save/restore operations are very fast.
// The current world that is being used can be found with world?(), which returns an integer.
// \def A world is a virtual copy of the defeasible part of the object database. The object
// database (set of slots, tables and global variables) is divided into the defeasible part and
// the stable part using the store declaration. Defeasible means that updates performed to a
// defeasible relation or variable can be undone later; r is defeasible if store(r) has been
// declared. Creating a world (choice) means storing the current status of the defeasible
// database (a delta-storage using the previous world as a reference). Returning to the
// previous world (backtrack) is just restoring the defeasible database to its previously
// stored state.
// \/def
// In addition, you may accept the hypothetical changes that you made within a world while
// removing the world and keeping the changes. This is done with the commit methods.
// commit() decreases the world counter by one, while keeping the updates that were made
// in the current world. It can be seen as a collapse of the current world and the previous
// world. commit(n) repeats commit() until the current world is n. Notice that this
// "collapse" will simply make the updates that were made in the current world (n) look like
// they were made in the previous world (n - 1); thus, these updates are still defeasible.\br
// Defeasible updates are fairly optimized in CLAIRE, with an emphasis on minimal book-keeping
// to ensure better performance. Roughly speaking, CLAIRE stores a pair of pointers for each
// defeasible update in the world stack. There are (rare) cases where it may be interesting to
// record more information to avoid overloading the trailing stack. For instance, trailing
// information is added to the stack for each update even if the current world has not changed.
// This strategy is actually faster than using a more sophisticated book-keeping, but may yield
// a world stack overflow.\br
// For instance, here is a simple program that solves the n queens problem
// (the problem is the following: how many queens can one place on a chessboard so that none are
// in situation of chess, given that a queen can move vertically, horizontally and diagonally
// in both ways ?) :
// \code
// column[n:(1 .. 8)] : (1 .. 8) := unknown
// possible[x:(1 .. 8), y:(1 .. 8)] : boolean := true
// store(column, possible)
//
// r1() :: rule(column[x] := z
// 			=> for y in ((1 .. 8) but x) possible[y,z] := false)
// r2() :: rule(column[x] := z
// 			=> let d := x + z
// 				in for y in (max(1,d - 8) .. min(d - 1, 8))
// 					possible[y,d - y] := false )
// r3() :: rule(column[x] := z
// 			=> let d := z - x
// 				in for y in (max(1,1 - d) .. min(8,8 - d))
// 					possible[y,y + d] := false)
//
// queens(n:(0 .. 8)) : boolean
// 	-> (if (n = 0) true
// 		else exists(p in (1 .. 8) | (possible[n,p] &
// 					branch((column[n] := p, queens(n - 1))))))
//
// (queens(8))
// \/code
// In this program queens(n) returns true if it is possible to place n queens.
// Obviously there can be at most one queen per line, so the purpose is to find a
// column for each queen in each line : this is represented by the column table. So,
// we have eight levels of decision in this problem (finding a line for each of the
// eight queens). The search tree (these imbricated choices) is represented by
// the stack of the recursive calls to the method queens. At each level of the
// tree, each time a decision is made (an affectation to the table column), a new world
// is created, so that we can backtrack (go back to previous decision level) if this
// hypothesis (this branch of the tree) leads to a failure.\br
// Note that the table possible, which tells us whether the n\sup th \/sup queen can be set on the p\sup th \/sup 
// line, is filled by means of rules triggered by column (declared event) and that both
// possible and column are declared store so that the decisions taken in worlds that have been
// left are undone (this avoids to keep track of decisions taken under hypotheses that have
// been dismissed since).\br
// Updates on lists can also be "stored" on worlds so that they become defeasible.
// Instead of using the nth= method, one can use the method store(l,x,v,b) that places
// the value v in l[x] and stores the update if b is true. In this case, a return to a
// previous world will restore the previous value of l[x]. If the boolean value is always true,
// the shorter form store(l,x,y) may be used. Here is a typical use of store :
// \code
// store(l,n,y,l[n] != y)
// \/code
// This is often necessary for tables with range list or set. For instance, consider the
// following :
// \code
// A[i:(1 .. 10)] : tuple(integer,integer,integer) := list<integer>(0,0,0)
// (let l := A[x]
// in (l[1] := 3, l[3] := 3))
// \/code
// even if store(A) is declared, the manipulation on l will not be recorded by the world
// mechanism. You would need to write :
// \code
// A[x] := list(3, A[x][2], 3)
// \/code
// Using store, you can use the original (and more space-efficient) pattern and write :
// \code
// (let l := A[x]
// in (store(l,1,3), store(l,3,3)))
// \/code
// There is another problem with the previous definition. The expression given as a default
// in a table definition is evaluated only once and the value is stored. Thus the same
// list<integer>(0,0,0) will be used for all A[x]. In this case, which is a default value
// that will support side-effects, it is better to introduce an explicit initialization of the table :
// \code
// (for i in (1 .. 10) A[i] := list<integer>(0,0,0))
// \/code
// There are two operations that are supported in a defeasible manner: direct replacement of the
// i\sup th\/sup element of l with y (using store(l,i,y)) and adding a new element at the end
// of the list (using store(l,y)). All other operations, such as nth+ or nth- are not defeasible.
// The addition of a new element is interesting because it either returns a new list or perform a
// defeasible side-effect. Therefore, one must also make sure that the assignment of the value of
// store(l,x) is also made in a defeasible manner (e.g., placing the value in a defeasible global
// variable). To perform an operation like nth+ or delete on a list in a defeasible manner, one
// usually needs to use an explicit copy (to protect the original list) and store the result using
// a defeasible update (cf. the second update in the next example).\br
// It is also important to notice that the management of defeasible updates is done at the
// relation level and not the object level. Suppose that we have the following :
// \code
// C1 <: object(a:list<any>, b:integer)
// C2 <: thing(c:C1)
// store(c,a)
// P :: C1()
// P.c := C2(a = list<any>(1,2,3) , b = 0) // defeasible but the C2 object remains
// P.c.a := delete(copy(P.c.a), 2) // this is defeasible
// P.c.b := 2  // not defeasible
// \/code
// The first two updates are defeasible but the third is not, because store(b) has not been declared.
// It is also possible to make a defeasible update on a regular property using put_store. It is worth
// noticing that hypothetical reasoning.
// @cat



// @cat @xl Communication ports
// @section I/O, Modules and System Interface
// @alias port ports socket sockets file files descriptor descriptors buffer buffers blob blobs
// In XL CLAIRE, the entire port interface has been rewritten such port is now the root class for an
// extensible hierarchy of communication interface (In CLAIRE 3, ports are based on a C++ import).
// We define two sorts of port :
// \def A device is a communication port that is connected to a physical port like a file or a
// socket that can be handled through a chain of filter \/def 
// \def
// A filter is a communication port that may modify, buffer or look at a data read or
// written from a device.
// \/def
// Given this sorts, we define the descriptor device as a wrapper for UNIX descriptor which handles
// read, write (read_port and write_port interface) and close (close_port interface)
// operations in a unified way for each derived class (disk_file, socket, pipe).
// At startup, 3 global variables named stdin, stdout and stderr are created to hold
// the standard input, output, and error devices respectively (UNIX descriptors 0,1,2 on most
// system).\br
// Languages often provide these standard ports in a buffered way, that is system calls read(2) or
// write(2) are made by chunks. So XL CLAIRE comes with two kind of filter, the buffer (as created
// by buffer!) that perform read (or
// write) once for each read (or written) chunk of a given size and the line_buffer (as created by
// line_buffer!) that perform write calls once for each written line.
// Depending on how the program was launched, the standard output may be a terminal or something
// else (e.g. pipe). In the later case we'll always provide stdout as a buffer but when it is found
// that the output is a terminal device, which is often shared by multiple processes, we'll provide
// stdout as a line_buffer. On the other hand the standard error port is always provided unbuffered,
// such that in case of crash we avoid data miss that could be hold by a buffer.\br
// To avoid problems of synchronization between reading and writing, it is sometimes useful to
// ensure that the buffer of a given port is empty. This is done by the command flush(p:port).
// flush(p) will perform all printing instructions for the port p that are waiting
// in the associated buffer (flush_port interface).\br
// A (buffered) file is opened with fopen(s:string,m:string) where s is the file path and m
// the opening mode ("r": read, "w": write, "a": append). For instance :
// \code
// inefficient_show_size(filepath:string) : void ->
// 	let f := fopen(filepath, "r"),
// 		content := fread(f)
// 	in printf("File ~A has ~S bytes\n", filepath, length(content))
// \/code
// An other provided interface is the ability to make a port from a string and vice versa. In XL
// CLAIRE we call that blob (based on device), the internal data representing the string is a chunk
// of memory allocated dynamically outside CLAIRE memory (CLAIRE 3 port! interface is supported for
// compatibility). Blob can be made in various ways with blob! including blob!(s:string) that would
// initialize the internal data with the string s :
// \code
// let b := blob!("toto")
// in assert(fread(b) = "toto")
//
// let b := blob!()
// in (fwrite("toto",b),
// 	assert(fread(b) = "toto"))
// \/code
// @cat




// @cat Printing
// @section I/O, Modules and System Interface
// There are several ways of printing in CLAIRE. Any entity may be printed with the
// function print. When print is called for an object that does not inherit from thing
// (an object without a name), it calls the method self_print of which you can define new
// restrictions whenever you define new classes. If self_print was called on an object x
// owned by a class toto for which no applicable restriction could be found,
// it would print <toto>.\br
// In the case of bags (sets or lists), strings, symbols or characters, the standard method
// is princ. It formats its argument in a somewhat nicer way than print. For example :
// \code
// print("john") prints "john"
// princ("john") prints john
// \/code
// Finally, there also exists a printf macro as in C. Its first argument is a string with
// possible occurrences of the control patterns ~S, ~I and ~A. The macro requires as many
// arguments as there are "tilde patterns" in the string, and pairs in order of appearance
// arguments together with tildes. These control patterns do not refer to the type of the
// corresponding argument but to the way you want it to be printed. The macro will call print
// for each argument associated with a ~S form, princ for each associated with a ~A form and
// will print the result of the evaluation of the argument for each ~I form. A mnemonic is A
// for alphanumeric, S for standard and I for instruction. Hence the command :
// \code
// printf("~S is ~A and here is what we know\n ~I", john, 23, show(john))
// \/code
// will be expanded into :
// \code
// (print(john), princ(" is "), princ(23),
// 	princ(" and here is what we know\n"),
// 		show(john))
// \/code
// Output may also be directed to a file or another device instead of the screen, using a port.
// A port is an object bound to a physical device, a memory buffer or a file. The method
// use_as_output is meant to select the port on which the output will be written. Following
// is an example :
// \code
// let p := fopen("agenda-2006", "w")
// in (use_as_output(p),
// 	write(agenda), fclose(p))
// \/code
// \xl In XL CLAIRE printf construction can take a port argument and would perform a local
// output rediction to the supplied port :
// \code
// printf(my_port, "~S is ~A and here is what we know\n ~I", john, 23, show(john))
// \/code
// will be expanded into :
// \code
// let old := use_as_output(my_port)
// in (print(john), princ(" is "), princ(23),
// 	princ(" and here is what we know\n"), show(john),
//  use_as_output(old))
// \/code
// CLAIRE also offers a simple method to redirect the output towards a string port. Two
// methods are needed to do this: print_in_string and end_of_string. print_in_string() starts
// redirecting all printing statements towards the string being built. end_of_string() returns
// the string formed by all the printing done between these two instructions. You can only use
// print_in_string with one output string at a time; more complex uses require the creation of
// multiple string ports.\br
// All trace statements will be directed to this port. A trace statement is either obtained
// implicitly through tracing a method or a rule, or explicitly with the trace statement.
// the statement trace(n, <string>, <args> ...) is equivalent to printf(<string>, <args> ..)
// with two differences: the string is printed only if the verbosity level verbose() is
// higher than n and the output port is ctrace(). The following lines are equivalent :
// \code
// trace(0, "assigning ~S with ~S", x, y)
// //[0] assigning ~S with ~S // x, y
// (if (verbose() >= 0) printf(ctrace(), "assigning ~S with ~S", x, y))
// \/code
// \xl In XL CLAIRE however, trace instructions are bound to a module such one can specify a
// per module verbose policy : a module m has a slot m.verbose that can take the values :
// \ul
// \li true (default) that tell that each trace of the module follows the system policy
// \li false tells that traces of m won't be issued
// \li an integer n would set the verbose level n for m only
// \li an interval of two integer that define a range of allowed levels for m only
// \/ul
// @cat


// @xl @cat WCL syntax
// @alias wcl
// @section I/O, Modules and System Interface
// XL CLAIRE comes with a new printing facility called WCL syntax standing for Web
// CLaire syntax due to its design originally meant for web oriented applications with
// generation of dynamic content.
// WCL syntax draws its inspiration from HTML and the ability to embed CLAIRE code
// in such language. It comes as a printing alternative to printf and also perform
// inline substitution.
// For instance, here is a simple WCL fragment and its printf equivalent :
// \code
// ?>Hello world<? <=> printf("Hello world")
// \/code
// A WCL fragment is introduced with the keyword \i ?>\/i  which is the beginning of a static
// string terminated by the corresponding keyword \i <?\/i  substituted at read time by a call
// to princ. As a convenience a WCL fragment may not be delimited with a
// coma as shown in the following equivalent forms :
// \code
// ?>toto<? princ("titi") ?>tata<?
// ?>toto<? , princ("titi"), ?>tata<?
// ?>toto<? princ("titi"), ?>tata<?
// ?>toto<? , princ("titi") ?>tata<?
// princ("tototititata")
// \/code
// As in a printf construction a WCL fragment can invoke a method take an argument, this is
// achieved by postfixing the selector of the call to the \i <?\/i  keyword as in :
// \code
// ?>toto<?princ "titi" <=> princ("tototiti")
// \/code
// As a notation shortcut, three special forms are allowed for the postfixed selector :
// \code
// ?>toto<?= <exp> <=> princ("toto"), echo(<exp>)
// ?>toto<?== <exp> <=> princ("toto"), self_html(<exp>)
// ?>toto<?oid <exp> <=> princ("toto"), princ(Core/Oid(<exp>))
// \/code
// Where echo and self_html and both extensible. The last form (oid) may be used to
// produce a unique printed value for the given expression <exp>. By default echo behave
// like princ for primitive objects (integers, floats, chars and strings) and self_print
// for other objects. self_html behave like echo but also perform conversion for special
// HTML entities :
// \ul
// \li '<' is printed as '&lt;'
// \li '>' is printed as '&gt;'
// \li ' ' (space) is printed as '&nbsp;'
// \li '&' is printed as '&amp;'
// \/ul
// As a summary, a WCL fragment as the following syntax :
// \code
// <wcl fragment> = < ?> <text> <? < <= | == | oid | property> <exp> >\sup opt\/sup  >
// \/code
// As a last sample here is a code that would generate an HTML table with 10 rows and ten columns
// where each cell contains its coordinates in the table :
// \code
// ?><table><?
// 	for y in (1 .. 10)
// 		( ?><tr><?
// 			for x in (1 .. 10) ( ?><td><?= x ?>,<?= y))
// ?></table><?
// \/code
// @cat




// @cat Reading
// @section I/O, Modules and System Interface
// Files can be read one expression at a time : read(p:port) reads the next CLAIRE expression
// on the port p or, in a single step, load(s:string) reads the file associated to the
// string s and evaluates it. It returns true when no problem occurred while loading the
// file and false otherwise. A variant of this method is the method sload(s:string) which
// does the same thing but prints the expression read and the result of their evaluation.
// Another variant is the method oload(s:string) which does the same thing but substitute
// an optimized form to each method's body. This may hinder the inspection of the code at the
// toplevel, but it will increase the efficiency of the interpreter.\br
// Files may contain comments. A comment is anything that follows a // until the end of
// the line. When reading, the CLAIRE reader will ignore comments (they will not be read
// and hence not evaluated). For instance :
// \code
// x :+ 1, // increments x by 1
// \/code
// To insure compatibility with earlier versions, CLAIRE also recognizes lines that begin with ';'
// as comments. Conversely, CLAIRE also support the C syntax for block comments: anything between
// /* and */ will be taken as a comment. Comments in CLAIRE may become active comments that behave
// like trace statements if they begin with [<level>] (see appendix B). The global variable
// NeedComment may be turned to true (it is false by default) to tell the reader to place any comment
// found before the definition of a class or a method in the comment slot of the associated CLAIRE
// object.\br
// The second type of special instructions are immediate conditionals. An immediate conditional
// is defined with the same syntax as a regular conditional but with a #if instead of an if :
// \code
// #if <test> <expression>
// 	< else <expression> >\sup opt \/sup
// \/code
// When the reader finds such an expression, it evaluates the test. If the value is true, then
// the reader behaves as if it had read the first expression, otherwise it behaves as if it had
// read the second expression (or nothing if there is no else). This is useful for implementing
// variants (such as debugging versions). For instance :\br
// \code
// #if debug printf("the value of x is ~S", x)
// \/code
// Note that the expression can be a block (within parentheses) which is necessary to place a
// definition (like a rule definition) inside a #if. Last, there exists another pre-processing
// directive for loading a file within a file: #include(s) loads the file as if it was included
// in the file in which the #include is read.\br
// There are a few differences between CLAIRE and C++ or Java parsing that need to be underlined :
// \ul
// \li Spaces are important since they act as a delimiter. In particular, a space cannot be inserted
// between a selector and its arguments in a call. Here is a simple example :
// \code
// foo (1,2,3) // this is not correct, one must write foo(1,2,3)
// \/code
// \li = is for equality and := for assignment. This is standard in pseudo-code notations because
// it is less ambiguous
// \li characters such as +, *, -, etc. do not have a special status. This allows the user to
// use them in a variable name (such as x+y). However, this is not advisable since it is
// ambiguous for many readers. A consequence is that spaces are needed around operations within
// arithmetic examples such as :
// \code
// x + (y * z) // instead of x+y*z which is taken as (one) variable name
// \/code
// \li The character '/' plays a special role for namespace (module) membership
// \/ul
// @cat






// @cat Symbols
// @section I/O, Modules and System Interface
// @alias identifier identifiers symbol symbols
// Identifiers are represented in CLAIRE with entities called symbols. Each identifier is
// represented by a symbol. A symbol is defined by a namespace (where the identifier belongs),
// a name (the sequence of character from the unqualified symbol) and a status. The status of a
// symbol is either private or export (the default status). When the status of an identifier is
// private, the reader will not recognize the qualified form from a module that is not a sub-module
// of that of the identifier. Therefore, the only way to read the identifier is inside its own
// namespace. When the status of the identifier is export, the qualified form gives access to the
// designated object, if the sharing declarations of namespaces have been properly set.\br
// Each symbol may be bound to the object that it designates. The object becomes the value of the
// symbol. The name of the object must be the symbol itself. In addition, the symbol collects another
// piece of useful information: the module where its value (the named object) is defined. If the
// symbol is defined locally (through a private or export definition), this definition module is
// the same as the owner of the symbol itself. If the symbol is shared (if it was defined as an
// identifier of an above module), this module is a subpart of the owner of the symbol.\br
// CLAIRE now supports a simple syntax for creating symbols directly, in addition to the various
// methods provided in the API. Symbols can be entered in the same way that they are printed, by
// indicating the module (namespace) to which the symbol belongs and the associated string,
// separated by a '/' :
// \code
// <claire symbol> = <module>/<string>
// \/code
// @cat

// @cat Modules
// @section I/O, Modules and System Interface
// @alias module modules
// Organizing software into modules is a key aspect of software engineering : modules
// separate different features as well as different levels of abstraction for a given task.
// To avoid messy designs and to encourage modular programming, programs can be structured into
// modules, which all have their own identifiers and may hide them to other modules. A module is
// thus a namespace that can be visible or hidden for other modules. CLAIRE supports multiple
// namespaces, organized into a hierarchy similar to the unix file system. The root of the
// hierarchy is the module CLAIRE, which is implicit. A module is defined as a usual CLAIRE
// object with two important slots: part_of which contains the name of the father module, and
// a slot uses which gives the list of all modules that can be used inside the new module. For
// instance :
// \code
// interface :: module(part_of = library, uses = list(claire))
// \/code
// defines interface as a new sub-module to the library module that uses the module claire
// (which implies using all the modules). All module names belong to the claire namespace
// (they are shared) for the sake of simplicity.
// \def A module is a CLAIRE object that represents a namespace. A namespace is a set of identifiers :
// each identifier (a symbol representing the name of an object) belongs to one unique namespace,
// but is visible in many namespaces. Namespaces allow the use of the same name for two different
// objects in two different modules. Modules are organized into a visibility hierarchy so that each
// symbol defined in a module m is visible in modules that are children of m.
// \/def
// Identifiers always belong to the namespace in which they are created (claire by default).
// The instruction module!() returns the module currently opened. To change to a new module, one may
// use begin(m:module) and end(m:module). The instruction begin(m) makes m the current module.
// Each newly created identifier (symbol) will belong to the module m, until end(m) resumes to the
// original module. For instance, we may define :
// \code
// begin(interface)
// window <: object(...)
// end(interface)
// \/code
// This creates the identifier interface/window. Each identifier needs to be preceded by its module,
// unless it belongs to the current module or one of its descendent, or unless it is private
// (cf. visibility rules). We call the short form "window" the unqualified identifier and the long
// one "interface/window" the qualified identifier.\br
// The visibility rules among name spaces are as follows :
// \ul
// \li unqualified identifiers are visible if and only if they belong to a descendent of the
// current module
// \li all qualified identifiers that are private are not visible
// \li other qualified identifiers are visible everywhere, but the compiler will complain if their
// module of origin does not belong to the list of allowed modules of the current modules
// \/ul
// Any identifier can be made private when it is defined by prefixing it with private/. For instance,
// we could have written :
// \code
// begin(interface)
// window <: object(...)
// private/temporary <: window(...)
// end(interface)
// \/code
// The declaration private/temporary makes "temporary" a private identifier that cannot be
// accessed outside the module interface (or one of its descendents). The declaration claire/window
// makes window an identifier from the claire module (thus it is visible everywhere), which is
// allowed since claire belongs to the list of usable modules for interface.\br
// In practice, there is almost always a set of files that we want to associate with a module,
// which means that we want to load into the module's namespace. CLAIRE allows an explicit
// representation of this through the slots made_of and source. made_of(m) is the list of
// files (described as strings) that we want to associate with the module and source(m) is the
// common directory (also described as a string). The benefits are the load/sload methods
// that provide automatic loading of the module's files into the right namespace and the module
// compiling features. CLAIRE expects the set of file names to be different from module names,
// otherwise a confusion may occur at compile time.\br
// A last important slot of a module is uses, a list of other modules that the new module is
// allowed to use. This list has two purposes, that only exist at compile time. The first one is
// to restrict the importation of symbols from other modules. A module is considered a legal import
// if it included itself in this uses list, or, recursively, if its father module is legal or if the
// module is legal for one of the modules in this list. An attempt to read a symbol m/s from a module
// that is not a legal import will provoke a compiler error. Second, this list is used by the
// compiler to find out which binaries should be included in the link script that is produced by
// the compiler.
// @cat




// @cat Global Variables and Constants
// @section I/O, Modules and System Interface
// @alias global constant constants
// CLAIRE offers the possibility to define global variables; they are named objects from the
// following class :
// \code
// global_variable <: thing(range:type, value:any)
// \/code
// For instance, one can create the following :
// \code
// tata :: global_variable(range = integer,
// 						value = 12)
// \/code
// However, there is a shorthand notation :
// \code
// tata:integer :: 12
// \/code
// Notice that, contrary to languages such as C++, you always must provide an initialization value
// when you define a global variable (it may be the unknown value). Variables can be used anywhere,
// following the visibility rules of their identifiers. Their value can be changed directly with the
// same syntax as local variables.
// \code
// tata := 12, tata :+ 1, tata :- 10
// \/code
// The value that is assigned to a global variable must always belong to its range, with the
// exception of the unknown value, which is allowed. If a variable is re-defined, the new value
// replaces the old one, with the exception still of unknown, which does not replace the previous
// value. This is useful for defining flags, which are global_variables that are set from the
// outside (e.g., by the compiler). One could write, for instance,
// \code
// talk:boolean :: unknown
// (#if talk printf(...))
// \/code
// The value of talk may be set to false before running the program to avoid loading the printf
// statements. When the value does not change, it is simpler to just assign a value to an
// identifier. For instance :
// \code
// toto :: 13
// \/code
// binds the value 13 to the identifier toto. This is useful to define aliases, especially when we
// use imported objects from other modules. For instance, if we use Logic/Algebra/exp, we may want
// to define a simpler alias with :
// \code
// exp :: Logic/Algebra/exp
// \/code
// The value assigned to a global variable may be made part of a world definition and thus restored
// by backtracking using choice/backtrack. It is simply required to declare the variable as a
// defeasible (i.e., backtrack -able) variable using the store declaration as for a relation :
// \code
// store(tata)
// (tata := 1, choice(), tata := 2, backtrack(), assert(tata = 1))
// \/code
// @cat

// @cat Miscellaneous
// @section Platform
// @cat


// @cat @xl Environment variables
// @section Platform
// Additionally to the CLAIRE getenv method, XL CLAIRE provides
// some tools that make possible to change an environment variable (setenv)
// or iterate over the whole environment of the process (environ/maxenv) as in :
// \code
// (for i in (1 .. maxenv())
// 	let (v, val) := explode_wildcard(environ(i), "*=*")
// 	in (assert(getenv(v) = val),
// 		printf("~A = ~S\n", v, val)))
// \/code
// Note that setenv and 
// @cat

// @cat @xl Process handling
// @section Platform
// 
// @cat

// @cat @xl File system
// @section Platform
// XL CLAIRE comes with a set of method used for the file system
// management. These methods are used to :
// \ul
// \li check whether a file or a directory exists (isfile?/isdir?)
// \li remove a file or a directory (unlink/rmdir)
// \li create new directories (mkdir)
// \li iterate over entries of a given directory (entries)
// \li check file times (faccessed/fmodified/fchanged)
// \li get a file size (fsize)
// \li create symbolic/hard links (link/symlink)
// \li get and change the file permission mode (fmode/chmod)
// \/ul
// @cat


// @cat @xl Debugging
// @section Using
// XL claire comes with a whole new debugger (since v3.3.39) that is far more
// robust and powerful than its previous implementation. The new strategy is to
// produce an instrumented meta code that calls the debugger handlers, as such
// interpreted and compiled code are homogeneously handled with the debugger.
// The debugger interface is handled by the toplevel and is highly inspired by
// the popular GNU debugger (gdb). The debugger is activated by the -debug command
// line option which would :
// \ul
// \li Instrument the loaded code. If additionally a compilation option is specified
// then the compiled code would also be instrumented (Notice that the compiler option
// -D implicitly implies -debug).
// \li Configure the toplevel to handle debug code.
// \/ul
// When an unhandled exception is caught by the toplevel a special debug loop is entered
// providing debugging interface to the user additionaly to the standard toplevel features,
// namely :
// \ul
// \li \b w, wh, whe, wher, where, bt \/b : backtrace of the execution stack (frames)
// \li \b f, fr, fra, fram, frame \/b : redisplay the current frame presented with a source code summary
// \li \b u, up \/b :  select the caller frame
// \li \b d, do, dow, down \/b :  select the called frame
// \li \b e, ed, edi, edit \/b : open the source file of the current frame at the right line (provided a correct setup of the
// WCL_EDITOR environment variable)
// \li local variables can be used as normal variable in the scope of the current selected frame (i.e.
// the user can use these variables in expressions)
// \li \b q \/b : abort the command and leave the debug loop
// \/ul
// Additionally the user may control a program execution step by step (stepper) either from
// an initial command or by interrupting the execution of a command. A program may be
// interrupted using ^C which would however stop the interpreter under Win32.
// @cat

// @doc class
// close interface is used to define constructors. Each time a new object x is
// created close(x) is call. The only case where the close interface isn't called
// is when the object is created by the special mClaire/new! allocator. close
// should always return a valid object (its argument most of time).
// \code
// ACCOUNT_ID:integer := 0
//
// account <: ephemeral_object(account_id:integer)
//
// close(self:account) : account ->
// 	(self.account_id := ACCOUNT_ID,
// 	ACCOUNT_ID :+ 1,
// 	self)
// \/code
close :: property(open = 3)




// @doc Printing
// self_print interface is used to redefine the way an entity is printed
// by the standard print method. self_print can be redefined for each new
// created class, for instance :
// \code
// account <: ephemeral_object(account_id:integer)
//
// self_print(self:account) : void ->
// 	printf("<account with id ~S>", self.account_id)
// \/code
self_print :: property(open = 3)


// @doc bag
// nth can be redefined on user class domain meant to have indexed access.
// The reader converts the x[y] notation into a call to nth(x,y) that
// at evaluation will call the redefined restriction :
// \code
// hash_table <: ephemeral_object(data:list[any])
//
// nth(x:hash_table, x:any) : any ->
// 	x.data[hash_value(x) and %%\xFFF]
// \/code
nth :: property(open = 3)

// @doc bag
// nth= can be redefined on user class domain meant to have indexed access.
// The reader converts the x[y] := z notation into a call to nth(x,y,z) that
// at evaluation will call the redefined restriction :
// \code
// hash_table <: ephemeral_object(data:list[any])
//
// nth=(x:hash_table, x:any, y:any) : void ->
// 	x.data[hash_value(x) and %%\xFFF] := y
// \/code
nth= :: property(open = 3)




// @doc bag
// add(s,x) adds x to the set s. The returned value is the set s U {x}.
// This method may modify the set s but not necessarily.
add(s:set, x:any) : set -> {}

// @doc bag
// add(s,x) adds x to the list l. The returned value is the list obtained by appending (x) to l.
add(l:list, x:any) : list -> nil


// @doc bag
// add*(l1,l2) returns the concatenated list l1 . l2, but it is destructive:
// it uses l1 as the data structure on which to perform the concatenation.
// Hence, the original l1 is no longer available after the method add* has been called
add*(l1:list, l2:list) : list -> nil

// @doc @xl char
// alpha?(c) returns true when the char c is in the range ('a' .. 'z', 'A' .. 'Z').
alpha?(c:char) : boolean -> true

// @doc @xl string
// alpha?(s) returns true if for all char c in s alpha?(c) is true.
alpha?(s:string) : boolean -> true



// @doc array
// creates a copy of the bag x that is represented as an array. The member type must
// be given as a parameter t and an error will occur if a member of the bag does not
// belong to t..
array!(x:bag, t:type) : type[t[]] -> any

// @doc module
// Sets the current namespace to the module m.
begin(m:module) : void -> none

// @doc module
// Pop the current namespace and restore the namespace that was active
// before the call to begin(m).
end(m:module) : void -> none

// @doc @xl number
// bin!(i) returns a string representation of the integer i in the binary basis
// (the length of the string is always 32). The string can only contain '0' and '1'
// chars
// \code
// bin!(0) -> "0000000000000000000000000000000"
// bin!(1) -> "0000000000000000000000000000001"
// bin!(12) -> "0000000000000000000000000001100"
// \/code
bin!(i:integer) : string -> ""

// @doc @xl number
// hex!(i) returns a string representation of the integer i in the hexadecimal
// basis (the length of the string is always 8). The string can only contain
// chars in the range ('0' .. '9') U ('A' .. 'F').
// \code
// hex!(0) -> "00000000"
// hex!(12) -> "0000000C"
// hex!(255) -> "000000FF"
// hex!(256) -> "00000100"
// \/code
hex!(i:integer) : string -> ""



// @doc bag
// Classical LISP methods that return the tail of the list (e.g. the list l starting at its second element ).
// \code
// cdr(list(1,2,3)) -> (2, 3)
// cdr(list(3,2,1)) -> (2, 1)
// \/code
cdr(l:list) : type[l] -> none

// @doc bag
// cast!(s, t) sets the member type of bag s to t. This method should be used carefully since
// their is no verification made to assert that all elements from the list actually belongs
// to the supplied type.
// \code
// cast!(list(1,2,3), integer) -> list<integer>(1,2,3)
// \/code
cast!(s:bag, t:type) : bag -> nil

// @doc number
// char!(n) returns the character which ASCII code is n.
// \code
// char!(65) -> 'A'
// \/code
char!(n:integer) : char -> ' '

// @doc @xl File system
// chmod(s, m) changes the mode of the file or directory s to m.
chmod(s:string, m:integer) : void -> none


// @doc @xl Miscellaneous
// color() returns the current color mode that can be on of :
// \ul
// \li 0 : uncolored
// \li 1 : terminal colors
// \li 2 : HTML colors
// \/ul
color() : integer -> 0

// @doc @xl Miscellaneous
// color(c) sets the color mode to c and returns the previous color mode
color(c:integer) : integer -> 0

// @doc @xl Miscellaneous
// color_princ(s) prints the string s on the current output (cout()).
// The string s may contain color sequences that will be printed
// as color modifiers according to the current color mode.
color_princ(s:string) : void -> 0

// @doc bag
// This traditional method appends x at the beginning of l and returns the constructed list.
// \code
// cons(1, list(2,3)) -> (1,2,3)
// \/code
cons(x:any, l:list) : list -> nil

// @doc class
// copy(x) returns a duplicate of the object x.
// It is not recursive : slots of the copied object are shared with that of the original one.
copy(x:object) : object -> none

// @doc bag
// The copy of a bag (a set or a list) returns a fresh set or list with the same elements
copy(s:bag) : bag -> nil

// @doc array
// The copy of an array returns a fresh array with the same elements
copy(a:array) : array -> nil

// @doc string
// The copy of a string is ... a copy of a string!
copy(s:string) : string -> ""

// @doc @xl date
// date_add(d, c, i) returns the date d incremented by i, where the unit of the increment
// depends on c :
// \ul
// \li 'H' or 'h' to increment hours
// \li 'M' to increment minutes
// \li 'S', 's' to increment seconds
// \li 'D', 'd' to increment days
// \li 'm' to increment months
// \li 'Y' or 'y' to increment years
// \/ul
date_add(d:float, c:char, i:integer) : float -> 0.0


// @doc bag
// delete(p, x, y) is equivalent to p(x) :delete y. This is a destructive method in
// the sense that it modifies its input argument unless the result is nil
// (There is only one empty list). The proper way to use delete, therefore, is either
// destructive (l :delete x) or non-destructive (delete(copy(l), x)).
delete(s:bag, x:any) : bag -> nil


// @doc @xl date
// diff_time(d1, d2) returns the difference d1 - d2 in seconds.
diff_time(d1:float, d2:float) : float -> 0.0

// @doc @xl char
// digit?(c) returns true if c is in the interval ('0' .. '9').
digit?(c:char) : boolean -> true

// @doc @xl string
// digit?(s) returns true if for all c in s digit?(c) is true.
digit?(s:string) : boolean -> true

// @doc @xl Miscellaneous
// ding() prints on stdout the "bell" char (ASCII 0x7).
ding() : void -> void



// @doc @xl port
// encode64(pr,pw,line_length) reads pr until EOF.
// read data are encoded in base 64 and then written
// on the port pw. line_length specify the length at
// which carriage return are inserted.
encode64(pr:port, pw:port, line_length:integer) : void -> none 

// @doc @xl port
// decode64(pr,pw) reads pr until EOF.
// read data is assumed to be encoded in base 64, the
// decoded data is written on pw.
decode64(pr:port, pw:port) : void -> none


// @doc @xl File system
// entries(s) returns the list of entries (files and sub-directories names)
// located in the directory s.
entries(s:string) : list[string] -> nil

// @doc @xl File system
// entries(s, w) returns the subset of entries (files and sub-directories names)
// located in the directory s that match the wildcard w (according to match_wilcard?).
// entries(s) is equivalent to entries(s, "*").
entries(s:string, w:string) : list[string] -> nil

// @doc @xl Environment variables
// environ(i) returns the i\sup th\/sup environment variable (1 based index) in the form "var=value".
environ(i:integer) : string -> ""


// @doc @xl Environment variables
// maxenv() returns the index of the last environment variable.
// For instance :
// \code
// for i in (1 .. maxenv()) printf("~A\n", environ(i))
// \/code
// printf the process environment in the same way as the env shell command.
maxenv() : integer -> 0

// @doc @xl Environment variables
// isenv?(v) tests the existence of the environment variable v.
isenv?(v:string) : boolean -> true


// @doc @xl string
// escape(s) encode the string s according to ISO-8859-1.
escape(s:string) : string -> ""


// @doc @xl string
// unescape(s) decode the string s assumed encoded according to ISO-8859-1.
unescape(s:string) : string -> ""

// @doc class
// exception!() returns the last exception that was raised.
exception!() : exception -> none


// @doc @xl string
// explode(s, sep) returns the list of substrings of s that are separated by sep.
// When sep is found at the beginning of the string s an empty match is added to the
// result list unlike if sep was found at the end of s. Last, if sep isn't found in
// s the result is a list that contain s as unique element.
// For instance :
// \code
// explode("CLAIRE--CLAIRE","--") -> list<string>("CLAIRE","CLAIRE")
// explode(";titi;toto",";") -> list<string>("","titi","toto")
// explode(";titi;toto;",";") -> list<string>("","titi","toto")
// explode("titi",";") -> list<string>("titi")
// \/code
explode(s:string, sep:string) : list[string] -> nil

// @doc @xl date
// explode(t) explodes the calendar time t in integers. The returned value
// is a tuple made of :
// \ul
// \li the year
// \li the month
// \li day of year (where January 1st is day 1)
// \li day of the month
// \li day of the week
// \li hour
// \li minute
// \li second
// \li and a boolean that tell whether summer time is in effect
// \/ul
explode(t:float) : tuple(integer, (1 .. 12), (1 .. 365), (1 .. 31), (1 .. 7), (0 .. 23), (0 .. 59), (0 .. 59), boolean) -> nil


// @doc @xl File system
// fcopy(s1,s2) copies the file s1 to a file named s2, if the copy is successful then
// the mode of s2 (according to fmode) is set to the same mode as s1.
fcopy(s1:string, s2:string) : void -> none

// @doc @xl File system
// fmode(s) returns the mode of the file s.
fmode(s:string) : integer -> 0

// @doc @xl File system
// fsize(s) returns the size in bytes of the file s. The returned value is a float
// and not an integer that could overflow for big files.
fsize(s:string) : float -> 0.0

// @doc @xl File system
// fchanged(s) returns the time when the status of file s was last changed (the time
// of the last write operation or the time of the last fmode call or the time
// of the last unlink...)
fchanged(s:string) : float -> 0.0

// @doc @xl File system
// fmodified(s) returns the time when the file s was last modified (e.g. the time
// of the last write operation)
fmodified(s:string) : float -> 0.0

// @doc @xl File system
// faccessed(s) returns the time when the file s was last accessed (e.g. the time
// of the last read operation)
faccessed(s:string) : float -> 0.0

// @doc type
// final(c) forbids the user to create any subclass of the class c.
// If c is a constant class, this is taken as a "diet" compiling directive.
final(c:class) : void -> none

// @doc @xl string
// find(s,x) returns the position in s where the first occurrence of x is found and 0 otherwise.
// \code
// find("toto","to") -> 1
// find("toto","oto") -> 2
// find("toto","ti") -> 0
// \/code
find(s:string, x:string) : integer -> 0

// @doc @xl string
// find(s,x,from) returns the position in s starting at from where the first occurrence of x
// is found and 0 otherwise.
// \code
// find("toto","to",2) -> 3
// find("toto","oto",2) -> 2
// find("toto","ti", 2) -> 0
// \/code
find(s:string, x:string, from:integer) : integer -> 0

// @doc @xl string
// find(s,x) returns the position in s where the last occurrence of x is found and 0 otherwise.
// \code
// rfind("toto","to") -> 3
// rfind("toto","tot") -> 1
// rfind("toto","ti") -> 0
// \/code
rfind(s:string, x:string) : integer -> 0

// @doc @xl string
// find(s,x,from) returns the position in s where the last occurrence of x is found
// before the position from and 0 otherwise.
// \code
// rfind("toto","to", 4) -> 3
// rfind("toto","to", 3) -> 3
// rfind("toto","to", 2) -> 1
// rfind("toto","ti", 4) -> 0
// \/code
rfind(s:string, x:string, from:integer) : integer -> 0


// @doc number
// transforms an integer into a float.
float!(x:integer) : float -> 0.0


// @doc call
// funcall provides an easy interface with external (C++) functions.
// funcall(f, s1, x, s) applies an external function to an argument of sort s1.
// The sort of the returned value must be passed as an argument.
// Notice that the last argument is the sort of the result, and that giving an
// erroneous sort argument will likely produce a fatal error.
funcall(f:function, s1:class, x:any, s:class) -> any

// @doc call
// like funcall(f, s1, x, s) but for external functions with two arguments.
funcall(f:function, s1:class, x:any, s2:class, y:any, s:class) -> any 

// @doc call
// like funcall(f, s1, x, s) but for external functions with three arguments.
funcall(f:function, s1:class, x:any, s2:class, y:any, s3:class, z:class, s:class) -> any

// @doc call
// funcall(m,x) applies a method with one argument
funcall(m:method, x:any) -> any 

// @doc call
// funcall(m,x,y) applies a method with two argument
funcall(m:method, x:any, y:any) -> any

// @doc call
// funcall(m,x,y) applies a method with three argument
funcall(m:method, x:any, y:any, z:any) -> any

// @doc call
// funcall(l,x) applies a lambda with one argument
funcall(l:lambda, x:any) -> any 

// @doc call
// funcall(l,x,y) applies a lambda with two argument
funcall(l:lambda, x:any, y:any) -> any

// @doc call
// funcall(l,x,y) applies a lambda with three argument
funcall(l:lambda, x:any, y:any, z:any) -> any
  

// @doc @xl port
// freadline(p) read a single line on the port p. The end-on-line
// marker is either CRLF, CR or LF and is not part of the returned
// line. 
freadline(p:port) : string -> ""

// @doc @xl port
// read a raw data from p until a separator in seps matches.
// If sensitive? is false the separator matching is made insensitively.
// esc is an escape char that is used while reading the raw data so that
// the char that follows cannot be part of a match. The return value
// is a tuple made of :
// \ul
// \li the raw data that was read (where escape sequences have been substituted by the
// escaped char)
// \li the element in seps that was matched or "" (the empty string) if the end-of-file
// was reached before a match could occur
// \/ul
freadline(p:port, seps:bag, sensitive?:boolean, esc:char) : tuple(string, (string U char)) -> nil

// @doc @xl port
// Equivalent to freadline(p, list(sep), sensitive?) but without support
// for escaping.
freadline(p:port, seps:bag, sensitive?:boolean) : tuple(string, (string U char)) -> nil

// @doc @xl port
// Equivalent to freadline(p, list(sep), sensitive?, esc)[1]
freadline(p:port, sep:string, sensitive?:boolean, esc:char) : string -> ""

// @doc @xl port
// Equivalent to freadline(p, sep, true)[1]
freadline(p:port, sep:string) : string -> ""

// @doc @xl port
// Equivalent to freadline(p, seps, true)
// For instance :
// \code
// parse_line_of_floats(p:port) : list[float] ->
// 	let l := list[float]
// 	in (while not(eof?(p))
// 			let (data, sep) := freadline(p, {',', ';', '\n'})
// 			in (if (length(data) > 0) l add float!(data),
// 				case sep ({""} break())), l)
// \/code
freadline(p:port, seps:bag) : tuple(string, (string U char)) -> nil




// @doc symbol
// gensym(s) generates randomly a new symbol prefixed by s.
gensym(s:string) : symbol -> none


// @doc array
// get(a, x) returns the lowest i such that a[i] = x (if no such i exists, 0 is returned).
get(a:array, x:any) : integer -> none

// @doc bag
// get(l, x) returns the lowest i such that l[i] = x (if no such i exists, 0 is returned).
get(l:list, x:any) : integer -> none

// @doc string
// get(l, x) returns the lowest i such that s[i] = c (if no such i exists, 0 is returned).
get(s:string, c:char) : integer -> none



// @doc @xl Environment variables
// setenv(s) adds or updates an environment variable defined by s = "var=value".
setenv(s:string) : void -> none

// @doc @xl Process handling
// getpid() returns the process id of the calling process
getpid() : integer -> 0 

// @doc @xl Process handling
// getppid() returns the parent process id of the calling process
getppid() : integer -> 0

// @doc @xl Process handling
// getuid() returns the real user ID of the calling process. Under windows
// this method always returns 0
getuid() : integer -> 0

// @doc bag
// hash(l, x) returns an integer between 1 and length(l) that is obtained through generic hashing.
// To obtain the best dispersion, one may use a list of size 2i-3. This function can be used to
// implement hash tables in CLAIRE; it is the basis of the table implementation.
hash(l:list, x:any) : integer -> 0


// @doc string
// integer!(s) returns the integer denoted by the string s if s is a string formed
// by a sign and a succession of digits.
integer!(s:string) : integer -> 0

// @doc number
// integer!(f) returns the lower integer approximation of f
integer!(f:float) : integer -> 0

// @doc char
// integer!(c) returns the ASCII code of c
integer!(c:char) : integer -> 0


// @doc symbol
// integer!(s) returns a unique index associated to a symbol s
integer!(s:symbol) : integer -> 0

// @doc methods
// Activate fast dispatch on the property p, that is dynamic calls should be optimized.
// p is meant to be a uniform property such the optimization can take place.
interface(p:property) : void -> none

// @doc methods
// This new method (in CLAIRE 3.1) is used to associate the interface status to a
// property or a set of properties. Within a class (through the use of
// interface(c, p1, ...)), this means that a member method will be generated for
// the C++ class associated to c. Note that this definition requires the presence of
// a method pi @ C for each property pi. In CLAIRE 3.1, a union (c1 U c2 ... U c3)
// can be used instead of a class, which is an elegant way to factor the interface
// declaration for c1, ... cn.
interface(c:(class U Union), pi:listargs) : void -> none

// @doc property
// r.inverse contains the inverse relation of r. If the range of r inherits from bag
// then r is considered multi-valued by default. If r and its inverse are mono-valued
// then if r(x) = y then inverse(r)(y) = x. If they are multi-valued, then inverse(r)(y)
// returns the set (resp. list) of all x such that (y % r(x)).
inverse(r:relation) : relation -> none

// @doc @xl File system
// Tells if s represents an existing directory entry.
isdir?(s:string) : boolean -> true

// @doc @xl File system
// Tells if s represents an existing file entry.
isfile?(s:string) : boolean -> true


// @doc @xl Process handling
// kill(p) terminates the process identified by the process id p.
// It first give a chance to the process to exit gracefully upon
// receipt of a SIGTERM signal. If the process still runs after
// a short timeout then a SIGKILL signal is send to the process.
// The caller should have necessary permissions.
kill(p:integer) : void -> none





// @doc @xl string
// left(s,i) is equivalent to substring(s, 1, i).
// \code
// left("123456", 2) -> "12"
// left("6", 2) -> "6"
// \/code
left(s:string, i:integer) : string -> ""

// @doc @xl string
// right(s,i) is equivalent to substring(s, length(s) - i + 1, length(s)).
// \code
// right("123456", 2) -> "56"
// right("6", 2) -> "6"
// \/code
right(s:string, i:integer) : string -> ""


// @doc array
// returns the length of an array
length(a:array) : integer -> 0


// @doc @xl File system
// creates a hard link for the file s1 with name s2.
link(s1:string, s2:string) : void -> none

// @doc @xl File system
// creates a symbolic link for the file s1 with name s2.
symlink(s1:string, s2:string) : void -> none

// @doc array
// list!(a) transforms a into a list.
list!(a:array) : type[list[member(a)]] -> none

// @doc bag
// list!(s) transforms s into a list. The order of the elements in the list can be anything.
list!(s:set) : type[list[member(s)]] -> none

// @doc @xl char
// lower?(c) returns true if c is not in ('A' .. 'Z').
lower?(c:char) : boolean -> true

// @doc @xl string
// lower?(s) returns true if for all char c in s lower?(c) is true.
lower?(s:string) : boolean -> true

// @doc @xl string
// lower(s) returns a copy of s where all uppercase letters are converted to lowercase.
lower(s:string) : string -> true

// @doc @xl date
// make_date(D,M,Y,h,m,s) returns the date D/M/Y h:m:s where months are one
// based index (M = 1 is January).
make_date(D:integer, M:integer, Y:integer, h:integer, m:integer, s:integer) : float -> 0.0

// @doc @xl date
// make_date(s) parses the string s and tries to create a date with it 
// according to RFC 1123
make_date(s:string) : float -> 0.0

// @doc @xl date
// make_time(s) parses the string s and tries to create a time with it
make_time(s:string) : float -> 0.0

// @doc @xl date
// returns the time constructed with the given hours, minutes and seconds
make_time(h:integer, m:integer, s:integer) : float -> 0.0

// @doc bag
// returns a list of length n filled with x (e.g., make_list(3, 0) = list(0, 0, 0)).
make_list(n:integer, x:any) : type[list[x]] -> none

// @doc @xl bag
// returns an empty list with type member t. n gives the size of the
// allocated content (i.e. adding n element won't cause further allocation).
make_list(t:type, n:integer) : list -> none

// @doc string
// make_string(i, c) returns a string of length i filled with the character c.
make_string(i:integer, c:char) : string -> ""


// @doc table
// returns a table with a domain of type d and a range t.
// The parameter x is the default value, thus x must belong to t, as
// well as any future value that will be put in the table.\br
// \xl In XL CLAIRE, tables created by make_table are seen as ephemeral,
// thus collectable by the GC.
make_table(d:type, t:type, x:any) : table -> none

// @doc @xl string
// match_wildcard?(s, w) returns true if the string s matches the wildcard w.
// The wildcard is a string that understand special chars :
// \ul
// \li '*' that means any sequence of chars
// \li '?' that means any char
// \li '#' escape the char that follow, necessary for instance to match special chars '*', '?' and '#'
// \/ul
// For instance :
// \code
// match_wildcard?("CLAIRE", "C*RE") -> true
// match_wildcard?("CLAIRE", "C*TE") -> false
// match_wildcard?("CLAIRE", "C???RE") -> true
// match_wildcard?("CLAIRE", "C???TE") -> false
// \/code
match_wildcard?(s:string, w:string) : boolean -> true

// @doc @xl string
// like match_wildcard?, explode_wildcard(s, w) matches the string
// s against the wildcard w. It return the list of matches or nil if
// the string s doesn't match. A match is made for each '*' and each
// sequence of '?'. For instance :
// \code
// explode_wildcard("CLAIRE", "C*RE") -> list<string>("LAI")
// explode_wildcard("CLAIRE", "C*TE") -> nil
// explode_wildcard("CLAIRE", "C???RE") -> list<string>("LAI")
// explode_wildcard("CLAIRE", "C???TE") -> nil
// \/code
explode_wildcard(s:string, w:string) : list[string] -> nil

// @doc array
// member_type(x) returns the type of all members of the array x.
// Therefore, member(a) = member_type(a) for an array a.
member_type(x:array) : type -> any

// @doc @xl string
// return a mime encoded representation of s (see RFC2047).
mime_encode(s:string) : string -> ""

// @doc @xl string
// decode the string s that is assumed to be mime encoded (see RFC2047).
mime_decode(s:string) : string -> ""

// @doc @xl File system
// mkdir(s, m) creates a new directory s with mode m.
mkdir(s:string, m:integer) : void -> none

// @doc @xl File system
// mkdir(s) is equivalent to mkdir(s, \777)
mkdir(s:string) : void -> none

// @doc number
// mod(x,y) is the rest of the Euclidean division of x by y (modulo).
mod(x:integer, y:integer) : integer -> 0

// @doc module
// module!() returns the current namespace (i.e. module).
module!() : module -> claire

// @doc module
// module!(r) returns the module where the restriction r was created.
module!(r:restriction) : module -> claire
 

// @doc bag
// nth(l,i) return the i\sup th\/sup element of the bag l.
// nth(l,i) is equivalent to l[i].
nth(l:bag, i:integer) : any -> none

// @doc table
// nth(t,x) returns the element of t that as the key x.
// nth(t,x) is equivalent to t[x].
nth(t:table, x:any) : any -> none

// @doc table
// nth(t,x) returns the element of t that as the key tuple(x, y).
// nth(t,x) is equivalent to t[x,y], t[tuple(x,y)] and nth(t,tuple(x,y)).
nth(t:table, x:any, y:any) : any -> none

// @doc array
// nth(a,i) returns the i\sup th\/sup element of the array a.
// nth(a,i) is equivalent to a[i].
nth(a:array, i:integer) : any => none

// @doc string
// nth(s,i) returns the i\sup th\/sup character of the string s.
// nth(s,i) is equivalent to s[i].
nth(s:string, i:integer) : any => none

// @doc number
// nth(n,i) returns true if the i\sup th\/sup digit of n in base 2 is 1.
// nth(n,i) is equivalent to n[i].
nth(n:integer, i:integer) : any => none

// @doc bag
// nth+(l,i,x) inserts element x at the i\sup th\/sup position in the bag l.
// By extension, i may be length(l) + 1, in which case x is
// inserted at the end of l. 
nth+(l:list, i:integer, x:any) : bag -> none

// @doc bag
// nth-(l,i) removes the i\sup th\/sup element of the bag l.
// By extension, i may be length(l) + 1, in which case x is
// inserted at the end of l. 
nth-(l:list, i:integer) : bag -> none



// @doc string
// nth=(s,i,c) sets the i\sup th\/sup character of the string s to c.
// nth=(s,i,c) is equivalent to s[i] := c.
nth=(s:string, i:integer, c:char) : any => none

// @doc table
// nth=(t,x,y) sets the item of t with key x to y.
// nth=(t,x,y) is equivalent to t[x] := y.
nth=(t:table, x:any, y:any) : any -> none

// @doc table
// nth=(t,x1,x2,y) sets the item t with key tuple(x1,x2) to y
// nth=(t,x1,x2,y) is equivalent to t[x1,x2] := y.
nth=(t:table, x1:any, x2:any, y:any) : any -> none


// @doc @xl string
// occurrence(s, z) returns the number of times when the substring z appears in s.
// \code
// occurrence("toto", "to") -> 2
// occurrence("toto", "tot") -> 1
// occurrence("toto", "t1") -> 0
// \/code
occurrence(s:string, z:string) : integer -> 0




// @doc Printing
// equivalent to print(n)
princ(n:integer) : void -> none

// @doc Printing
// princ(s) prints the string s on the current output (cout()).
princ(s:string) : void -> none

// @doc @xl Printing
// princ(s,i,j) is equivalent to princ(substring(s,i,j)) but without
// the allocation of a temporary string
princ(s:string, i:integer, j:integer) : void -> none

// @doc Printing
// princ(c) prints the char c on the current output (cout()).
princ(c:char) : void -> none




// @doc class
// put(p,x,y) is equivalent to p(x) := y but does not trigger the rules
// associated to p (seen as a relation) or the inverse of p.
// Besides, this operation is performed without any type-checking.
put(p:(property U slot), x:object, y:any) : any -> none

// @doc table
// put(t,x,y) is equivalent to t[x] := y but does not trigger the rules
// associated to a.
// Besides, this operation is performed without any type-checking.
put(t:table, x:object, y:any) : any -> none


// @doc symbol
// put(s,x) binds the symbol s to the object x.
put(s:symbol, x:any) : any -> none


// @doc integer
// random(n) returns an integer in (0 .. n-1), supposedly with uniform probability.
random(n:integer) : integer -> 0

// @doc integer
// random!(n) resets the seed for the random number generator process.
random!(n:integer) : void -> none

// @doc @xl integer
// random!() resets the seed with the current UNIX time value for the random number generator
// process.
random!() : void -> none



// @doc @xl string
// returns a copy of the string src where all occurrence of s have been replaced by rep.
// \code
// replace("toto", "to", "ti") -> "titi"
// replace("tototiti", "to", "") -> "titi"
// replace("totitoti", "tot", "t") -> "titi"
// \/code
replace(src:string, s:string, rep:string) : string -> ""

// @doc @xl File system
// rmdir(s) removes the directory s. The directory have to be empty and the calling
// process must have sufficient permissions.
rmdir(s:string) : void -> none

// @doc driving optimizations
// safe(x) is semantically equivalent to x and is ignored by the interpreter (x = safe(x)).
// On the other hand, this tells the compiler that the expression x must be compiled with
// the safe setting of the optimizing options. This is useful when a complete program requires
// high optimization settings for performance reasons but you still want to ensure that (say) 
// overflow errors will be detected. A typical use would be :
// \code
// try safe(x * y) catch error MAX_INTEGER
// \/code
// to implement a bounded multiplication that can be placed in an optimize module.
safe(x:any) : any -> any




// @doc @xl Miscellaneous
// setcwd(s) set the current working directory to the path s. this path can then
// be obtained with pwd.
setcwd(s:string) : void -> none

// @doc @xl Miscellaneous
// pwd() is used to obtain the path of the current working directory. this directory
// may be changed with setcwd.
pwd() : string -> ""

// @doc @xl Miscellaneous
// setlocale(cat, s) is a wrapper for the C lib setlocale.
// It sets the notion of natural language formatting style for particular
// sets of routines. The cat argument defines the category of the routine
// setlocale applies (see man). cat is one of the following :
// \ul
// \li CTYPE = 0
// \li LC_NUMERIC = 1
// \li LC_TIME = 2 
// \li LC_COLLATE = 3
// \li LC_MONETARY = 4
// \li LC_MESSAGES = 5 
// \li LC_ALL = 6
// \li LC_PAPER = 7
// \li LC_NAME = 8
// \li LC_ADDRESS = 9 
// \li LC_TELEPHONE = 10
// \li LC_MEASUREMENT = 11
// \li LC_IDENTIFICATION = 12
// \/ul
setlocale(cat:integer, s:string) : string -> ""

// @doc @xl Miscellaneous
// getlocale(s) returns the current locale for the given category cat (see setlocale).
getlocale(cat:integer) : string -> ""


// @doc bag
// The method shrink truncates the list l so that its length becomes n.
// This is a true side-effect and the value returned is always the same as the input.
// As a consequence, shrink(l, 0) returns an empty list that is different from the
// canonical empty list nil.
// \code
// let l := list<integer>(1,2,3)
// in (shrink(l, 2),
// 	assert(length(l) = 2))
// \/code
shrink(l:list, n:integer) : list  -> nil

// @doc string
// The method shrink truncates the string s so that its length becomes n.
// This is a true side-effect and the value returned is always the same as the input.
// \code
// let s := "123"
// in (shrink(s, 2),
// 	assert(length(s) = 2))
// \/code
shrink(s:string, n:integer) : string -> ""

// @doc @xl Miscellaneous
// sleep(t) suspends the execution of the process for t ms.
sleep(t:integer) : void -> none

// @doc @xl char
// space?(c) returns true if c is in {' ', '%%\t', '%%\r', '%%\n'}.
// \code
// space?(' ') -> true
// space?('\n') -> true
// space?('t') -> false
// \/code
space?(c:char) : boolean -> true

// @doc @xl string
// space?(s) returns true if for all c in s c is in {' ', '%%\t', '%%\r', '%%\n'}.
// space?("    ") -> true
// space?("   \n") -> true
// space?("    t") -> false
space?(s:string) : boolean -> true


// @doc world
// store(r1, r2, ...) declares the relations (properties or arrays) as defeasible
// (using the world mechanism)
store(rels:listargs) : void -> none

// @doc world
// store(v) declares the global variable v as defeasible
// (using the world mechanism).
store(v:global_variable) : void -> none

// @doc world
// store(a, n, v, b) is equivalent to a[n] := v but also stores
// this update in the current world if b is true. As a syntactical convenience,
// the argument b may be omitted if it is true. Note that there is a similar method
// for properties called put_store.
store(a:array, n:integer, v:any, b:boolean) : void -> none

// @doc world
// store(l, n, v, b) is equivalent to l[n] := v but also stores
// this update in the current world if b is true. As a syntactical convenience,
// the argument b may be omitted if it is true. Note that there is a similar method
// for properties called put_store.
store(l:list, n:integer, v:any, b:boolean) : void -> none

// @doc @xl date
// strftime(f,d) is a wrapper for the C lib strftime.
// f may contain formatters introduced by the '%' (see man).
strftime(f:string, d:float) : string -> ""

// @doc symbol
// string! converts a symbol into a string. For example if toto is a symbol string!(toto)
// returns "toto". Unlike make_string, it returns the unqualified form :
// \code
// string!(Francois/agenda) -> "agenda"
// whereas make_string(Francois/agenda) -> "Francois/agenda"
// \/code
string!(s:symbol) : string -> ""

// @doc number
// make a new string from an integer n.
string!(n:integer) : string -> ""




// @doc string
// substring(s,i,j) returns the substring of s starting at the i\sup th\/sup character and ending
// at the j th. For example :
// \code
// substring("CLAIRE", 3, 4) -> "AI"
// \/code
// If i is negative, the empty string is returned and if j is out of bounds
// (j > length(s)), then the system takes j = length(s).
substring(s:string, i:integer, j:integer) : string -> ""

// @doc string
// substring(s1,s2,b) returns i if s2 is a subsequence of s1, starting at s1's i\sup th\/sup character.
// The boolean b is there to allow case-sensitiveness or not (identify 'a' and 'A' or not).
// In case s2 cannot be identified with any subsequence of s1, the returned value is 0.
substring(s1:string, s2:string, b:boolean) : integer -> 0


// @doc symbol
// symbol!(s,m) returns the symbol associated to s in the module m . A new symbol is
// created if no such symbol exists.
symbol!(s:string, m:module) : symbol -> none



 
// @doc @xl date
//  timer!() return the current date time in second with millisecond granularity.
// That is a real time clock is started, the returned value may be used with
// elapsed or uptime to get the time elapsed since the timer! call.
timer!() : float -> 0.0

// @doc @xl date
// elapsed(t) returns the time in millisecond (accounted in real time) that has
// elapsed since the call to timer!()
elapsed(t:float) : integer -> 0

// @doc @xl date
// uptime(x) prints on the current output a human readable version of the time elapsed
// (accounted in real time) since timer! with millisecond granularity.
uptime(t:float) : void -> none

// @doc @xl string
// trim(s) returns a copy of s where heading and tailing blank chars (' ', '%%\n', '%%\t', '%%\r')
// have been removed, one may use ltrim or rtrim that operate on left/right only.
// \code
// trim("toto") -> "toto"
// trim(" toto  ") -> "toto"
// trim(" \ttoto\n") -> "toto"
// \/code
trim(s:string) -> string

// @doc @xl string
// ltrim(s) (say left trim) returns a copy of s where heading blank chars (' ', '%%\n', '%%\t', '%%\r')
// have been removed.
// \code
// ltrim("toto") -> "toto"
// ltrim(" toto  ") -> "toto  "
// ltrim(" \ttoto\n") -> "toto\n"
// \/code
ltrim(s:string) -> string

// @doc @xl string
// rtrim(s) (say right trim) returns a copy of s where tailing blank chars (' ', '%%\n', '%%\t', '%%\r')
// have been removed.
// \code
// rtrim("toto") -> "toto"
// rtrim(" toto  ") -> " toto"
// rtrim(" \ttoto\n") -> " \ttoto"
// \/code
rtrim(s:string) -> string

// @doc @xl File system
// unlink(s) removes the file s from the disk. note that the the file may still exists
// after the call since an other process may have it already open...
unlink(s:string) -> void xl

// @doc @xl string
// upper?(c) returns false if c is an lowercase letter.
// \code
// upper?('t') -> false
// upper?('1') -> true
// upper?('T') -> true
// \/code
upper?(c:char) : boolean -> true

// @doc @xl string
// upper?(s) returns false if it exists a char c in s such c is
// a lowercase letter
// \code
// upper?("toto") -> false
// upper?("123") -> true
// upper?("1 % @ B") -> true
// \/code
upper?(s:string) : boolean -> true

// @doc @xl string
// returns a copy of the string s where all lowercase letters have been
// converted to uppercase.
// \code
// upper("toto") -> "TOTO"
// upper("a 1 % @ B") -> "A 1 % @ B"
// \/code
upper(s:string) : string -> ""

// @doc @xl string
// url_encode(s) returns a new string that is a representation of s encoded
// according to RFC 1738.
// \code
// url_encode("toto") -> "toto"
// url_encode("toto titi=tata") -> "toto+titi%3Dtata"
// \/code
url_encode(s:string) : string -> ""

// @doc @xl string
// url_decode(s) returns a new string that is the decoded version of s
// according to RFC 1738.
// \code
// url_decode("toto") -> "toto"
// url_decode("toto+titi%3Dtata") -> "toto titi=tata"
// \/code
url_decode(s:string) : string -> ""

// @doc port
// use_as_output(p) changes the value of the current output (the port where all
// print instructions will be sent AKA cout()) to p. It returns the previous port that was used
// as output which can thus be saved and possibly restored later.
use_as_output(p:port) : port -> stdout

// @doc world
// world?() returns the index of the current world.
world?() : integer -> 0

// @doc world
// choice() creates a new world and steps into it.
choice() : void -> none

// @doc world
// backtrack() pops the current world and returns to the previous one.
backtrack() : void -> none

// @doc world
// backtrack(n) returns to the world numbered with n, and pops all the intermediary worlds.
backtrack(n:integer) : void -> none


// @doc world
// The method commit() returns to the previous world but carries the updates that
// were made within the current world; these updates now belong to the previous world
// and another call to backtrack() would undo them.
commit() : void -> none

// @doc world
// commit(n) returns to the world numbered with n through successive applications of
// commit().
commit(n:integer) : void -> none


// @doc number
// (x ^ y) returns the y exponent of x. y must be a positive integer,
// otherwise an error is raised.
^(x:integer, y:integer) : integer => 0


// @doc bag
// (l ^ y) skips the y first members of the list l.
// If the integer y is bigger than the length of the list l, the result
// is the empty list, otherwise it is the sublist starting at the y + 1 position in
// l (up to the end).
^(l:list, y:integer) : list -> nil

// @doc bag
// (s1 ^ s2) returns the intersection of the two sets s1 and s2 that is the set of entities
// that belong to both s1 and s2. 
// Other internal restrictions of the property ^ exist, where ^ denotes the intersection
// (it is used for the type lattice).
^(s1:set, s2:set) : set -> {}

// @doc number
// ^2(x) returns the 2 exponent of x
^2(x:integer) => integer


// @doc type
// (x % y) returns (x E y) for any entity x and any abstract set y.
// An abstract set is an object that represents a set, which is a type or a list.
%(x:any, y:any) : boolean -> true



// @doc number
// returns the product of two integers
*(x:integer, y:integer) : integer => 0


// @doc number
// returns the opposite of x
-(x:integer) : integer => 0


// @doc number
// returns the division of two integers
/(x:integer, y:integer) : integer => 0


// @doc number
// returns true if x is greater than y
>(x:float, y:float) : boolean => true

// @doc number
// returns true if x is greater or equal to y
>=(x:integer, y:integer) : boolean => true

// @doc number
// returns true if x is greater or equal to y
>=(x:float, y:float) : boolean => true


// @doc number
// returns true if x is lower than y
<(x:float, y:float) : boolean => true


// @doc number
// returns true if x is lower or equal to y
<=(x:float, y:float) : boolean => true


// @doc string
// s1 /+ s2 returns a new string that is the concatenation of the two strings.
// \code
// "toto" /+ "titi" -> "tototiti".
// \/code
/+(s1:string, s2:string) : string -> ""

// @doc  bag
// l1 /+ l2 returns a new list that is the concatenation of the two lists.
/+(l1:list, l2:list) : list -> nil

// @doc type
// x .. y returns the interval interval (x .. y).
..(x:integer, y:integer) : Interval -> none

// @doc entity
// (x = y) returns true if x is equal to y and nil otherwise.
// Equality is defined as identity for all entities except strings, lists and sets. 
// For lists, sets and strings, equality is defined recursively as follows: x
// and y are equal if they are of same size n and if x[i] is equal to y[i] for all i in (1 .. n). 
=(x:any, y:any) : boolean -> none



// @doc string
// returns true if x is greater than y according to the lexicographic
// order induced by the ASCII order on characters.
>(x:string, y:string) : boolean -> true

// @doc string
// returns true if x is lower than y according to the lexicographic
// order induced by the ASCII order on characters.
<(x:string, y:string) : boolean -> true

// @doc string
// returns true if x is greater or equal to y according to the lexicographic
// order induced by the ASCII order on characters.
>=(x:string, y:string) : boolean -> true

// @doc string
// returns true if x is lower or equal to y according to the lexicographic
// order induced by the ASCII order on characters.
<=(x:string, y:string) : boolean -> true


// @doc char
// returns true if ASCII code of x is greater than ASCII code of y
>(x:char, y:char) : boolean -> true

// @doc char
// returns true if ASCII code of x is lower than ASCII code of y
<(x:char, y:char) : boolean -> true

// @doc char
// returns true if ASCII code of x is greater or equal to ASCII code of y
>=(x:char, y:char) : boolean -> true



// @doc type
// The order on types is the inclusion: (x <= y) returns true if all
// members of type x are members of type y.
<=(x:type, y:type) : boolean -> true



// @doc bag
// (l << n) left-shifts the list l by n units, which means that the n first
// members of the list are removed. This is a method with a side-effect since
// the returned value is the original list, which has been modified.
<<(l:list, n:integer) : list -> nil



// @doc @xl Free-able objects
// The prefree! interface is called by the GC before a freeable_object is actually freed.
// It give a chance to terminate inter-object operations that may need a last synchronization
// step (like the flush of a filter). Since an object x given to the handler prefree! is about to be
// freed you should never create reference on x in the scope of the handler (i.e. don't add x to a
// list, don't set a global var to x).
prefree! :: property(open = 3)

// @doc @xl Free-able objects
// In a similar way to prefree! interface free! is called by the GC before a freeable_object is
// actually freed. It is a good place, for instance, to free externally allocated memory. An object x given to the
// free! handler should be handled with a lot of care :
// \ul
// \li Don't try to access x.s where x.s is itself an object (x.s could already be freed by the GC).
// use prefree! instead for such operation
// \li Don't create reference on x (i.e. don't add x to a list, don't set a global var to x)
// \/ul
free! :: property(open = 3)


// @doc @xl world
// XL CLAIRE provides a convenient way to (pre)allocate defeasible lists in a class
// prototypes. Starting with CLAIRE 3, the content of a defeasible list have to be
// allocated prior to perform updates on it. prealloc_list(t,n) allocates an empty list
// for a class prototype that will automatically initialize a slot with a preallocated
// list of n elements and initially empty :
// \code
// lesson <: ephemeral_object(
// 			students:list[student] = prealloc_list(student, 100))
// 
// (store(students))
// 
// lesson!() : lesson -> lesson()
// \/code
// notice that the list owned by the class prototype is actually empty and that it becomes
// allocated only once it is copied (as done by instantiation process).
prealloc_list(t:type, n:integer) : list -> nil

// @doc @xl world
// preallocate a set in a similar way to prealloc_list.
prealloc_set(t:type, n:integer) : set -> nil