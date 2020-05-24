#pragma once

#include "unit_base.hpp"

#include <type_traits>

namespace jb {
namespace unit {
        

/**
 * Compare two units.
 * Only applicable if one is implicitly convertible to the other.
 */
template<typename UNIT_A, typename UNIT_B,
         typename = std::enable_if_t<IsUnitV<UNIT_A> && IsUnitV<UNIT_B> && (UNIT_A::IsImplicitlyConvertibleTo<UNIT_B> || UNIT_B::IsImplicitlyConvertibleTo<UNIT_A>)>>
bool operator==(const UNIT_A& a, const UNIT_B& b) {
    if constexpr (UNIT_A::IsImplicitlyConvertibleTo<UNIT_B>) {
        return typename UNIT_A::ConverterTo<UNIT_B>::convert(a.count()) == b.count();
    } else {
        return a.count() == typename UNIT_B::ConverterTo<UNIT_A>::convert(b.count());
    }
}

/**
 * Add two units.
 * Only applicable if they share the same base_unit.
 * 
 * Must not be allowed for any implicitly convertible units, as the 0-points might be different (ie celcius and fahrenheit).
 * 
 * @return the result of the addition represented in the more exact unit.
 */
template<typename UNIT_A, typename UNIT_B,
         typename = std::enable_if_t<IsUnitV<UNIT_A> && IsUnitV<UNIT_B> && std::is_same_v<typename UNIT_A::base_unit, typename UNIT_B::base_unit>>>
auto operator+(const UNIT_A& a, const UNIT_B& b) {
    using unit_a = UNIT_A;
    using unit_b = UNIT_B;

    if constexpr (unit_a::IsImplicitlyConvertibleTo<unit_b>) {
        unit_b aConverted = a;
        return unit_b(aConverted.count() + b.count());
    } else if constexpr (unit_b::IsImplicitlyConvertibleTo<unit_a>) {
        unit_a bConverted = b;
        return unit_a(a.count() + bConverted.count());

    }
}

/**
 * Subtract two units.
 * Only applicable if they share the same base_unit.
 * 
 * Must not be allowed for any implicitly convertible units, as the 0-points might be different (ie celcius and fahrenheit).
 * 
 * @return the result of the subtraction represented in the more exact of the two units.
 */
template<typename UNIT_A, typename UNIT_B,
         typename = std::enable_if_t<IsUnitV<UNIT_A> && IsUnitV<UNIT_B> && std::is_same_v<typename UNIT_A::base_unit, typename UNIT_B::base_unit>>>
auto operator-(const UNIT_A& a, const UNIT_B& b) {
    using unit_a = UNIT_A;
    using unit_b = UNIT_B;

    if constexpr (unit_a::IsImplicitlyConvertibleTo<unit_b>) {
        unit_b aConverted = a;
        return unit_b(aConverted.count() - b.count());
    } else if constexpr (unit_b::IsImplicitlyConvertibleTo<unit_a>) {
        unit_a bConverted = b;
        return unit_a(a.count() - bConverted.count());

    }
}

/**
 * Multiply a unit with an arithmetic type or an arithmetic type with a unit.
 * 
 * @return the result of the multiplication represented in the unit
 */
template<typename TYPE_A, typename TYPE_B,
         typename = std::enable_if_t<(IsUnitV<TYPE_A> && std::is_arithmetic_v<TYPE_B>) || std::is_arithmetic_v<TYPE_A> && IsUnitV<TYPE_B>>>
auto operator*(const TYPE_A& a, const TYPE_B& b) {
    if constexpr (IsUnitV<TYPE_A>) {
        return TYPE_A(a.count() * b);
    } else {
        return TYPE_B(a * b.count());
     }
}

/**
 * Divide a unit by an arithmetic type.
 * 
 * @return the unit divided by the arithmetic value
 */
template<typename TYPE_A, typename TYPE_B,
         typename = std::enable_if_t<(IsUnitV<TYPE_A> && std::is_arithmetic_v<TYPE_B>)>>
auto operator/(const TYPE_A& a, const TYPE_B& b) {
    return TYPE_A(a.count() / b);
}


}
}