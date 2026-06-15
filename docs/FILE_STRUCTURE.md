# BubbleScript File Structure

```text
bubblescript/
│
├── README.md
├── FILE_STRUCTURE.md
├── PLANS.md
├── examples/
│   ├── hello.bubble
│   ├── variables.bubble
│   └── loops.bubble
│
├── src/
│   ├── main.cpp
│   │
│   ├── lexer/
│   │   ├── Token.h
│   │   ├── Token.cpp
│   │   ├── Lexer.h
│   │   └── Lexer.cpp
│   │
│   ├── parser/
│   │   ├── Parser.h
│   │   ├── Parser.cpp
│   │   ├── AST.h
│   │   └── AST.cpp
│   │
│   ├── interpreter/
│   │   ├── Interpreter.h
│   │   └── Interpreter.cpp
│   │
│   ├── runtime/
│   │   ├── Environment.h
│   │   └── Environment.cpp
│   │
│   └── utils/
│       └── Error.h
│
├── tests/
│   ├── lexer_tests.cpp
│   ├── parser_tests.cpp
│   └── interpreter_tests.cpp
│
└── build/
```

## Responsibility of Each Folder

### lexer/

Converts source code into tokens.

Example:

```bubble
say "hello"
```

Becomes:

```text
SAY
STRING("hello")
EOF
```

### parser/

Converts tokens into an AST.

Example:

```bubble
say "hello"
```

Becomes:

```text
PrintStatement
 └── StringLiteral("hello")
```

### interpreter/

Walks through the AST and executes it.

Example:

```bubble
say "hello"
```

Output:

```text
hello
```

### runtime/

Stores variables and program state.

Example:

```bubble
bubble name = "john"
```

Environment:

```text
name -> "john"
```

### examples/

Programs used for testing.

### tests/

Unit tests.
