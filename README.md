# md5.hpp

[![CMake](https://github.com/shediao/md5.hpp/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/shediao/md5.hpp/actions/workflows/cmake-multi-platform.yml)

一个现代、易于使用、仅头文件的 C++20 MD5 哈希库，支持编译期和运行期计算。

## 核心功能

- **编译期计算**: 利用 C++20 `constexpr`，可以在编译阶段直接计算字符串字面量的 MD5 哈希值。
- **运行期计算**: 提供灵活的流式 API，用于在运行时计算字符串、字节数组或数据流的 MD5。
- **仅头文件**: 只需包含 `md5/md5.hpp` 即可，无需链接库文件，方便快速集成。
- **易于使用**: 简洁的 API 设计，无论是简单场景还是复杂需求都能轻松应对。
- **无依赖**: 不依赖任何第三方库。

## 使用方法

### 快速开始

计算字符串的 MD5 哈希值非常简单：

```cpp
#include <iostream>
#include <md5/md5.hpp>

int main() {
    // 运行时计算
    std::string message = "Hello, world!";
    std::string hash = md5::md5sum(message);
    std::cout << "MD5 of '" << message << "': " << hash << std::endl;
    // 输出: MD5 of 'Hello, world!': 6cd3556deb0da54bca060b4c39479839

    // 编译期计算 (需要 C++20)
    consteval auto compile_time_hash = md5::MD5("Hello, C++20").hexdigest();
    std::cout << "Compile-time MD5: " << compile_time_hash << std::endl;
    // 输出: Compile-time MD5: 2fb194837e3eb2f062872007b165620d

    return 0;
}
```

### 流式 API

对于大数据流或分块数据，可以使用 `update` 接口：

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
    // 输出: Streamed MD5: 6cd3556deb0da54bca060b4c39479839
}
```

## API 介绍

### `md5::md5sum(input)`

一个便捷的自由函数，用于快速计算字符串或字节数组的哈希值。

- `md5::md5sum(std::string_view const& input)`
- `md5::md5sum(const char* input, size_t length)`

### `md5::MD5` 类

提供对哈希计算过程的完整控制。

- `constexpr MD5()`: 默认构造函数。
- `constexpr MD5(input, length)`: 构造并直接计算完整数据的哈希值。
- `constexpr void update(input, length)`: 分块更新哈希计算。
- `constexpr void finalize()`: 完成计算过程。在调用 `hexdigest()` 前必须调用此函数。
- `constexpr static_string<32> hexdigest() const`: 返回一个包含 32 个字符的十六进制哈希值。结果类型是 `static_string`，可以隐式转换为 `std::string`。

## 构建与集成

### CMake

我们推荐使用 CMake 的 `FetchContent` 或 `add_subdirectory` 来集成 `md5.hpp`。

```cmake
# 在你的 CMakeLists.txt 中

# 方法 1: 使用 FetchContent (推荐)
include(FetchContent)
FetchContent_Declare(
  md5_hpp
  GIT_REPOSITORY https://github.com/shediao/md5.hpp.git
  GIT_TAG main # 或者指定一个具体的 release tag
)
FetchContent_MakeAvailable(md5_hpp)

# 方法 2: 使用 add_subdirectory (如果你将本仓库作为子模块)
# add_subdirectory(external/md5.hpp)

# 链接到你的目标
target_link_libraries(your_target PRIVATE md5::md5)
```

### 手动集成

由于是仅头文件库，你也可以直接将 `include/` 目录下的 `md5/` 文件夹复制到你的项目中，并确保编译器可以找到它。

```cpp
#include "path/to/your/md5/md5.hpp"
```

本项目需要 **C++20** 或更高版本的编译器。

## 构建测试

如果你克隆了本仓库并希望运行测试，可以使用以下命令：

```bash
git clone https://github.com/shediao/md5.hpp.git
cd md5.hpp
cmake -B build -DMD5_BUILD_TESTS=ON
cmake --build build
cd build
ctest --output-on-failure
```
