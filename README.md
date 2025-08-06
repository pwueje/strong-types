
# strong_types

Type-safe strong typedefs for C++

## Overview

This library provides a simple and efficient way to create strong typedefs (strong types) in C++. Strong types help prevent bugs by making invalid operations between logically distinct types impossible, even if they share the same underlying representation (e.g., `int`).

## Features
- Header-only, zero-overhead abstraction
- Type-safe wrappers for primitive types
- Prevents accidental mixing of types
- Supports comparison operators and value access

## Example Usage

```cpp
#include <pjexx/strong_types.h>
using namespace pjexx::strong_types;

using Width = strong_type<int, struct WidthTag>;
using Length = strong_type<int, struct LengthTag>;
using Name  = strong_type<std::string, struct NameTag>;

Width w{10};
Length l{20};
Name n{"Alice"};

// w and l are not interchangeable, even though both wrap int
// Width w2 = l; // Compilation error
```

## Building & Testing

This project uses CMake and Conan for dependency management and building.

### Prerequisites
- CMake >= 3.20
- Conan >= 2.0
- A C++20 compatible compiler

### Build Steps
```sh
# Install dependencies and generate CMake presets
conan install . --output-folder=build --build=missing

# Configure and build using Conan-generated presets
cmake --preset=conan-debug
cmake --build --preset=conan-debug

# Run tests
cd build && ctest
```

## License

See [LICENSE.md](LICENSE.md).
