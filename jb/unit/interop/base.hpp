#pragma once

#include "../unit_base.hpp"

namespace jb {
namespace unit {
namespace interop {

template<typename UNIT>
struct ResolveBaseUnit;
template<typename UNIT>
using ResolveBaseUnitT = typename ResolveBaseUnit<UNIT>::type;

template<typename BASE_UNIT, typename RATIO, typename REP>
struct MakeUnit;
template<typename BASE_UNIT, typename RATIO, typename REP>
using MakeUnitT = typename MakeUnit<UNIT>::type;





template<typename BASE_UNIT, typename RATIO, typename REP>
struct ResolveBaseUnit<Unit<BASE_UNIT, RATIO, REP>> {
    using type = BASE_UNIT;
};




template<typename BASE_UNIT, typename RATIO, typename REP>
struct MakeUnit {
    using type = Unit<BASE_UNIT, RATIO, REP>;
};



}
}
}
