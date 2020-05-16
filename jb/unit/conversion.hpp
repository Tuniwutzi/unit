#pragma once

#include <ratio>
#include <type_traits>

namespace jb {
namespace unit {

    
template<typename BASE_UNIT, typename RATIO, typename REP>
struct Unit;

template<typename FROM_UNIT, typename TO_UNIT>
struct UnitConverter {
    static constexpr bool IsConvertible = false;
    static constexpr bool LosesPrecision = false;
};

// default implementation for the same base_unit
template<typename BASE_UNIT, typename FROM_RATIO, typename FROM_REP, typename TO_RATIO, typename TO_REP>
struct UnitConverter<Unit<BASE_UNIT, FROM_RATIO, FROM_REP>, Unit<BASE_UNIT, TO_RATIO, TO_REP>> {
    using from_base_unit = BASE_UNIT;
    using to_base_unit = BASE_UNIT;

    using from_ratio = FROM_RATIO;
    using to_ratio = TO_RATIO;

    using from_rep = FROM_REP;
    using to_rep = TO_REP;

    static constexpr bool IsConvertible = true;
    static constexpr bool LosesPrecision = std::ratio_less_v<from_ratio, to_ratio>;

    static constexpr to_rep convert(from_rep from) {
        using ConversionRatio = std::ratio_divide<from_ratio, to_ratio>;
        return to_rep((ConversionRatio::num * from) / ConversionRatio::den);
    }
};

// template<typename FROM_UNIT, typename TO_UNIT>
// using IsConvertibleV = UnitConverter<FROM_UNIT, TO_UNIT>::IsConvertible;

// template<typename FROM_UNIT, typename TO_UNIT>
// using LosesPrecisionV = UnitConverter<FROM_UNIT, TO_UNIT>::LosesPrecision;

}
}