# md5.hpp

[![CMake](https://github.com/shediao/md5.hpp/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/shediao/md5.hpp/actions/workflows/cmake-multi-platform.yml)

A modern, easy-to-use, header-only C++20 MD5 hash library that supports both compile-time and runtime calculations.

## Core Features

- **Compile-time Calculation**: Leverages C++20 `constexpr` to compute MD5 hashes of string literals directly at compile time.
- **Runtime Calculation**: Provides a flexible streaming API for computing MD5 hashes of strings, byte arrays, or data streams at runtime.
- **Header-Only**: Simply include `md5/md5.hpp` with no need to link against a library, allowing for quick integration.
- **Easy to Use**: A clean API design that is easy to handle for both simple and complex use cases.
- **Zero Dependencies**: Does not depend on any third-party libraries.

## Usage

### Quick Start

Calculating the MD5 hash of a string is very simple:

```cpp
#include <iostream>
#include <md5/md5.hpp>

int main() {
    // Runtime calculation
    std::string message = "Hello, world!";
    std::string hash = md5::md5sum(message);
    std::cout << "MD5 of '" << message << "': " << hash << std::endl;
    // Output: MD5 of 'Hello, world!': 6cd3556deb0da54bca060b4c39479839

    // Compile-time calculation (requires C++20)
    consteval auto compile_time_hash = md5::MD5("Hello, C++20").hexdigest();
    std::cout << "Compile-time MD5: " << compile_time_hash << std::endl;
    // Output: Compile-time MD5: 2fb194837e3eb2f062872007b165620d

    return 0;
}
```

### Streaming API

For large data streams or chunked data, you can use the `update` interface:

```cpp
#include <iostream>
#include <md5/md5.hpp>

int main() {
    md5::MD5 hasher;
    hasher.update("Hello, ");
    hasher.update("world!");
    hasher.finalize();

    std::string hash = hasher.hexdigest();
    std::cout << "Streamed MD5: " << hash << std::endl;
    // Output: Streamed MD5: 6cd3556deb0da54bca060b4c39479839
}
```

## API Reference

### `md5::md5sum(input)`

A convenient free function for quickly calculating the hash of a string or byte array.

- `md5::md5sum(std::string_view const& input)`
- `md5::md5sum(const char* input, size_t length)`

### `md5::MD5` Class

Provides full control over the hash calculation process.

- `constexpr MD5()`: Default constructor.
- `constexpr MD5(input, length)`: Constructs and immediately computes the hash for the complete data.
- `constexpr void update(input, length)`: Updates the hash calculation in chunks.
- `constexpr void finalize()`: Finalizes the calculation. This must be called before calling `hexdigest()`.
- `constexpr static_string<32> hexdigest() const`: Returns a 32-character hexadecimal hash value. The result type is `static_string`, which is implicitly convertible to `std::string`.

## Build and Integration

### CMake

We recommend integrating `md5.hpp` using CMake's `FetchContent` or `add_subdirectory`.

```cmake
# In your CMakeLists.txt

# Method 1: Using FetchContent (Recommended)
include(FetchContent)
FetchContent_Declare(
  md5_hpp
  GIT_REPOSITORY https://github.com/shediao/md5.hpp.git
  GIT_TAG main # Or specify a concrete release tag
)
FetchContent_MakeAvailable(md5_hpp)

# Method 2: Using add_subdirectory (if you have this repository as a submodule)
# add_subdirectory(external/md5.hpp)

# Link to your target
target_link_libraries(your_target PRIVATE md5::md5)
```

### Manual Integration

Since it is a header-only library, you can also copy the `md5/` directory from `include/` directly into your project and ensure your compiler can find it.

```cpp
#include "path/to/your/md5/md5.hpp"
```

This project requires a compiler that supports **C++20** or higher.

## Building Tests

If you have cloned the repository and want to run the tests, you can use the following commands:

```bash
git clone https://github.com/shediao/md5.hpp.git
cd md5.hpp
cmake -B build -DMD5_BUILD_TESTS=ON
cmake --build build
cd build
ctest --output-on-failure
```
