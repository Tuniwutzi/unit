#pragma once

#include "conversion.hpp"

#include <ratio>

namespace jb {

namespace unit {


/*

Def.:
Einheit = BASE_UNIT
Andere Einheit = !unit_convertible_v<BASE_UNIT, OTHER_BASE_UNIT>

Zuweisung:
    Selbe Einheit:
        Wenn Genauigkeitsverlust: explizit
        Sonst: implizit
    Andere Einheit:
        /
    Arithmetic:
        /

Vergleich:
    Selbe Einheit:
        Immer
    Andere Einheit:
        /
    Arithmetic:
        /
    
+, -:
    Selbe Einheit:
        Immer, gibt genauere von beiden UnitRepresentations zurück (die mit der kleineren ratio)
    Andere Einheit:
        /
    Arithmetic:
        /

*, /:
    Selbe Einheit:
        / (Sonderfall für Meter*Meter = Quadratmeter? Und Quadratmeter/Meter = Meter? Falls es andere Einheiten mit solchem Verhalten gibt kann man es formalisieren und in der Einheit compile-time-flags hinterlegen was erlaubt ist)
    Andere Einheit:
        / (Sonderfall für Relationseinheiten; wenn wir bspw. MetersPerSecond implementieren sollte das (m/s)*s möglich sein - ergibt wieder meter. Auch das eventuell formalisieren, falls wir Geteilt-Operatoren für verschiedene Einheiten formalisieren [0 man kann beliebige Einheiten in Verhältnis stellen])
    Arithmetic:
        Immer, gibt selbe Representation zurück
        Problem: was wenn bei Division eine Kommazahl rauskommt?
            => selbes Verhalten wir wenn ich int(5) / 2 rechne => truncate! Wenn ich Meters(5) / 2 rechne bekomme ich Meters(2) raus. Falls ich die Genauigkeit haben will kann ich DeciMeters(50) / 2 rechnen.

*/


template<typename BASE_UNIT, typename RATIO, typename REP>
struct Unit {
public:
    using rep = REP;


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

template<typename UNIT, typename BASE_UNIT>
struct IsBaseUnit : public std::false_type {};
template<typename BASE_UNIT, typename RATIO, typename REP>
struct IsBaseUnit<Unit<BASE_UNIT, RATIO, REP>, BASE_UNIT> : public std::true_type {};

template<typename UNIT, typename BASE_UNIT>
constexpr bool IsBaseUnitV = IsBaseUnit<UNIT, BASE_UNIT>::value;

}

}