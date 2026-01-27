# CLAIRE / XL Claire

XL CLAIRE is a fork of the original **Claire 3** language (Yves Caseau).  
This distribution (often referred to as **XL Claire**) keeps compatibility with Claire 3 while adding practical extensions and a larger application framework layer (“WebClaire”).  
CLAIRE is implemented in **C++** and provides both an **interpreter** and a **compiler** (generating efficient C++).

- Original Claire 3 repo: https://github.com/ycaseau/CLAIRE3.4

## Why choose XL Claire ?
- https://github.com/expert-solutions-clariprint/Claire/tree/master/whyXlClaire.md

## Documentation
- Quick start documentation (MD): https://github.com/expert-solutions-clariprint/Claire/tree/master/documentation.md
- Canonical documentation (HTML manual): https://expert-solutions-clariprint.github.io/Claire/

> This repository is the developer Git.

---

## Quick Guide / Entry Point (10 minutes)

### 1) Read the docs (don’t skip)
- **Start here (HTML manual):** https://expert-solutions-clariprint.github.io/Claire/
- The `docs/` folder contains the sources used to generate the manual.

### 2) Build from source
The repo’s README recommends building a new Claire installation package with:

```bash
./make
```

If you’re packaging or integrating into CI, inspect the build scripts and Makefiles in the repo root.

### 3) What you get after build
You should have the CLAIRE toolchain available (interpreter + compiler).  
From there you can:
- run scripts as a “scripting language”,
- compile Claire code to C++ for performance,
- build web apps using WebClaire (WCL).

### 4) Learn the 4 XL features that change everything
These are the most “XL” parts you’ll notice quickly:

**A) WCL printing syntax** (`?> ... <?`) — practical for HTML/text generation

```claire
?><table><?
  for y in (1 .. 10)
  ( ?><tr><?
      for x in (1 .. 10)
      ( ?><td><?= x ?>,<?= y ?><? )
    ?></tr><? )
?></table><?
```

**B) Modules = namespaces**  
Modules are first-class namespaces and can be composed (with visibility control through `uses`).

```claire
interface :: module(part_of = library, uses = list(claire))

begin(interface)
  window <: object(...)
end(interface)
```

**C) Module-driven CLI options**  
Each module can contribute its own command line options (usage + handler), and options are merged based on what you link/import.

**D) Debugger**  
Run with `-debug` to get a gdb-like debug loop (backtrace, frame navigation, locals, open editor, etc.).

---

## What is “XL Claire” exactly?

In short: **Claire 3 compatibility + extensions**.

### Inherited from Claire 3 (core language)
- automatic garbage collection
- rule processing capabilities
- rich type system (type intervals, second-order types, static/dynamic typing)
- parametric classes and methods
- propagation rules based on events
- dynamic versioning (exploring search spaces)
- set-based programming with intuitive syntax
- polymorphic and parametric functional programming
- entity-relation approach (relations, inverses, unknown values)

### XL Claire additions (language/runtime extensions)
- extended Kernel API
- simpler system integration, compiler interface and module sharing
- extensible I/O architecture with embedded filtering support
- arbitrary long strings
- automatic support of memory congestion
- WCL printing syntax (`?>...<?`)
- extensible command line handling (modules can add option sets)
- serialization for IPC and session data
- documentation generation from code comments
- gdb-like debugger for interpreted and compiled code
- scanf-like parametric regex engine

### “Ecosystem” modules commonly used in applications
- Apache 2.0 bridge (`mod_wcl`)
- HTTP/CGI handling (Http/Wcl modules)
- sessions + web debugger (Wcl)
- localization (Locale)
- DBMS abstraction (Dbo/Db + drivers)
- XML and SOAP (Sax/Soap)
- on-the-fly mail generation (Mail)
- PDF framework (HTML/CSS conversion, attachments, digital signatures) (Pdf)

---

## Repository map (where to look)

Top-level folders you’ll typically care about:

- `kernel/` — core runtime/kernel
- `meta/` — meta-model / reflective layer
- `compile/` — compiler toolchain
- `console/` — console tooling / REPL-like entry points
- `include/` — headers / C++ integration surface
- `docs/` — documentation sources (HTML manual generation)
- `test/` — tests
- `release/`, `stable2/` — packaging / release branches/artifacts (as used by maintainers)

---

## Related repositories (libraries)

If you’re looking for “batteries included” reusable libraries (DB, XML, HTTP, PDF, etc.), see:

- **ClaireToolKit**: https://github.com/expert-solutions-clariprint/ClaireToolKit

(It contains many of the higher-level application modules referenced above.)

---

## License

Apache-2.0. See `LICENSE`.
