#pragma once

#include "unit_base.hpp"

namespace jb {
namespace unit {
    
namespace base_units {
struct Meter {
    inline static const char* symbol = "m";
};
}
    
using CentiMeters = Unit<base_units::Meter, std::centi, int32_t>;
using Meters = Unit<base_units::Meter, std::ratio<1>, int32_t>;
using KiloMeters = Unit<base_units::Meter, std::kilo, int32_t>;

}
}