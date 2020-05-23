#pragma once

#include <jb/unit.hpp>

using namespace jb::unit;

class BaseUnitA1;
class BaseUnitA2;
class BaseUnitB;

using UnitA1_m = Unit<BaseUnitA1, std::milli, int>;
using UnitA1 = Unit<BaseUnitA1, std::ratio<1>, int>;
using UnitA1_k = Unit<BaseUnitA1, std::kilo, int>;

using UnitA2_m = Unit<BaseUnitA2, std::milli, int>;
using UnitA2 = Unit<BaseUnitA2, std::ratio<1>, int>;
using UnitA2_k = Unit<BaseUnitA2, std::kilo, int>;

using UnitB_m = Unit<BaseUnitB, std::milli, int>;
using UnitB = Unit<BaseUnitB, std::ratio<1>, int>;
using UnitB_k = Unit<BaseUnitB, std::kilo, int>;

static constexpr int DifferenceA1A2 = 10;

namespace jb::unit {

// ToDo: change LosesPrecision in the custom UnitConverters so we can test if the field is evaluated correctly

template<typename FROM_RATIO, typename FROM_REP, typename TO_RATIO, typename TO_REP>
struct UnitConverter<Unit<BaseUnitA1, FROM_RATIO, FROM_REP>, Unit<BaseUnitA2, TO_RATIO, TO_REP>> {
    using normalizing_converter = typename Unit<BaseUnitA1, FROM_RATIO, FROM_REP>::template ConverterTo<UnitA1>;
    using target_converter = UnitA2::ConverterTo<Unit<BaseUnitA2, TO_RATIO, TO_REP>>;

    static constexpr bool IsConvertible = true;
    static constexpr bool LosesPrecision = true;

    static constexpr TO_REP convert(FROM_REP rep) {
        auto normalized = normalizing_converter::convert(rep);

        UnitA2::rep normalizedTarget = normalized + DifferenceA1A2;

        return target_converter::convert(normalizedTarget);
    }
};
template<typename FROM_RATIO, typename FROM_REP, typename TO_RATIO, typename TO_REP>
struct UnitConverter<Unit<BaseUnitA2, FROM_RATIO, FROM_REP>, Unit<BaseUnitA1, TO_RATIO, TO_REP>> {
    using normalizing_converter = typename Unit<BaseUnitA2, FROM_RATIO, FROM_REP>::template ConverterTo<UnitA2>;
    using target_converter = UnitA1::ConverterTo<Unit<BaseUnitA1, TO_RATIO, TO_REP>>;

    static constexpr bool IsConvertible = true;
    static constexpr bool LosesPrecision = true;

    static constexpr TO_REP convert(FROM_REP rep) {
        auto normalized = normalizing_converter::convert(rep);

        UnitA2::rep normalizedTarget = normalized - DifferenceA1A2;

        return target_converter::convert(normalizedTarget);
    }
};

}