# CLAIRE

CLAIRE is a fork of the ​Claire 3 language (from Yves Caseau) which is a high-level functional object-oriented language originally aimed at solving complex problem (see ​Claire 3 description and the Papers page). The CLAIRE language with the WebClaire framework is a more general purpose language while being fully compliant with the original Claire 3 language, either used as a scripting language or as a dynamic web application framework. Claire is written in C++ and comes with an interpreter and a compiler that generates efficient C++. 

## Key aspects

### Inherited from ​Claire 3 :

 * automatic garbage collection
 * rules processing capabilities
 * rich type system including type intervals and second-order types (with static/dynamic typing)
 * parametric classes and methods
 * propagation rules based on events
 * dynamic versioning that supports easy exploration of search spaces
 * set-based programming with an intuitive syntax
 * simple-minded object-oriented programming
 * truly polymorphic and parametric functional programming
 * an entity-relation approach with explicit relations, inverses and unknown values 

### Starting with XL Claire :

 * extended Kernel API
 * simpler system integration, compiler interface and module sharing process
 * extensible IO architecture with embedded filtering support
 * support for arbitrary long strings
 * automatic support of memory congestion
 * new printing syntax using tag notation ( ?>...<? )
 * extensible command line handling, each new module may provide its own option set
 * serialization of entities for IPC and session data
 * user documentation generation from code comments
 * GDB like debugger for both interpreted and compiled code
 * parametric regular expression like engine (scanf) 

### Starting with Claire :

 * Apache 2.0 bridge (through the apache module mod_wcl)
 * HTTP/CGI handling (Http/Wcl? modules)
 * session support (Wcl module)
 * Web debugger providing on page report and backtrace of unhandled exception (Wcl module)
 * localization (Locale module)
 * DBMS abstraction layer which prevent to write any SQL request (Dbo/Db? modules and driver modules)
 * XML and SOAP support (Sax/Soap? modules)
 * on the fly mail generation (Mail module)
 * Pdf framework to read and write PDF documents (HTML/CSS convertor, attachements, digital signature) (Pdf module) 

## This is the developper GIT.

To build a new Claire installation package :

`./make`


