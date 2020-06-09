#pragma once

#include "conversion.hpp"

#include <ratio>

namespace jb {
namespace unit {

template<typename BASE_UNIT, typename RATIO, typename REP>
struct Unit {
public:
    using base_unit = BASE_UNIT;
    using ratio = RATIO;
    using rep = REP;

    static_assert(!std::is_same_v<BASE_UNIT, void>, "Base unit must not be void");


    explicit Unit(REP count)
        :_count(count) {
    }

    template<typename TO_UNIT>
    using ConverterTo = UnitConverter<Unit, TO_UNIT>;

    template<typename TO_UNIT>
    static constexpr bool IsConvertibleTo = ConverterTo<TO_UNIT>::IsConvertible;
    template<typename TO_UNIT>
    static constexpr bool IsImplicitlyConvertibleTo = IsConvertibleTo<TO_UNIT> && !ConverterTo<TO_UNIT>::LosesPrecision;
    template<typename TO_UNIT>
    static constexpr bool IsExplicitlyConvertibleTo = IsConvertibleTo<TO_UNIT> && ConverterTo<TO_UNIT>::LosesPrecision;

    template<typename TO_BASE_UNIT, typename TO_RATIO, typename TO_REP,
             void* = std::enable_if_t<IsImplicitlyConvertibleTo<Unit<TO_BASE_UNIT, TO_RATIO, TO_REP>>, void*>(0)>
    operator Unit<TO_BASE_UNIT, TO_RATIO, TO_REP>() const {
        using to_unit = Unit<TO_BASE_UNIT, TO_RATIO, TO_REP>;
        return to_unit(ConverterTo<to_unit>::convert(_count));
    }
    template<typename TO_BASE_UNIT, typename TO_RATIO, typename TO_REP,
             int* = std::enable_if_t<IsExplicitlyConvertibleTo<Unit<TO_BASE_UNIT, TO_RATIO, TO_REP>>, int*>(0)>
    explicit operator Unit<TO_BASE_UNIT, TO_RATIO, TO_REP>() const {
        
        using to_unit = Unit<TO_BASE_UNIT, TO_RATIO, TO_REP>;
        return to_unit(ConverterTo<to_unit>::convert(_count));
    }


    template<typename OTHER>
    bool operator!=(const OTHER& other) const {
        return !(*this == other);
    }


    template<typename OTHER>
    auto& operator+=(OTHER o) {
        return *this = (*this + o);
    }
    template<typename OTHER>
    auto& operator-=(OTHER o) {
        return *this = (*this - o);
    }
    template<typename OTHER>
    auto& operator*=(OTHER o) {
        return *this = (*this * o);
    }
    template<typename OTHER>
    auto& operator/=(OTHER o) {
        return *this = (*this / o);
    }

    REP count() const {
        return _count;
    }


private:
    REP _count;
};

template<typename T>
struct IsUnit : public std::false_type {};
template<typename BASE_UNIT, typename RATIO, typename REP>
struct IsUnit<Unit<BASE_UNIT, RATIO, REP>> : public std::true_type {};
template<typename T>
constexpr bool IsUnitV = IsUnit<T>::value;

}
}