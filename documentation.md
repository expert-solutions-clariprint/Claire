# XL Claire — Documentation (Markdown)

This document is a **Markdown adaptation and guided entry point** to the HTML manual for **XL Claire** (the “Claire language + XL extensions” distribution maintained by eXpert solutions / expert-solutions-clariprint).

- **HTML manual (source of truth):** https://expert-solutions-clariprint.github.io/Claire/
- **Repository:** https://github.com/expert-solutions-clariprint/Claire

---

## 1) What is Claire / XL Claire?

**CLAIRE** is a high-level, portable, functional and object-oriented language with advanced rule-processing capabilities. It aims at expressing complex algorithms with fewer lines while keeping code readable.

The language focuses on:
- a rich type system (including intervals and second-order types),
- parametric classes and methods,
- propagation rules (event-driven),
- dynamic versioning (for exploration of search spaces),
- set-based and polymorphic programming,
- an entity-relation approach (relations, inverses, unknown values).

**XL Claire** extends the original Claire 3 language with additional runtime/kernel features and practical “systems” capabilities, including:
- extended Kernel API,
- simplified system integration and module sharing,
- extensible I/O architecture with filters,
- arbitrary long strings,
- memory congestion handling,
- **WCL** printing syntax (`?>...<?`),
- extensible **command line** option handling per module,
- **serialization** for IPC and session storage,
- documentation generation from code comments,
- **GDB-like debugger** for interpreted and compiled code,
- a scanf-like parametric regex engine.

(See the repo README for the “Key aspects” list, and the HTML manual for detailed semantics.)

---

## 2) Quick orientation: the manual structure

The HTML manual is organized by categories. Main sections include:

1. **Introduction**
2. **Primitives** (including **Dates & Times [XL]**)
3. **Objects, Classes and Slots**
4. **Lists, Sets and Instructions**
5. **Methods and Types**
6. **Tables, Rules and Hypothetical Reasoning**
7. **I/O, Modules and System Interface** (includes **WCL**, **Modules**, **Command line**, **Serialization [XL]**)
8. **Platform** (env vars, processes, filesystem, signals… mostly [XL])
9. **Using XL Claire** (**Debugging [XL]**)
10. Driving optimizations

---

## 3) Notation: what “[XL]” means

In the HTML manual, features marked **[XL]** are **XL Claire specific** (extensions beyond the original Claire 3 baseline).

---

## 4) Core concepts (fast recap)

### 4.1 Primitives

- **Integers** are represented using 30 bits (OID model constraint).
- **Floats** are C double precision.

### 4.2 Dates and Times [XL]

Dates/times are represented as **floats** containing a UNIX time (seconds since Epoch), because Claire integers are 30-bit while Unix time is typically 32-bit.

Notable functions include:
- `make_date(...)`, `make_time(...)`
- `strftime(...)`
- `date_add(...)`, `diff_time(...)`
- `timer!()`, `elapsed(...)`
- `time_set()`, `time_get()`, `time_show()`

---

## 5) Namespaces and Modules

Modules are **first-class objects** representing **namespaces**. Claire supports **multiple namespaces**, arranged in a hierarchy similar to a Unix filesystem.

### 5.1 Defining a module

A module has important slots:
- `part_of` (parent module)
- `uses` (modules allowed to be imported/used)

Example (from the manual):

```claire
interface :: module(part_of = library, uses = list(claire))
```

### 5.2 Entering/leaving a module namespace

```claire
begin(interface)
  window <: object(...)
end(interface)
```

This defines the identifier `interface/window`.

### 5.3 Visibility rules (practical summary)

- Unqualified identifiers are visible only if they belong to a descendant of the current module.
- Qualified identifiers marked `private/` are not visible outside their module subtree.
- Other qualified identifiers are visible, but the compiler may reject them if they come from modules not allowed by `uses`.

### 5.4 Files attached to modules

Modules can model their source layout via:
- `made_of(m)` : list of files associated with module `m`
- `source(m)` : common directory

This enables automatic loading/compilation workflows.

---

## 6) I/O and Web-oriented printing: WCL syntax [XL]

XL Claire introduces **WCL (Web CLaire) syntax**, designed for generating dynamic content with an HTML-like feel and inline Claire evaluation.

Conceptually:
- It’s an alternative to `printf`.
- It supports inline substitution and embedded code blocks.

Example snippet shown in the manual (HTML table generator):

```claire
?><table><?
  for y in (1 .. 10)
  ( ?><tr><?
      for x in (1 .. 10)
      ( ?><td><?= x ?>,<?= y ?><? )
    ?></tr><? )
?></table><?
```

If you build web apps or server-side HTML generation, **WCL is one of the defining XL features**.

---

## 7) Command line handling [XL]

XL Claire adds a command line processor where **each module can declare its own options** through handlers:

- `option_usage(opt:{"-x"}) -> tuple(description, usage, details)`
- `option_respond(opt:{"-x"}, args:list[string]) -> void`
- `option_parsed() -> void` (runs after all options are parsed)

This design lets an executable inherit option sets from linked modules (e.g., linking a “Reader” module implicitly adds `-f` / `-ef`).

---

## 8) Serialization [XL] (IPC and sessions)

The `Serialize` module provides serialization/deserialization of Claire values through ports:

- `serialize(p:port, self:any) -> serialize_context`
- `serialize(p:port, top?:boolean, self:any) -> serialize_context`
- `unserialize(p:port) -> any`

Use cases:
- **IPC** (pipes/sockets)
- Persisting **session data**
- Transmitting results/errors between processes

The manual highlights:
- Primitive types are always serializable.
- Tables, bags/arrays serialize recursively as needed.
- Named objects serialize by **name** only; the receiver must have the referenced named objects defined.

---

## 9) Debugger [XL]

XL Claire includes a robust debugger (instrumented meta-code) inspired by **gdb** and activated via `-debug`.

When an unhandled exception occurs, you can enter a debug loop with commands such as:
- backtrace: `w`, `wh`, `whe`, `where`, `bt`
- frame navigation: `f`, `frame`, `u` (up), `d` (down)
- open editor at source location: `e`, `edit` (requires `WCL_EDITOR`)
- local variables usable as normal variables in the selected frame
- quit: `q`

This is meant to work consistently for interpreted and compiled code.

---

## 10) XL Claire “application modules” (what exists in this distribution)

Beyond the language/kernel features, the repository README points to additional modules/features often used in real applications:

- **Apache 2.0 bridge** (`mod_wcl`)
- **HTTP/CGI handling** (`Http/*`, `Wcl*`)
- **Sessions + web debugger** (`Wcl`)
- **Localization** (`Locale`)
- **DBMS abstraction** (Dbo / Db* modules + drivers) to avoid writing SQL directly
- **XML and SOAP** (`Sax`, `Soap*`)
- **Mail generation** (`Mail`)
- **PDF framework** (`Pdf`) including HTML/CSS conversion, attachments, digital signatures

If you’re documenting “XlClaire” for developers, these are the **practical modules** that typically define the ecosystem beyond the core language.

---

## 11) Where to go next

- Read the **HTML manual** end-to-end for precise semantics:
  - https://expert-solutions-clariprint.github.io/Claire/
- Use the repository structure as a map:
  - `kernel/`, `meta/`, `console/`, `compile/`, `docs/`, …

---

## Appendix — Manual metadata

From the HTML manual header:
- Manual title: **claire v3.7.8 user manual**
- Last updated: **Tue, 02 Apr 2024**
- Authors include: Yves Caseau, Sylvain Benilan, Xavier Pechoultres (expert-solutions), Laurent Rebière (expert-solutions)

