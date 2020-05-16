#pragma once

#include "unit_base.hpp"

namespace jb {
namespace unit {
    
namespace _base_units {
    struct Meter;
}
    
using CentiMeters = Unit<_base_units::Meter, std::centi, int32_t>;
using Meters = Unit<_base_units::Meter, std::ratio<1, 1>, int32_t>;
using KiloMeters = Unit<_base_units::Meter, std::kilo, int32_t>;

}
}