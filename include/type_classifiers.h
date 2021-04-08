#pragma once

#include <type_traits>


//
// Type
//

template <typename T>
struct Type {
  using type = T;

  constexpr Type<T>() {}

};


//
// Combinators
//

// EQUAL
template <typename...> struct TypeEQUAL;

// NOT
template <typename T>
struct TypeNOT {
  using type = Type<T>;

  constexpr TypeNOT<T>() {}
  // constexpr operator!
};

// NOT Equal
template <typename TL, typename TR>
struct TypeNOT<TypeEQUAL<TL, TR>> {
  using type = TypeEQUAL<TL, TR>;

  constexpr TypeNOT() {}

  constexpr operator bool() {
    return !static_cast<bool>(type());
  }
};

// OR
template <typename TL, typename TR>
struct TypeOR {
  using type_left = TL;
  using type_right = TR;

  constexpr TypeOR<TL, TR>() {}
};

// AND
template <typename TL, typename TR>
struct TypeAND {
  using type_left = TL;
  using type_right = TR;

  constexpr TypeAND<TL, TR>() {}
};


//
// Equality
//

// Type Type
template <typename TL, typename TR>
struct TypeEQUAL<Type<TL>, Type<TR>> {
  using type_left = Type<TL>;
  using type_right = Type<TR>;

  constexpr TypeEQUAL() {}

  constexpr operator bool() {
    return std::is_same<typename type_left::type, typename type_right::type>::value;
  }
};


// Type TypeNOT
template <typename TL, typename TR>
struct TypeEQUAL<Type<TL>, TypeNOT<TR>> {
  using type_left = Type<TL>;
  using type_right = TypeNOT<TR>;

  constexpr TypeEQUAL() {}

  constexpr operator bool() {
    return !static_cast<bool>(type_left() == typename type_right::type());
  }
};


// Type TypeOR
template <typename TL, typename TRL, typename TRR>
struct TypeEQUAL<Type<TL>, TypeOR<TRL, TRR>> {
  using type_left = Type<TL>;
  using type_right = TypeOR<TRL, TRR>;

  constexpr TypeEQUAL() {}

  constexpr operator bool() {
    return static_cast<bool>(type_left() == typename type_right::type_left())
        || static_cast<bool>(type_left() == typename type_right::type_right());
  }
};

// Type TypeAND
template <typename TL, typename TRL, typename TRR>
struct TypeEQUAL<Type<TL>, TypeAND<TRL, TRR>> {
  using type_left = Type<TL>;
  using type_right = TypeAND<TRL, TRR>;

  constexpr TypeEQUAL() {}

  constexpr operator bool() {
    return static_cast<bool>(type_left() == typename type_right::type_left())
        && static_cast<bool>(type_left() == typename type_right::type_right());
  }
};

// TypeOR Type
template <typename TLL, typename TLR, typename TR>
struct TypeEQUAL<TypeOR<TLL, TLR>, Type<TR>> {
  using type_left = TypeOR<TLL, TLR>;
  using type_right = Type<TR>;

  constexpr TypeEQUAL() {}

  constexpr operator bool() {
    return static_cast<bool>(typename type_left::type_left() == type_right())
        || static_cast<bool>(typename type_left::type_right() == type_right());
  }
};

// TypeOR TypeNOT
template <typename TLL, typename TLR, typename TR>
struct TypeEQUAL<TypeOR<TLL, TLR>, TypeNOT<TR>> {
  using type_left = TypeOR<TLL, TLR>;
  using type_right = TypeNOT<TR>;

  constexpr TypeEQUAL() {}

  constexpr operator bool() {
    return static_cast<bool>(typename type_left::type_left() == type_right())
        || static_cast<bool>(typename type_left::type_right() == type_right());
  }
};


