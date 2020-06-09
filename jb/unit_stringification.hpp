#pragma once

#include <jb/unit.hpp>

#include <sstream>

namespace jb{
namespace unit {
namespace _helpers {

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
                break;
            }
        }

        std::stringstream ss;
        if (n == 1) {
            if (power > 0) {
                ss << "10";
                if (power > 1){
                    ss << "^" << power;
                }
            }
        } else {
            ss << N;
        }

        return ss.str();
    }();

    return rv;
}

struct RatioString {
    std::string ratio;
    bool namedRatio;
};

// accept NUM and DEN to use the reduced ratio
// (ratio is defined such that ratio<10, 10000> != ratio<1, 1000>, but ratio<10, 10000>::num == 1 && ratio<10,10000>::den == 1000)
template<auto NUM, auto DEN>
const RatioString& ratioString() {
    static const auto rv = []() -> RatioString {
        using RATIO = std::ratio<NUM, DEN>;

        std::string rv;
        bool known = true;
        if constexpr (std::is_same_v<RATIO, std::ratio<1>>) {
            rv = "";
        } else if constexpr (std::is_same_v<RATIO, std::milli>) {
            rv = "m";
        } else if constexpr (std::is_same_v<RATIO, std::centi>) {
            rv = "c";
        } else if constexpr (std::is_same_v<RATIO, std::kilo>) {
            rv = "k";
        } else if constexpr (std::is_same_v<RATIO, std::mega>) {
            rv = "M";
        } else {
            known = false;

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
        }

        return {
            std::move(rv),
            known
        };
    }();

    return rv;
}

template<typename BASE_UNIT>
const std::string& baseUnitString(BASE_UNIT) {
    static const std::string rv = BASE_UNIT::symbol;

    return rv;
}

template<typename... FACTORS>
const std::string& baseUnitString(relations::Product<FACTORS...>);
template<typename T>
const std::string& baseUnitString(relations::Inverse<T>);

namespace {
template<typename... FACTORS>
struct ProductString;
template<typename FIRST, typename... REST>
struct ProductString<FIRST, REST...> {
    template<typename BUFFER_TYPE>
    static void append(BUFFER_TYPE& numerators, BUFFER_TYPE& denominators) {
        numerators[baseUnitString(FIRST())]++;
        ProductString<REST...>::append(numerators, denominators);
    }
};
template<typename FIRST, typename... REST>
struct ProductString<relations::Inverse<FIRST>, REST...> {
    template<typename BUFFER_TYPE>
    static void append(BUFFER_TYPE& numerators, BUFFER_TYPE& denominators) {
        denominators[baseUnitString(FIRST())]++;
        ProductString<REST...>::append(numerators, denominators);
    }
};
template<>
struct ProductString<> {
    template<typename BUFFER_TYPE>
    static void append(BUFFER_TYPE& numerators, BUFFER_TYPE& denomiators) {
    }
};
}

template<typename... FACTORS>
const std::string& baseUnitString(relations::Product<FACTORS...>) {
    static const std::string rv = []() {
        std::map<std::string, size_t> numerators, denominators;
        auto stringify = [](const auto& map) {
            std::stringstream rv;

            if (map.size() > 1) {
                rv << "(";
            }

            bool first = true;
            for (const auto& [string, power] : map) {
                if (first) {
                    first = false;
                } else {
                    rv << "*";
                }

                rv << string;
                if (power > 1) {
                    rv << "^" << power;
                }
            }

            if (map.size() > 1) {
                rv << ")";
            }

            return rv.str();
        };

        ProductString<FACTORS...>::append(numerators, denominators);

        std::string rv = "(";

        if (!numerators.empty()) {
            rv += stringify(numerators);
        } else {
            rv += "1";
        }

        if (!denominators.empty()) {
            rv += "/";

            rv += stringify(denominators);
        }

        return rv + ")";
    }();
    return rv; 
};
template<typename T>
const std::string& baseUnitString(relations::Inverse<T>) {
    static const std::string rv = []() {
        return "(1/" + baseUnitString(T()) + ")";
    }();
    return rv;
}

}
}
}

template<typename BASE_UNIT, typename RATIO, typename REP>
std::ostream& operator<<(std::ostream& s, const jb::unit::Unit<BASE_UNIT, RATIO, REP>& unit) {
    s << unit.count();

    const auto& [ratio, namedRatio] = jb::unit::_helpers::ratioString<RATIO::num, RATIO::den>();

    if (!namedRatio) {
        s << "(" << jb::unit::_helpers::baseUnitString(BASE_UNIT()) << "*" << ratio << ")";
    } else {
        s << ratio << jb::unit::_helpers::baseUnitString(BASE_UNIT());
    }

    return s;
}
