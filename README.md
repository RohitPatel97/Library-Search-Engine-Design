# Library Search Engine Design

A C++20 project that models library book records and benchmarks how different data structures perform when inserting, removing, and searching for books. The program reads book data from standard input, stores it in multiple STL containers, measures the cost of common operations, and exports the timing results in CSV format for analysis.

## Overview

This project was built to explore the tradeoffs between common data structures used in search-heavy applications. Using a shared `Book` object and a consistent input dataset, the program compares the performance of:

- `std::vector`
- `std::list` (doubly linked list)
- `std::forward_list` (singly linked list)
- `std::map` (binary search tree)
- `std::unordered_map` (hash table)

The goal is to show how container choice affects runtime for operations such as front/back insertion, front/back removal, and ISBN-based search.

## Features

- Reads and stores structured book records containing:
  - ISBN
  - title
  - author
  - price
- Implements a custom `Book` class with:
  - constructors and assignment operators
  - accessor and modifier methods
  - stream insertion/extraction operators
  - comparison operators using C++20's three-way comparison support
- Benchmarks container operations across multiple STL data structures
- Measures elapsed time for each operation as the dataset grows or shrinks
- Exports results as CSV for graphing or spreadsheet analysis
- Uses randomized sample ordering to reduce bias in measurement order

## Why this project stands out

This project goes beyond a basic CRUD-style library app by combining object-oriented design, STL container usage, file parsing, algorithm analysis, and performance benchmarking in one implementation. It demonstrates:

- strong C++ fundamentals
- practical understanding of data structure tradeoffs
- ability to work with file I/O and structured data
- experience collecting and analyzing performance data
- clean modular design across multiple source files

## Project Structure

```text
Library-Search-Engine-Design-main/
|-- CMakeLists.txt       # Cross-platform build configuration
|-- README.md            # Project documentation
|-- include/             # Public project headers
|   |-- Book.hpp
|   |-- Operations.hpp
|   `-- Timer.hpp
|-- src/                 # Application source files
|   |-- Book.cpp
|   `-- main.cpp
`-- data/
    `-- output.csv       # Example benchmark output
```

## How it works

1. The program reads book records from standard input.
2. Each record is stored as a `Book` object.
3. The same dataset is used to test operations across several data structures.
4. Runtime measurements are collected at fixed intervals.
5. Final results are printed in CSV format.

Search operations are based on ISBN keys, which makes the comparison between sequential containers and key-based containers especially clear.

## Input Format

The program expects book records in CSV-style format, one record per line:

```csv
"9789998287532", "Over in the Meadow", "Ezra Jack Keats", 91.11
"9780134685991", "Effective Modern C++", "Scott Meyers", 49.99
```

Each line should contain:

- quoted ISBN
- quoted title
- quoted author
- numeric price

## Build Instructions

Compile with a C++20-compatible compiler such as `g++`:

```bash
g++ -std=c++20 -O2 -Wall -Wextra -pedantic -Iinclude src/main.cpp src/Book.cpp -o library_search_engine
```

Or build with CMake:

```bash
cmake -S . -B build
cmake --build build
```

## Run Instructions

Provide an input file through standard input and redirect the CSV results to a file:

```bash
./library_search_engine < books.txt > results.csv
```

Notes:

- Benchmark progress messages are written to the console through `std::clog`
- Timing results are written to standard output in CSV format
- The included `data/output.csv` is an example of generated benchmark results

## Example Output Columns

The generated CSV includes benchmark columns such as:

- `Vector/Insert at the back`
- `Vector/Search`
- `DLL/Insert at the front`
- `SLL/Remove from the back`
- `BST/Search`
- `Hash Table/Insert`

This makes it easy to import the results into Excel, Google Sheets, Python, or MATLAB for visualization.

## Concepts Demonstrated

- Object-oriented programming in C++
- STL containers and iterators
- Time complexity and data structure analysis
- Benchmarking and runtime measurement
- CSV parsing and formatted stream I/O
- Use of `std::map` and `std::unordered_map` for keyed lookup
- C++20 language features including the spaceship operator

## Future Improvements

- Add command-line argument support for input and output files
- Support sorting and filtering by title, author, or price
- Add graphical visualization of benchmark results
- Compare larger real-world datasets
- Expand the project into an interactive library search application

## Author

Developed as a C++ data structures and performance analysis project focused on benchmarking search and storage strategies for library book records.
