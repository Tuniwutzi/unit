#pragma once

#include <jb/unit.hpp>

#include <sstream>

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
const std::pair<std::string, bool>& ratioString() {
    static const auto rv = []() -> std::pair<std::string, bool> {
        std::string rv;
        if constexpr (std::is_same_v<RATIO, std::milli>) {
            rv = "m";
        } else if constexpr (std::is_same_v<RATIO, std::centi>) {
            rv = "c";
        } else if constexpr (std::is_same_v<RATIO, std::kilo>) {
            rv = "k";
        } else if constexpr (std::is_same_v<RATIO, std::mega>) {
            rv = "M";
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

        bool known = rv.empty();
        return {
            std::move(rv),
            known
        };
    }();

    return rv;
}

template<typename BASE_UNIT>
const std::string& baseUnitString() {
    static const std::string rv = BASE_UNIT::symbol;

    return rv;
}

template<typename BASE_UNIT, typename RATIO, typename REP>
std::ostream& operator<<(std::ostream& s, const jb::unit::Unit<BASE_UNIT, RATIO, REP>& unit) {
    s << unit.count();


    static const auto& ratioRef = ratioString<RATIO>();

    if (!ratioRef.second) {
        s << "(" << baseUnitString<BASE_UNIT>() << "*" << ratioRef.first << ")";
    } else {
        s << ratioRef.first << baseUnitString<BASE_UNIT>();
    }

    return s;
}
