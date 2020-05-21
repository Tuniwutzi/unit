#pragma once

#include "unit_base.hpp"

#include <type_traits>

namespace jb {
namespace unit {
        

template<typename UNIT_A, typename UNIT_B,
         typename = std::enable_if_t<IsUnitV<UNIT_A> && IsUnitV<UNIT_B> && (UNIT_A::IsImplicitlyConvertibleTo<UNIT_B> || UNIT_B::IsImplicitlyConvertibleTo<UNIT_A>)>>
bool operator==(const UNIT_A& a, const UNIT_B& b) {
    if constexpr (UNIT_A::IsImplicitlyConvertibleTo<UNIT_B>) {
        return typename UNIT_A::ConverterTo<UNIT_B>::convert(a.count()) == b.count();
    } else {
        return a.count() == typename UNIT_B::ConverterTo<UNIT_A>::convert(b.count());
    }
}

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

}
}