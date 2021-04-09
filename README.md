# cpp-type-classifiers

A set of compile-time type classifiers for C++, meant to improve the usability of the &lt;type_traits> library.


## Getting Started

Clone this repository or download <a href="https://github.com/tsmanner/cpp-type-classifiers/raw/main/include/type_classifiers.h" download>type_classifiers.h</a>, and put it in your include path.

To start classifying your types, start by wrapping the types you care about in `typing::Type` so they can be composed into classifications.  Next, start combining those `Type`s into the classifications you want.  For example, the following is a classification that includes all signed integer types:

```cpp
#include "type_classifiers.h"
// Pull Type into the namespace
using typing::Type;
// Use decltype here so the compiler doesn't make an instance and pack it into your binary
using SignedIntType = decltype(Type<int>() || Type<int8_t>() || Type<int16_t>() || Type<int32_t>() || Type<int64_t>());
```

Now you can use it to control function implementations with `std::enable_if`, or to cause compile failures with `static_assert` when a type is (or is not!) a signed integer.

```cpp
#include <iostream>
#include <type_traits>

template <typename T>
typename std::enable_if<Type<T>() == SignedIntType()>::type
func(T const &inT) {
  std::cout << "T is signed integer!\n";
}

template <typename T>
typename std::enable_if<Type<T>() != SignedIntType()>::type
func(T const &inT) {
  std::cout << "T is not a signed integer!\n";
}
```

The second form can be expressed in three different ways:

```cpp
typename std::enable_if<Type<T>() != SignedIntType()>::type
typename std::enable_if<Type<T>() == !SignedIntType()>::type
typename std::enable_if<!(Type<T>() == SignedIntType())>::type
```

Boolean OR, AND, and NOT operations are all supported with the `Type` meta-class, and comparisons are symmetrical.  That means it is possible to enforce a classification on multiple types at once, or to use other classifications as terms within some new classificiation.

A function with two template arguments, where one function call should happen if both are signed ints, and a different one for any other combination, could be represented with:

```cpp
#include <iostream>
#include <type_traits>

template <typename T1, typename T2>
typename std::enable_if<(Type<T1>() && Type<T2>()) == SignedIntType()>::type
func(T const &inT) {
  std::cout << "T1 and T2 are signed integers!\n";
}

template <typename T>
typename std::enable_if<(Type<T1>() && Type<T2>()) != SignedIntType()>::type
func(T const &inT) {
  std::cout << "Either T1 or T2 is not a signed integer!\n";
}
```