// TypeOR TypeOR
template <typename TLL, typename TLR, typename TRL, typename TRR>
struct TypeEQUAL<TypeOR<TLL, TLR>, TypeOR<TRL, TRR>> {
  using type_left = TypeOR<TLL, TLR>;
  using type_right = TypeOR<TRL, TRR>;

  constexpr TypeEQUAL() {}

  constexpr operator bool() {
    return static_cast<bool>(typename type_left::type_left() == type_right())
        || static_cast<bool>(typename type_left::type_right() == type_right());
  }
};

// TypeOR TypeAND
template <typename TLL, typename TLR, typename TRL, typename TRR>
struct TypeEQUAL<TypeOR<TLL, TLR>, TypeAND<TRL, TRR>> {
  using type_left = TypeOR<TLL, TLR>;
  using type_right = TypeAND<TRL, TRR>;

  constexpr TypeEQUAL() {}

  constexpr operator bool() {
    return static_cast<bool>(typename type_left::type_left() == type_right())
        || static_cast<bool>(typename type_left::type_right() == type_right());
  }
};

// TypeAND Type
template <typename TLL, typename TLR, typename TR>
struct TypeEQUAL<TypeAND<TLL, TLR>, Type<TR>> {
  using type_left = TypeAND<TLL, TLR>;
  using type_right = Type<TR>;

  constexpr TypeEQUAL() {}

  constexpr operator bool() {
    return static_cast<bool>(typename type_left::type_left() == type_right())
        && static_cast<bool>(typename type_left::type_right() == type_right());
  }
};

// TypeAND TypeNOT
template <typename TLL, typename TLR, typename TR>
struct TypeEQUAL<TypeAND<TLL, TLR>, TypeNOT<TR>> {
  using type_left = TypeAND<TLL, TLR>;
  using type_right = TypeNOT<TR>;

  constexpr TypeEQUAL() {}

  constexpr operator bool() {
    return static_cast<bool>(typename type_left::type_left() == type_right())
        && static_cast<bool>(typename type_left::type_right() == type_right());
  }
};

// TypeAND TypeOR
template <typename TLL, typename TLR, typename TRL, typename TRR>
struct TypeEQUAL<TypeAND<TLL, TLR>, TypeOR<TRL, TRR>> {
  using type_left = TypeAND<TLL, TLR>;
  using type_right = TypeOR<TRL, TRR>;

  constexpr TypeEQUAL() {}

  constexpr operator bool() {
    return static_cast<bool>(typename type_left::type_left() == type_right())
        && static_cast<bool>(typename type_left::type_right() == type_right());
  }
};

// TypeAND TypeAND
template <typename TLL, typename TLR, typename TRL, typename TRR>
struct TypeEQUAL<TypeAND<TLL, TLR>, TypeAND<TRL, TRR>> {
  using type_left = TypeAND<TLL, TLR>;
  using type_right = TypeAND<TRL, TRR>;

  constexpr TypeEQUAL() {}

  constexpr operator bool() {
    return static_cast<bool>(typename type_left::type_left() == type_right())
        && static_cast<bool>(typename type_left::type_right() == type_right());
  }
};


//
// EQUAL
//

