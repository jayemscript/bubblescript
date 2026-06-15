# BubbleScript Development Plan

## Phase 1 - Hello World

Goal:

```bubble
say "Hello World"
```

Tasks:

* Read file contents
* Split lines
* Detect "say"
* Print text

No lexer
No parser
No AST

Just prove execution works.

---

## Phase 2 - Build a Lexer

Goal:

Convert source code into tokens.

Example:

```bubble
say "hello"
```

Output:

```text
SAY
STRING("hello")
EOF
```

Create:

* TokenType enum
* Token class
* Lexer

---

## Phase 3 - Build a Parser

Goal:

Convert tokens into AST nodes.

Example:

```bubble
say "hello"
```

AST:

```text
PrintStatement
 └── StringLiteral
```

Create:

* AST Node base class
* Statement nodes
* Expression nodes
* Parser

---

## Phase 4 - Interpreter

Goal:

Execute AST.

Example:

```bubble
say "hello"
```

Output:

```text
hello
```

Create:

* Interpreter visitor
* Execute statements
* Evaluate expressions

---

## Phase 5 - Variables

Syntax:

```bubble
bubble name = "John"
say name
```

Add:

* Variable declarations
* Variable lookup
* Runtime environment

---

## Phase 6 - Arithmetic

Syntax:

```bubble
bubble x = 10
bubble y = 20

say x + y
```

Add:

* *
* *
* *
* /

Expression evaluation

---

## Phase 7 - Conditions

Syntax:

```bubble
if x > 5 {
    say "big"
}
```

Add:

* >
* <
* > =
* <=
* ==
* !=

If statements

---

## Phase 8 - Loops

Syntax:

```bubble
repeat 5 {
    say "pop"
}
```

Add:

* Repeat statement
* Loop execution

---

## Phase 9 - Functions

Syntax:

```bubble
func greet(name) {
    say name
}

greet("John")
```

Add:

* Function declarations
* Function calls
* Scope

---

## Phase 10 - Polish

Add:

* Better error messages
* Comments
* Imports
* Standard library

Example:

```bubble
// comment

say "done"
```

---

## Future

Optional advanced features:

* Bytecode VM
* JIT compilation
* LLVM backend
* Garbage collection
* Modules
* Classes
* Objects

````

Goal:

```bubble
bubble user = "John"

func greet(name) {
    say "Hello"
    say name
}

greet(user)
````

If BubbleScript can run this, you've already built something very close to a real language.
