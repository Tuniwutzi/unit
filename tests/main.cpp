#include <jb/unit.hpp>

#include <iostream>
#include <sstream>

const jb::unit::CentiMeters cm(100);
const jb::unit::Meters m(100);
const jb::unit::KiloMeters km(100);

const jb::unit::Grams g(1000);

const jb::unit::DegreeCelsius c(100);
const jb::unit::DegreeFarenheit f(100);


template<auto N>
const std::string& numberAsPowerOf10() {
    static const auto rv  = []() -> std::string {
        if constexpr (N == 0) {
            return "0";
        }
        
        static_assert(N > 0, "N < 0 not implemented");

        uint32_t power = 0;
        decltype(N) rem = 0;

        auto n = N;
        while (rem == 0) {
            auto result = std::div(n, decltype(N)(10));

            if (result.rem == 0) {
                power++;
                n = result.quot;
            } else {
                rem = result.rem;
            }
        }

        std::stringstream ss;
        if (rem > 1) {
            ss << rem << "*";
        }
        if (power > 0) {
            ss << "10";
            if (power > 1){
                ss << "^" << power;
            }
        }

        return ss.str();
    }();

    return rv;
}
template<typename RATIO>
const std::string& ratioString(bool& knownRatioString) {
    static const auto rv = []() -> std::pair<std::string, bool> {
        std::string rv;
        if constexpr (std::is_same_v<RATIO, std::milli>) {
            rv = "m";
        } else if constexpr (std::is_same_v<RATIO, std::centi>) {
            rv = "c";
        } else if constexpr (std::is_same_v<RATIO, std::kilo>) {
            rv = "k";
        }

        if (!rv.empty()) {
            return {
                std::move(rv),
                true
            };
        }

        constexpr auto num = RATIO::num;
        constexpr auto den = RATIO::den;


        rv = numberAsPowerOf10<num>();
        if constexpr (den != 1) {
            if (rv.empty()) {
                rv = "1";
            }
            rv += "/" + numberAsPowerOf10<den>();

            rv = "(" + rv + ")";
        }

        return {
            std::move(rv),
            false
        };
    }();

    knownRatioString = rv.second;
    return rv.first;
}

template<typename BASE_UNIT>
const std::string& baseUnitString() {
    static const auto rv = []() -> std::string {
        // using jb::unit::base_units;
        return BASE_UNIT::symbol;
    }();

    return rv;
}

template<typename BASE_UNIT, typename RATIO, typename REP>
std::ostream& operator<<(std::ostream& s, const jb::unit::Unit<BASE_UNIT, RATIO, REP>& unit) {
    s << unit.count();


    bool knownRatioString;
    static const auto& ratioStringRef = ratioString<RATIO>(knownRatioString);

    if (ratioStringRef.empty()) {
        s << baseUnitString<BASE_UNIT>();

    } else if (!knownRatioString) {
        s << "(" << baseUnitString<BASE_UNIT>() << "*" << ratioStringRef << ")";
    } else {
        s << ratioStringRef << baseUnitString<BASE_UNIT>();
    }

    return s;
}


void implicitConversions() {
    jb::unit::Meters v(10);

    // Not allowed:
    // v = cm;
    // v = g;
    // v = 5;
    
    // Allowed:
    v = m;
    v = km;
}

void explicitConversions() {
    jb::unit::Meters v(10);

    // Not allowed:
    // static_cast<jb::unit::Meters>(jb::unit::Grams(5));
    
    // Allowed:
    static_cast<jb::unit::Meters>(cm);
}

void conversionBetweenBaseUnits() {
    jb::unit::DegreeCelsius c(10);
    jb::unit::DegreeFarenheit f(10);

    std::cout << c.count() << "°C, " << f.count() << "°F" << std::endl;

    c = jb::unit::DegreeFarenheit(10);
    f = jb::unit::DegreeCelsius(10);

    std::cout << c.count() << "°C, " << f.count() << "°F" << std::endl;

    jb::unit::Meters m(10);
    jb::unit::Grams g(10);

    // g = m;
    // m = g;
}

void comparisons() {
    // different units
    // m == g;
    // m == c;
    // m == f;

    // same units
    m == m;
    m == cm;
    cm == m;
    km == m;
    m == km;

    // different but comparable units
    c == f;
    f == c;
}

int main() {
    implicitConversions();
    explicitConversions();
    conversionBetweenBaseUnits();
    comparisons();

    std::cout << jb::unit::Meters(50) << std::endl;
    std::cout << jb::unit::CentiMeters(50) << std::endl;
    std::cout << jb::unit::KiloMeters(50) << std::endl;

    return 0;
}