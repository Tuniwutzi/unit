#pragma once

#include "unit_relations.hpp"

namespace jb {
namespace unit {

namespace _helpers {

template<typename NORMALIZED_EXPRESSION>
struct IsValidResult : public std::true_type {};
template<>
struct IsValidResult<void> : public std::false_type {};
template<typename... FACTORS>
struct IsValidResult<Product<FACTORS...>> {
    using product = Product<FACTORS...>;
    static constexpr bool value = product::numerators::distinct::size <= 1 && product::denominators::distinct::size <= 1;
};
template<typename NORMALIZED_EXPRESSION>
constexpr bool IsValidResultV = IsValidResult<NORMALIZED_EXPRESSION>::value;

}

// template<typename UNIT_A, typename UNIT_B,
//          typename = std::enable_if_t<_helpers::IsValidResultV<MultiplyT<typename UNIT_A::base_unit, typename UNIT_B::base_unit>>>>
// auto operator*(UNIT_A a, UNIT_B b) {
//     using base_unit = MultiplyT<typename UNIT_A::base_unit, typename UNIT_B::base_unit>;

//     if constexpr (UNIT_A::IsImplicitlyConvertibleTo<UNIT_B>) {
//         auto ac = typename UNIT_A::ConverterTo<UNIT_B>::convert(a.count());
//         auto res = ac * b.count();
//         return Unit<base_unit, typename UNIT_B::ratio, decltype(res)>(res);
//     } else if constexpr (UNIT_B::IsImplicitlyConvertibleTo<UNIT_A>) {
//         auto bc = typename UNIT_B::ConverterTo<UNIT_A>::convert(b.count());
//         auto res = a.count() * bc;
//         return Unit<base_unit, typename UNIT_A::ratio, decltype(res)>(res);
//     }
// }

template<typename UNIT_A, typename UNIT_B,
         typename = std::enable_if_t<_helpers::IsValidResultV<DivideT<typename UNIT_A::base_unit, typename UNIT_B::base_unit>>>>
auto operator/(UNIT_A a, UNIT_B b) {
    using base_unit_result = DivideT<typename UNIT_A::base_unit, typename UNIT_B::base_unit>;
    using ratio_result = typename std::ratio_divide<typename UNIT_A::ratio, typename UNIT_B::ratio>::type;

    auto result = a.count() / b.count();
    return Unit<base_unit_result, ratio_result, decltype(result)>(result);
}


// template<typename UNIT_A, typename UNIT_B,
//          typename = std::enable_if_t<std::is_same_v<typename UNIT_A::base_unit, typename UNIT_B::base_unit>>>
// auto operator*(UNIT_A a, UNIT_B b) {
//     if constexpr (UNIT_A::IsImplicitlyConvertibleTo<UNIT_B>) {
//         auto ac = typename UNIT_A::ConverterTo<UNIT_B>::convert(a.count());
//         auto res = ac * b.count();
//         return Unit<PowerOf<typename UNIT_A::base_unit>, typename UNIT_B::ratio, decltype(res)>(res);
//     } else if constexpr (UNIT_B::IsImplicitlyConvertibleTo<UNIT_A>) {
//         auto bc = typename UNIT_B::ConverterTo<UNIT_A>::convert(b.count());
//         auto res = a.count() * bc;
//         return Unit<PowerOf<typename UNIT_A::base_unit>, typename UNIT_A::ratio, decltype(res)>(res);
//     }
// }

}
}