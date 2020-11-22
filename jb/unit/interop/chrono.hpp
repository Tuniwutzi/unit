#pragma once


#include "base.hpp"

#include <chrono>


namespace jb {
namespace unit {

namespace base_units {

struct Second {
    static inline const char* symbol = "s";
};

}

namespace interop {

template<typename RATIO, typename REP>
struct ResolveBaseUnit<std::chrono::duration<RATIO, REP>> {
    using type = ::jb::unit::base_units::Second;
};

template<typename RATIO, typename REP>
struct MakeUnit<::jb::unit::base_units::Second, RATIO, REP>> {
    using type = std::chrono::duration<RATIO, REP>;
};

}
}
}
