# cpp-structure-introspection

**cpp-structure-introspection** is a lightweight C++ library that allows you to access the members of a struct by index, similar to how you would access elements in a tuple. This can be particularly useful for generic programming and reflection-like functionality in C++.

## Key Features

- **Simple structure member access by index**: Access each member of a struct with `get<i>()`, where `i` is the zero-based index of the member.
- **No macros or boilerplate code**: Introspection capabilities are added without the need for additional macros.
- **Easy integration**: Just include the header, and you’re ready to use it.

## Example Usage

Here's a quick example to demonstrate how to use cpp-structure-introspection:

```cpp
#include <raw.cpp> // Include the library header

struct Point {
  int x, y, z;
};

int main() {
  Point point{2, 3, 5};
  
  // Access struct members by index
  std::cout << "x : " << get<0>(point) << std::endl;
  std::cout << "y : " << get<1>(point) << std::endl;
  std::cout << "z : " << get<2>(point) << std::endl;
}
```

### Output

```
x : 2
y : 3
z : 5
```

## Requirements

- **C++17 or later** is recommended for compatibility.