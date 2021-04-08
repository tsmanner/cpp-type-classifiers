#include <iomanip>
#include <iostream>
#include <type_traits>

#include "type_classifiers.h"

using typing::Type;

template <typename T>
struct Int {
  static_assert(
    Type<T>() == (Type<int>() || Type<int8_t>() || Type<int16_t>() || Type<int32_t>() || Type<int64_t>()),
    "Int template argument must be a signed `int` type"
  );
};

template <typename T1, typename T2>
struct IntPair {
  static_assert(
    (Type<T1>() && Type<T2>()) == (Type<int>() || Type<int8_t>() || Type<int16_t>() || Type<int32_t>() || Type<int64_t>()),
    "IntPair template arguments must be signed `int` types"
  );
};

template <typename T1, typename T2>
typename std::enable_if<((Type<T1>() && Type<T2>()) == (Type<int>() || Type<int8_t>()))>::type
f() {
  std::cout << "f()\n";
}

int main() {
  static_assert(Type<int>() == (Type<int>() || Type<int8_t>()), "Ruh Roh");
  static_assert((Type<int>() || Type<int8_t>()) == (Type<int>() || Type<int8_t>()), "Ruh Roh");

  static_assert(Type<int>() != (Type<unsigned>() || Type<uint8_t>()), "Ruh Roh");
  static_assert((Type<int>() || Type<int8_t>()) != (Type<unsigned>() || Type<uint8_t>()), "Ruh Roh");
  static_assert((Type<int>() || Type<int8_t>()) == (!Type<unsigned>() && !Type<uint8_t>()), "Ruh Roh");

  static_assert(Type<int>() == (!Type<unsigned>()), "Ruh Roh");

  using std::cout;
  cout << std::boolalpha;

  Int<int> i;
  Int<int8_t> i8;

  IntPair<int, int8_t> i_i8;
  // IntPair<int, uint8_t> i_u8;

  f<int, int8_t>();

  return 0;
}
