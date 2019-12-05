# Cpp-structure-introspection

```cpp
#include <raw.cpp>

struct Point {
  int x, y, z;
};

int main() {
  Point point{2, 3, 5};
  
  std::cout << "x : " << get <0>(point) << std::endl;
  std::cout << "y : " << get <1>(point) << std::endl;
  std::cout << "z : " << get <2>(point) << std::endl;
}
```

```
x : 2
y : 3
z : 5
```
