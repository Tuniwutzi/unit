#pragma once

#include "unit_relations.hpp"
#include "conversion.hpp"

// Unambiguous Product: an ordered, non-trivial product with one distinct base unit and one distinct inverse, as in Product<N, N, ...., N, Inverse<D>, Inverse<D>, ..., Inverse<D>>
// Unambiguous Expression: a normalized expression where the product, if it exists, is unambiguous

// the generic operators * and / are only defined when the result is an unambiguous expression

namespace jb {
namespace unit {

namespace _helpers {

template<typename NORMALIZED_EXPRESSION>
struct IsValidResult : public std::true_type {};
template<typename... FACTORS>
struct IsValidResult<relations::Product<FACTORS...>> {
    using product = relations::Product<FACTORS...>;
    static constexpr bool value = product::numerators::distinct::size <= 1 && product::denominators::distinct::size <= 1;
};
template<typename NORMALIZED_EXPRESSION>
constexpr bool IsValidResultV = IsValidResult<NORMALIZED_EXPRESSION>::value;

}

template<typename UNIT_A, typename UNIT_B,
         typename = std::enable_if_t<_helpers::IsValidResultV<relations::DivideT<typename UNIT_A::base_unit, typename UNIT_B::base_unit>>>>
auto operator/(UNIT_A a, UNIT_B b) {
    using base_unit_result = relations::DivideT<typename UNIT_A::base_unit, typename UNIT_B::base_unit>;
    using ratio_result = typename std::ratio_divide<typename UNIT_A::ratio, typename UNIT_B::ratio>::type;

    auto result = a.count() / b.count();
    if constexpr (std::is_same_v<base_unit_result, void>) {
        return (ratio_result::num * result) / ratio_result::den;
    } else {
        return Unit<base_unit_result, ratio_result, decltype(result)>(result);
    }
}

template<typename UNIT_A, typename UNIT_B,
         typename = std::enable_if_t<_helpers::IsValidResultV<relations::MultiplyT<typename UNIT_A::base_unit, typename UNIT_B::base_unit>>>>
auto operator*(UNIT_A a, UNIT_B b) {
    using base_unit_result = relations::MultiplyT<typename UNIT_A::base_unit, typename UNIT_B::base_unit>;
    using ratio_result = typename std::ratio_multiply<typename UNIT_A::ratio, typename UNIT_B::ratio>::type;

    auto result = a.count() * b.count();
    if constexpr (std::is_same_v<base_unit_result, void>) {
        return (ratio_result::num * result) / ratio_result::den;
    } else {
        return Unit<base_unit_result, ratio_result, decltype(result)>(result);
    }
}

}
}
