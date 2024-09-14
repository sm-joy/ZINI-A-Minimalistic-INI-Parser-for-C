# ZINI - A Simple INI Parser Library

ZINI is a straightforward and lightweight library for parsing INI files in C. It allows you to read, write, and manage configuration files in the INI format efficiently. This library provides a simple interface for handling sections and key-value pairs within INI files.

## Features

- **Read INI files**: Load and parse INI files into memory.
- **Write INI files**: Save changes back to INI files.
- **Manage sections and key-value pairs**: Easily add and retrieve sections and key-value pairs.
- **Memory management**: Automatically handle memory allocation and deallocation.

## Getting Started

### Prerequisites

- A C compiler (e.g., `gcc` or `clang`).

### Installation

You can include ZINI in your project by copying the header and source files or by cloning the repository.

#### Single Header Version

For a simple integration, use the single header file approach:

1. Download the `zini.h` file from the `SingleHeader` folder.
2. Include it in your project with:

    ```c
    #include "zini.h"
    ```

#### Multi-File Version

For a more modular approach, use the multi-file version:

1. Download `zini.h` and `zini.c` from the `Multi-File` folder.
2. Include `zini.h` in your project and compile `zini.c` along with your source files.

    ```c
    #include "zini.h"
    ```

    Compile with:

    ```sh
    gcc -o your_program your_program.c zini.c
    ```