// Type Type
template <typename TL, typename TR>
constexpr auto operator==(Type<TL>, Type<TR>) {
  return TypeEQUAL<Type<TL>, Type<TR>>();
}
// Type TypeNOT
template <typename TL, typename TR>
constexpr auto operator==(Type<TL>, TypeNOT<TR>) {
  return TypeEQUAL<Type<TL>, TypeNOT<TR>>();
}
// Type TypeOR
template <typename TL, typename TRL, typename TRR>
constexpr auto operator==(Type<TL>, TypeOR<TRL, TRR>) {
  return TypeEQUAL<Type<TL>, TypeOR<TRL, TRR>>();
}
// Type TypeAND
template <typename TL, typename TRL, typename TRR>
constexpr auto operator==(Type<TL>, TypeAND<TRL, TRR>) {
  return TypeEQUAL<Type<TL>, TypeAND<TRL, TRR>>();
}
// TypeNOT Type
template <typename TL, typename TR>
constexpr auto operator==(TypeNOT<TL>, Type<TR>) {
  return TypeEQUAL<TypeNOT<TL>, Type<TR>>();
}
// TypeNOT TypeNOT
template <typename TL, typename TR>
constexpr auto operator==(TypeNOT<TL>, TypeNOT<TR>) {
  return TypeEQUAL<TypeNOT<TL>, TypeNOT<TR>>();
}
// TypeNOT TypeOR
template <typename TL, typename TRL, typename TRR>
constexpr auto operator==(TypeNOT<TL>, TypeOR<TRL, TRR>) {
  return TypeEQUAL<TypeNOT<TL>, TypeOR<TRL, TRR>>();
}
// TypeNOT TypeAND
template <typename TL, typename TRL, typename TRR>
constexpr auto operator==(TypeNOT<TL>, TypeAND<TRL, TRR>) {
  return TypeEQUAL<TypeNOT<TL>, TypeAND<TRL, TRR>>();
}
// TypeOR Type
template <typename TLL, typename TLR, typename TR>
constexpr auto operator==(TypeOR<TLL, TLR>, Type<TR>) {
  return TypeEQUAL<TypeOR<TLL, TLR>, Type<TR>>();
}
// TypeOR TypeNOT
template <typename TLL, typename TLR, typename TR>
constexpr auto operator==(TypeOR<TLL, TLR>, TypeNOT<TR>) {
  return TypeEQUAL<TypeOR<TLL, TLR>, TypeNOT<TR>>();
}
// TypeOR TypeOR
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator==(TypeOR<TLL, TLR>, TypeOR<TRL, TRR>) {
  return TypeEQUAL<TypeOR<TLL, TLR>, TypeOR<TRL, TRR>>();
}
// TypeOR TypeAND
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator==(TypeOR<TLL, TLR>, TypeAND<TRL, TRR>) {
  return TypeEQUAL<TypeOR<TLL, TLR>, TypeAND<TRL, TRR>>();
}
// TypeAND Type
template <typename TLL, typename TLR, typename TR>
constexpr auto operator==(TypeAND<TLL, TLR>, Type<TR>) {
  return TypeEQUAL<TypeAND<TLL, TLR>, Type<TR>>();
}
// TypeAND TypeNOT
template <typename TLL, typename TLR, typename TR>
constexpr auto operator==(TypeAND<TLL, TLR>, TypeNOT<TR>) {
  return TypeEQUAL<TypeAND<TLL, TLR>, TypeNOT<TR>>();
}
// TypeAND TypeOR
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator==(TypeAND<TLL, TLR>, TypeOR<TRL, TRR>) {
  return TypeEQUAL<TypeAND<TLL, TLR>, TypeOR<TRL, TRR>>();
}
// TypeAND TypeAND
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator==(TypeAND<TLL, TLR>, TypeAND<TRL, TRR>) {
  return TypeEQUAL<TypeAND<TLL, TLR>, TypeAND<TRL, TRR>>();
}


//
// NOT EQUAL
//

