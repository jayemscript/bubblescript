# BubbleScript

A simple interpreted programming language written in C++.

BubbleScript is a personal learning project created to explore how programming languages work internally—from lexical analysis and parsing to AST evaluation and runtime execution.

The goal is not to compete with existing languages, but to understand how languages like Python, JavaScript, and Lua execute code under the hood.

---

## Philosophy

BubbleScript aims to be:

* Easy to read
* Easy to learn
* Beginner-friendly
* Fun to experiment with
* Built from scratch for educational purposes

Example:

```bubble
say "Hello, World!"
```

---

## Current Status

Project Status: 🚧 In Development

The language is currently in the planning phase.

Planned milestones:

* [ ] Basic file execution
* [ ] Lexer
* [ ] Parser
* [ ] Abstract Syntax Tree (AST)
* [ ] Interpreter
* [ ] Variables
* [ ] Arithmetic expressions
* [ ] Conditional statements
* [ ] Loops
* [ ] Functions
* [ ] Standard library

---

## Example Syntax

### Printing

```bubble
say "Hello World"
```

### Variables

```bubble
bubble name = "John"

say name
```

### Arithmetic

```bubble
bubble x = 10
bubble y = 20

say x + y
```

### Conditions

```bubble
if x > 5 {
    say "Big Number"
}
```

### Loops

```bubble
repeat 3 {
    say "Pop!"
}
```

### Functions

```bubble
func greet(name) {
    say "Hello"
    say name
}

greet("John")
```

---

## Project Structure

```text
bubblescript/
├── README.md
├── FILE_STRUCTURE.md
├── PLANS.md
├── examples/
├── src/
├── tests/
└── build/
```

For detailed architecture, see:

* FILE_STRUCTURE.md
* PLANS.md

---

## Learning Goals

This project is intended to teach:

* Compiler fundamentals
* Interpreter design
* Tokenization (Lexing)
* Parsing
* Abstract Syntax Trees
* Runtime environments
* Language implementation in C++

---

## Why "BubbleScript"?

Because every programming language starts as a small idea.

BubbleScript is meant to be simple, lightweight, and approachable—a language where ideas can rise to the surface one bubble at a time.

---

## Future Ideas

Potential future features:

* Modules
* Objects and classes
* Bytecode virtual machine
* Garbage collection
* Package manager
* LLVM backend
* Native executable generation

---

## License

This project is created for learning and experimentation.

License: Apache License
