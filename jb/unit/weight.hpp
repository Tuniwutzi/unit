#pragma once

#include "unit_base.hpp"

namespace jb {
namespace unit {
    
namespace _base_units {
    struct Gram;
}

using MilliGrams = Unit<_base_units::Gram, std::milli, int64_t>;
using Grams = Unit<_base_units::Gram, std::ratio<1, 1>, int32_t>;
using KiloGrams = Unit<_base_units::Gram, std::kilo, int32_t>;

}
}