// Type Type
template <typename TL, typename TR>
constexpr auto operator!=(Type<TL>, Type<TR>) {
  return !TypeEQUAL<Type<TL>, Type<TR>>();
}
// Type TypeNOT
template <typename TL, typename TR>
constexpr auto operator!=(Type<TL>, TypeNOT<TR>) {
  return !TypeEQUAL<Type<TL>, TypeNOT<TR>>();
}
// Type TypeOR
template <typename TL, typename TRL, typename TRR>
constexpr auto operator!=(Type<TL>, TypeOR<TRL, TRR>) {
  return !TypeEQUAL<Type<TL>, TypeOR<TRL, TRR>>();
}
// Type TypeAND
template <typename TL, typename TRL, typename TRR>
constexpr auto operator!=(Type<TL>, TypeAND<TRL, TRR>) {
  return !TypeEQUAL<Type<TL>, TypeAND<TRL, TRR>>();
}
// TypeNOT Type
template <typename TL, typename TR>
constexpr auto operator!=(TypeNOT<TL>, Type<TR>) {
  return !TypeEQUAL<TypeNOT<TL>, Type<TR>>();
}
// TypeNOT TypeNOT
template <typename TL, typename TR>
constexpr auto operator!=(TypeNOT<TL>, TypeNOT<TR>) {
  return !TypeEQUAL<TypeNOT<TL>, TypeNOT<TR>>();
}
// TypeNOT TypeOR
template <typename TL, typename TRL, typename TRR>
constexpr auto operator!=(TypeNOT<TL>, TypeOR<TRL, TRR>) {
  return !TypeEQUAL<TypeNOT<TL>, TypeOR<TRL, TRR>>();
}
// TypeNOT TypeAND
template <typename TL, typename TRL, typename TRR>
constexpr auto operator!=(TypeNOT<TL>, TypeAND<TRL, TRR>) {
  return !TypeEQUAL<TypeNOT<TL>, TypeAND<TRL, TRR>>();
}
// TypeOR Type
template <typename TLL, typename TLR, typename TR>
constexpr auto operator!=(TypeOR<TLL, TLR>, Type<TR>) {
  return !TypeEQUAL<TypeOR<TLL, TLR>, Type<TR>>();
}
// TypeOR TypeNOT
template <typename TLL, typename TLR, typename TR>
constexpr auto operator!=(TypeOR<TLL, TLR>, TypeNOT<TR>) {
  return !TypeEQUAL<TypeOR<TLL, TLR>, TypeNOT<TR>>();
}
// TypeOR TypeOR
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator!=(TypeOR<TLL, TLR>, TypeOR<TRL, TRR>) {
  return !TypeEQUAL<TypeOR<TLL, TLR>, TypeOR<TRL, TRR>>();
}
// TypeOR TypeAND
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator!=(TypeOR<TLL, TLR>, TypeAND<TRL, TRR>) {
  return !TypeEQUAL<TypeOR<TLL, TLR>, TypeAND<TRL, TRR>>();
}
// TypeAND Type
template <typename TLL, typename TLR, typename TR>
constexpr auto operator!=(TypeAND<TLL, TLR>, Type<TR>) {
  return !TypeEQUAL<TypeAND<TLL, TLR>, Type<TR>>();
}
// TypeAND TypeNOT
template <typename TLL, typename TLR, typename TR>
constexpr auto operator!=(TypeAND<TLL, TLR>, TypeNOT<TR>) {
  return !TypeEQUAL<TypeAND<TLL, TLR>, TypeNOT<TR>>();
}
// TypeAND TypeOR
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator!=(TypeAND<TLL, TLR>, TypeOR<TRL, TRR>) {
  return !TypeEQUAL<TypeAND<TLL, TLR>, TypeOR<TRL, TRR>>();
}
// TypeAND TypeAND
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator!=(TypeAND<TLL, TLR>, TypeAND<TRL, TRR>) {
  return !TypeEQUAL<TypeAND<TLL, TLR>, TypeAND<TRL, TRR>>();
}


//
// NOT
//

// Type
template <typename T>
constexpr auto operator!(Type<T>) {
  return TypeNOT<T>();
}
// TypeNOT
template <typename T>
constexpr auto operator!(TypeNOT<T>) {
  return T();
}
// TypeEQUAL
template <typename TL, typename TR>
constexpr auto operator!(TypeEQUAL<TL, TR>) {
  return TypeNOT<TypeEQUAL<TL, TR>>();
}
// TypeOR
template <typename TL, typename TR>
constexpr auto operator!(TypeOR<TL, TR>) {
  return TypeNOT<TypeOR<TL, TR>>();
}
// TypeAND
template <typename TL, typename TR>
constexpr auto operator!(TypeAND<TL, TR>) {
  return TypeNOT<TypeAND<TL, TR>>();
}


