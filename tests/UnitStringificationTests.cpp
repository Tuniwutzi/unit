#include <gtest/gtest.h>

#include <jb/unit.hpp>
#include <jb/unit_stringification.hpp>

#include "TestUnits.hpp"
#include "CompilitimeOperatorTests.hpp"

template<typename T>
static std::string tostr(T unit) {
    std::stringstream ss;
    ss << unit;
    return ss.str();
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

TEST(UnitStringificationTests, StringifyUnambiguousRelations)
{
    UnitA1 a1(0);
    UnitA2 a2(1);

    auto a1Squared = a1 * a1;
    ASSERT_EQ(tostr(a1Squared), "0(A1^2)");

    auto a1Cubed = a1Squared * a1;
    ASSERT_EQ(tostr(a1Cubed), "0(A1^3)");

    auto divided = a1Cubed / a2;
    ASSERT_EQ(tostr(divided), "0(A1^3/A2)");

    auto dividedTwice = divided / a2;
    ASSERT_EQ(tostr(dividedTwice), "0(A1^3/A2^2)");
}

TEST(UnitStringificationTests, StringifyAmbiguousRelations)
{
    using Multiplication = relations::Product<BaseUnitA1, BaseUnitA2, BaseUnitB>;
    using Division = relations::InvertT<relations::Product<BaseUnitDynamic<'x'>, BaseUnitDynamic<'y'>, BaseUnitDynamic<'z'>>>;
    using Both = relations::MultiplyT<Multiplication, Division>;

    Unit<Multiplication, std::ratio<1>, int> m(0);
    Unit<Division, std::ratio<1>, int> d(0);
    Unit<Both, std::ratio<1>, int> b(0);

    ASSERT_EQ(tostr(m), "0((A1*A2*B))");
    ASSERT_EQ(tostr(d), "0(1/(x*y*z))");
    ASSERT_EQ(tostr(b), "0((A1*A2*B)/(x*y*z))");
}
