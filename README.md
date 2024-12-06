# Compiler Construction

This repository contains the implementation of a custom compiler for a subset of programming languages. The compiler follows the typical structure of a modern compiler and is capable of converting source code written in a high-level language into assembly code. The goal of this project is to understand the various phases involved in compiler construction and implement them step by step.

## Features

- **Lexical Analysis (Tokenizer):** Converts source code into tokens.
- **Parsing:** Converts tokens into an Abstract Syntax Tree (AST) using context-free grammar.
- **Semantic Analysis:** Performs type checking and scope management.
- **Intermediate Representation (IR):** A step between parsing and code generation that simplifies optimization and target code generation.
- **Code Generation:** Generates assembly code from the IR.
- **Optimizations:** Implements basic optimization techniques like constant folding and dead code elimination.
- **Error Handling:** Provides comprehensive error reporting for syntax and semantic errors.

## Phases of the Compiler

1. **Lexical Analysis:**
   - The lexical analyzer breaks the input source code into tokens. Each token represents a fundamental element of the language, such as keywords, variables, operators, or symbols.
   
2. **Parsing:**
   - The parser takes the list of tokens and applies context-free grammar to build an Abstract Syntax Tree (AST), which represents the syntactic structure of the program.
   
3. **Semantic Analysis:**
   - This phase involves verifying the semantic correctness of the program. It ensures that operations are type-safe and checks for errors like undeclared variables or invalid operations.
   
4. **Intermediate Representation (IR):**
   - The program is converted into an intermediate form that is easier to optimize and transform into the final code. This phase abstracts the target architecture to allow for better optimizations.
   
5. **Optimization:**
   - Optimizations like constant folding and dead code elimination are applied to improve the generated assembly code's efficiency.
   
6. **Code Generation:**
   - The final phase involves translating the IR or AST into assembly code, which is specific to the target architecture.

## Installation

### Prerequisites

- A C++ compiler (e.g., g++)
- Make (for building the project)
- Linux or Windows with Cygwin, or macOS

### Steps to Install

1. Clone this repository:

   ```bash
   git clone https://github.com/hamadhassan/Compiler-Construction.git
   cd Compiler-Construction