//
// OR
//

// Type Type
template <typename TL, typename TR>
constexpr auto operator||(Type<TL>, Type<TR>) {
  return TypeOR<Type<TL>, Type<TR>>();
}
// Type TypeNOT
template <typename TL, typename TR>
constexpr auto operator||(Type<TL>, TypeNOT<TR>) {
  return TypeOR<Type<TL>, TypeNOT<TR>>();
}
// Type TypeOR
template <typename TL, typename TRL, typename TRR>
constexpr auto operator||(Type<TL>, TypeOR<TRL, TRR>) {
  return TypeOR<Type<TL>, TypeOR<TRL, TRR>>();
}
// Type TypeAND
template <typename TL, typename TRL, typename TRR>
constexpr auto operator||(Type<TL>, TypeAND<TRL, TRR>) {
  return TypeOR<Type<TL>, TypeAND<TRL, TRR>>();
}
// TypeNOT Type
template <typename TL, typename TR>
constexpr auto operator||(TypeNOT<TL>, Type<TR>) {
  return TypeOR<TypeNOT<TL>, Type<TR>>();
}
// TypeNOT TypeNOT
template <typename TL, typename TR>
constexpr auto operator||(TypeNOT<TL>, TypeNOT<TR>) {
  return TypeOR<TypeNOT<TL>, TypeNOT<TR>>();
}
// TypeNOT TypeOR
template <typename TL, typename TRL, typename TRR>
constexpr auto operator||(TypeNOT<TL>, TypeOR<TRL, TRR>) {
  return TypeOR<TypeNOT<TL>, TypeOR<TRL, TRR>>();
}
// TypeNOT TypeAND
template <typename TL, typename TRL, typename TRR>
constexpr auto operator||(TypeNOT<TL>, TypeAND<TRL, TRR>) {
  return TypeOR<TypeNOT<TL>, TypeAND<TRL, TRR>>();
}
// TypeOR Type
template <typename TLL, typename TLR, typename TR>
constexpr auto operator||(TypeOR<TLL, TLR>, Type<TR>) {
  return TypeOR<TypeOR<TLL, TLR>, Type<TR>>();
}
// TypeOR TypeNOT
template <typename TLL, typename TLR, typename TR>
constexpr auto operator||(TypeOR<TLL, TLR>, TypeNOT<TR>) {
  return TypeOR<TypeOR<TLL, TLR>, TypeNOT<TR>>();
}
// TypeOR TypeOR
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator||(TypeOR<TLL, TLR>, TypeOR<TRL, TRR>) {
  return TypeOR<TypeOR<TLL, TLR>, TypeOR<TRL, TRR>>();
}
// TypeOR TypeAND
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator||(TypeOR<TLL, TLR>, TypeAND<TRL, TRR>) {
  return TypeOR<TypeOR<TLL, TLR>, TypeAND<TRL, TRR>>();
}
// TypeAND Type
template <typename TLL, typename TLR, typename TR>
constexpr auto operator||(TypeAND<TLL, TLR>, Type<TR>) {
  return TypeOR<TypeAND<TLL, TLR>, Type<TR>>();
}
// TypeAND TypeOR
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator||(TypeAND<TLL, TLR>, TypeOR<TRL, TRR>) {
  return TypeOR<TypeAND<TLL, TLR>, TypeOR<TRL, TRR>>();
}
// TypeAND TypeAND
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator||(TypeAND<TLL, TLR>, TypeAND<TRL, TRR>) {
  return TypeOR<TypeAND<TLL, TLR>, TypeAND<TRL, TRR>>();
}


//
// AND
//

