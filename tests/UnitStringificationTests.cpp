#include <gtest/gtest.h>

#include <jb/unit.hpp>
#include <jb/unit_stringification.hpp>

#include "TestUnits.hpp"
#include "CompilitimeOperatorTests.hpp"

template<typename T>
static std::string tostr(T unit) {
    return (std::stringstream() << unit).str();
}

TEST(UnitStringificationTests, StringifyKnownRatios)
{
    UnitA1 a1(0);
    UnitA1_k a1_k(0);
    UnitA1_m a1_m(0);

    ASSERT_EQ(tostr(a1), "0A1");
    ASSERT_EQ(tostr(a1_k), "0kA1");
    ASSERT_EQ(tostr(a1_m), "0mA1");
}

TEST(UnitStringificationTests, StringifyArbitratyRatios)
{
    Unit<BaseUnitA1, std::ratio<7, 13>, int> no_shorten(0);
    ASSERT_EQ(tostr(no_shorten), "0(A1*(7/13))");

    Unit<BaseUnitA1, std::ratio<700, 130000>, int> shorten(0);
    ASSERT_EQ(tostr(shorten), "0(A1*(7/1300))");

    Unit<BaseUnitA1, std::ratio<7, 1000>, int> power_den(0);
    ASSERT_EQ(tostr(power_den), "0(A1*(7/10^3))");

    Unit<BaseUnitA1, std::ratio<100, 13>, int> power_num(0);
    ASSERT_EQ(tostr(power_num), "0(A1*(10^2/13))");
}
