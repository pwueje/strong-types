
# strong_types

Type-safe strong typedefs for C++

## Overview

This library provides a simple and efficient way to create strong typedefs (strong types) in C++. Strong types help prevent bugs by making invalid operations between logically distinct types impossible, even if they share the same underlying representation (e.g., `int`).

## Features
- Header-only, zero-overhead abstraction
- Type-safe wrappers for primitive types
- Prevents accidental mixing of types
- Supports
    - comparison operators
    - value access
    - arithmetic (for arithmetic types)
    - hashing (usable in unordered containers)

## Example Usage

### Basic Usage
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

### Arithmetic operations
```cpp
#include <pjexx/strong_types.h>
using namespace pjexx::strong_types;
// strong_type supports arithmetic for arithmetic types:
Width w1{3};
Width w2{7};
auto w_sum = w1 + w2; // w_sum.get() == 10
w_sum += w1;           // w_sum.get() == 13
auto w_prod = w1 * w2; // w_prod.get() == 21
```

### Hashing support
```cpp
// strong_type supports hashing and can be used in unordered containers:

#include <unordered_map>
#include <unordered_set>
#include <functional>

std::unordered_map<Width, std::string> width_map;
width_map[w] = "ten";
std::unordered_set<Name> name_set;
name_set.insert(n);

// You can also use std::hash directly:
std::hash<Width> width_hasher;
size_t hash_value = width_hasher(w);
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
