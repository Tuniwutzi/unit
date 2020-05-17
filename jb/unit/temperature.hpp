#pragma once

#include "unit_base.hpp"

namespace jb {
namespace unit {
    
namespace base_units {
struct Celsius {
    inline static const char* symbol = "°C";
};
struct Farenheit {
    inline static const char* symbol = "°F";
};
}
    
using DegreeCelsius = Unit<base_units::Celsius, std::ratio<1>, float>;
using DegreeFarenheit = Unit<base_units::Farenheit, std::ratio<1>, float>;

template<typename FROM_RATIO, typename FROM_REP, typename TO_RATIO, typename TO_REP>
class UnitConverter<Unit<base_units::Celsius, FROM_RATIO, FROM_REP>, Unit<base_units::Farenheit, TO_RATIO, TO_REP>> {
public:
    using from_unit = Unit<base_units::Celsius, FROM_RATIO, FROM_REP>;
    using to_unit = Unit<base_units::Farenheit, TO_RATIO, TO_REP>;

    using normalizing_converter = UnitConverter<from_unit, DegreeCelsius>;
    using target_converter = UnitConverter<DegreeFarenheit, to_unit>;

    static constexpr bool IsConvertible = true;
    static constexpr bool LosesPrecision = normalizing_converter::LosesPrecision || target_converter::LosesPrecision;

    static constexpr TO_REP convert(FROM_REP from) {
        // convert whichever ratio was used to represent the parameter into 1/1 ratio
        auto celsius = normalizing_converter::convert(from);

        // get fahrenheit in 1/1 ratio
        DegreeFarenheit::rep fahrenheit = (celsius * 9) / 5 + 32;

        // return fahrenheit in target ratio
        return target_converter::convert(fahrenheit);
    }
};
template<typename FROM_RATIO, typename FROM_REP, typename TO_RATIO, typename TO_REP>
class UnitConverter<Unit<base_units::Farenheit, FROM_RATIO, FROM_REP>, Unit<base_units::Celsius, TO_RATIO, TO_REP>> {
public:
    using from_unit = Unit<base_units::Farenheit, FROM_RATIO, FROM_REP>;
    using to_unit = Unit<base_units::Celsius, TO_RATIO, TO_REP>;

    using normalizing_converter = UnitConverter<from_unit, DegreeFarenheit>;
    using target_converter = UnitConverter<DegreeCelsius, to_unit>;

    static constexpr bool IsConvertible = true;
    static constexpr bool LosesPrecision = normalizing_converter::LosesPrecision || target_converter::LosesPrecision;
    
    static constexpr TO_REP convert(FROM_REP from) {
        auto fahrenheit = normalizing_converter::convert(from);

        DegreeCelsius::rep celsius = ((fahrenheit - 32) * 5) / 9;

        return target_converter::convert(celsius);
    }
};

}
}