// Type Type
template <typename TL, typename TR>
constexpr auto operator&&(Type<TL>, Type<TR>) {
  return TypeAND<Type<TL>, Type<TR>>();
}
// Type TypeNOT
template <typename TL, typename TR>
constexpr auto operator&&(Type<TL>, TypeNOT<TR>) {
  return TypeAND<Type<TL>, TypeNOT<TR>>();
}
// Type TypeOR
template <typename TL, typename TRL, typename TRR>
constexpr auto operator&&(Type<TL>, TypeOR<TRL, TRR>) {
  return TypeAND<Type<TL>, TypeOR<TRL, TRR>>();
}
// Type TypeAND
template <typename TL, typename TRL, typename TRR>
constexpr auto operator&&(Type<TL>, TypeAND<TRL, TRR>) {
  return TypeAND<Type<TL>, TypeAND<TRL, TRR>>();
}
// TypeNOT Type
template <typename TL, typename TR>
constexpr auto operator&&(TypeNOT<TL>, Type<TR>) {
  return TypeAND<TypeNOT<TL>, Type<TR>>();
}
// TypeNOT TypeNOT
template <typename TL, typename TR>
constexpr auto operator&&(TypeNOT<TL>, TypeNOT<TR>) {
  return TypeAND<TypeNOT<TL>, TypeNOT<TR>>();
}
// TypeNOT TypeOR
template <typename TL, typename TRL, typename TRR>
constexpr auto operator&&(TypeNOT<TL>, TypeOR<TRL, TRR>) {
  return TypeAND<TypeNOT<TL>, TypeOR<TRL, TRR>>();
}
// TypeNOT TypeAND
template <typename TL, typename TRL, typename TRR>
constexpr auto operator&&(TypeNOT<TL>, TypeAND<TRL, TRR>) {
  return TypeAND<TypeNOT<TL>, TypeAND<TRL, TRR>>();
}
// TypeOR Type
template <typename TLL, typename TLR, typename TR>
constexpr auto operator&&(TypeOR<TLL, TLR>, Type<TR>) {
  return TypeAND<TypeOR<TLL, TLR>, Type<TR>>();
}
// TypeOR TypeNOT
template <typename TLL, typename TLR, typename TR>
constexpr auto operator&&(TypeOR<TLL, TLR>, TypeNOT<TR>) {
  return TypeAND<TypeOR<TLL, TLR>, TypeNOT<TR>>();
}
// TypeOR TypeOR
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator&&(TypeOR<TLL, TLR>, TypeOR<TRL, TRR>) {
  return TypeAND<TypeOR<TLL, TLR>, TypeOR<TRL, TRR>>();
}
// TypeOR TypeAND
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator&&(TypeOR<TLL, TLR>, TypeAND<TRL, TRR>) {
  return TypeAND<TypeOR<TLL, TLR>, TypeAND<TRL, TRR>>();
}
// TypeAND Type
template <typename TLL, typename TLR, typename TR>
constexpr auto operator&&(TypeAND<TLL, TLR>, Type<TR>) {
  return TypeAND<TypeAND<TLL, TLR>, Type<TR>>();
}
// TypeAND TypeNOT
template <typename TLL, typename TLR, typename TR>
constexpr auto operator&&(TypeAND<TLL, TLR>, TypeNOT<TR>) {
  return TypeAND<TypeAND<TLL, TLR>, TypeNOT<TR>>();
}
// TypeAND TypeOR
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator&&(TypeAND<TLL, TLR>, TypeOR<TRL, TRR>) {
  return TypeAND<TypeAND<TLL, TLR>, TypeOR<TRL, TRR>>();
}
// TypeAND TypeAND
template <typename TLL, typename TLR, typename TRL, typename TRR>
constexpr auto operator&&(TypeAND<TLL, TLR>, TypeAND<TRL, TRR>) {
  return TypeAND<TypeAND<TLL, TLR>, TypeAND<TRL, TRR>>();
}

