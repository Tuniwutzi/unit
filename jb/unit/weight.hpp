#pragma once

#include "unit_base.hpp"

namespace jb {
namespace unit {
    
namespace base_units {
struct Gram {
    inline static const char* symbol = "g";
};
}

using MilliGrams = Unit<base_units::Gram, std::milli, int64_t>;
using Grams = Unit<base_units::Gram, std::ratio<1, 1>, int32_t>;
using KiloGrams = Unit<base_units::Gram, std::kilo, int32_t>;

}
}