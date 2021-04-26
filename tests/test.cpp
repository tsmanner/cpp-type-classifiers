#include <iomanip>
#include <iostream>
#include <type_traits>

#include "type_classifiers.h"

using typing::Type;

using SignedIntType = decltype(Type<int>() || Type<int8_t>() || Type<int16_t>() || Type<int32_t>() || Type<int64_t>());

template <typename T>
struct Int {
  static_assert(
    Type<T>() == SignedIntType(),
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
typename std::enable_if<((Type<T1>() && Type<T2>()) == SignedIntType())>::type
f() {
  std::cout << "f()\n";
}


template <typename T>
typename std::enable_if<(Type<T>() == !Type<int>())>::type
g() {
  std::cout << "g()\n";
}


int main() {
  static_assert(Type<int>() == (Type<int>() || Type<int8_t>()), "Ruh Roh");
  static_assert((Type<int>() || Type<int8_t>()) == (Type<int>() || Type<int8_t>()), "Ruh Roh");

  static_assert(Type<int>() != (Type<unsigned>() || Type<uint8_t>()), "Ruh Roh");
  static_assert(Type<int>() == !(Type<unsigned>() || Type<uint8_t>()), "Ruh Roh");
  static_assert(Type<int>() == (!Type<unsigned>() && !Type<uint8_t>()), "Ruh Roh");

  static_assert(!(Type<int>() != Type<int>()), "Ruh Roh");
  static_assert(!(Type<int>() == !Type<int>()), "Ruh Roh");
  static_assert((Type<unsigned>() == !Type<int>()), "Ruh Roh");

  static_assert((Type<int>() || Type<int8_t>()) != (Type<unsigned>() || Type<uint8_t>()), "Ruh Roh");
  static_assert((Type<int>() || Type<int8_t>()) == !(Type<unsigned>() || Type<uint8_t>()), "Ruh Roh");
  static_assert((Type<int>() || Type<int8_t>()) == (!Type<unsigned>() && !Type<uint8_t>()), "Ruh Roh");

  static_assert(Type<int>() == (!Type<unsigned>()), "Ruh Roh");
  static_assert(Type<int>() == Type<typing::Any>(), "Ruh Roh");
  static_assert(Type<int>() != Type<typing::None>(), "Ruh Roh");
  static_assert(Type<int>() == !Type<typing::None>(), "Ruh Roh");
  static_assert(!(Type<int>() == Type<typing::None>()), "Ruh Roh");

  using std::cout;
  cout << std::boolalpha;

  cout << (!(Type<int>() == !Type<int>())) << '\n';

  // If uncommented, the next line fails to compile with
  // "no matching function call" because `g` takes only `!int`
  // g<int>();
  g<unsigned>();

  Int<int> i;
  Int<int8_t> i8;

  IntPair<int, int8_t> i_i8;
  // If uncommented, the next line fails to compile with
  // assertion that uint8_t is not a signed int type
  // IntPair<int, uint8_t> i_u8;

  f<int, int8_t>();

  return 0;
}
