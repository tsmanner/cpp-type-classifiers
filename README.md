# cpp-type-classifiers

A set of compile-time type classifiers for C++, meant to improve the usability of the &lt;type_traits> library.


## Getting Started

Clone this repository or download [type_classifiers.h](./include/type_classifiers.h), and put it in your include path.

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

## Template parameter pack

To use this library with template parameter packs, you'll need the ability to fold operators through lists of `Type` instances.  A generic way of doing that looks like this:

```cpp
template <typename F, typename T1, typename T2>
constexpr auto fold(F const &inF, T1 const &inT1, T2 const &inT2) {
  return inF(inT1, inT2);
};

template <typename F, typename T1, typename T2, typename... Ts>
constexpr auto fold(F const &inF, T1 const &inT1, T2 const &inT2, Ts const &...inTs) {
  return inF(inT1, fold(inF, inT2, inTs...));
};
```

This `fold` function can now be used with any of the operators defined by the stl in the `<functional>` header.  Let's revisit the example of checking for and unsigned types.  That could accomplished with this

```cpp
template <typename... Ts>
struct TypeSet {
  static constexpr auto valid_types = fold(std::logical_or<>(), typing::Types<Ts>()...);
};

using SignedIntType = decltype(TypeSet<int, int8_t, int16_t, int32_t, int64_t>::valid_types);
```
