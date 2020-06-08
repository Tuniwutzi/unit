#include <gtest/gtest.h>

#include "TestUnits.hpp"
#include "CompilitimeOperatorTests.hpp"

#include <jb/unit/unit_relations.hpp>
#include <jb/unit/unit_relation_operators.hpp>
#include <jb/unit_stringification.hpp>


using namespace jb::unit;


using BaseUnitA1ByA2 = Product<BaseUnitA1, Inverse<BaseUnitA2>>;
using BaseUnitBSquared = Product<BaseUnitB, BaseUnitB>;
using BaseUnitBCubed = Product<BaseUnitB, BaseUnitB, BaseUnitB>;
using BaseUnitBInverted = Inverse<BaseUnitB>;


TEST(UnitRelationsTests, DivideBySameUnit) {
    UnitB b1(10), b2(5);

    auto result = b1 / b2;
    ASSERT_EQ(result, 2);
    ASSERT_TRUE((std::is_arithmetic_v<decltype(result)>));
}

TEST(UnitRelationsTests, DivideBySameUnitDifferentRatio) {
    UnitB b(10000);
    UnitB_k b_k(5);

    auto result = b / b_k;
    ASSERT_EQ(result, 2);
    ASSERT_TRUE((std::is_arithmetic_v<decltype(result)>));
}

TEST(UnitRelationsTests, DivideByOtherUnit) {
    UnitA1 a1(10);
    UnitA2 a2(5);

    auto result = a1 / a2;
    ASSERT_EQ(result.count(), 2);

    using actual_unit = decltype(result);

    using expected_unit = Unit<BaseUnitA1ByA2, std::ratio<1>, int>;
    ASSERT_TRUE((std::is_same_v<actual_unit, expected_unit>));
}

TEST(UnitRelationsTests, DivideByOtherUnitDifferentRatio) {
    UnitA1 a1(10000);
    UnitA2_k a2_k(5);

    auto result = a1 / a2_k;
    ASSERT_EQ(result.count(), 2000);

    using actual_unit = decltype(result);

    using expected_unit = Unit<BaseUnitA1ByA2, std::ratio<1, 1000>, int>;
    ASSERT_TRUE((std::is_same_v<actual_unit, expected_unit>));
}


TEST(UnitRelationsTests, MultiplyBySameUnit) {
    UnitB b1(10), b2(5), b3(3);

    auto squared = b1 * b2;

    {
        ASSERT_EQ(squared.count(), 50);
        
        using squared_unit = decltype(squared);
        using expected_unit = Unit<BaseUnitBSquared, std::ratio<1>, int>;

        ASSERT_TRUE((std::is_same_v<squared_unit, expected_unit>));
    }

    auto cubed = squared * b3;

    {
        ASSERT_EQ(cubed.count(), 150);
        
        using cubed_unit = decltype(cubed);
        using expected_unit = Unit<BaseUnitBCubed, std::ratio<1>, int>;

        ASSERT_TRUE((std::is_same_v<cubed_unit, expected_unit>));
    }
}

TEST(UnitRelationsTests, MultiplyBySameUnitDifferentRatio) {
    UnitB_m b1(10);
    UnitB b2(5);
    UnitB_k b3(3);

    auto squared = b1 * b2;

    {
        ASSERT_EQ(squared.count(), 50);
        
        using squared_unit = decltype(squared);
        using expected_unit = Unit<BaseUnitBSquared, std::milli, int>;

        ASSERT_TRUE((std::is_same_v<squared_unit, expected_unit>));
    }

    auto cubed = squared * b3;

    {
        ASSERT_EQ(cubed.count(), 150);
        
        using cubed_unit = decltype(cubed);
        using expected_unit = Unit<BaseUnitBCubed, std::ratio<1>, int>;

        ASSERT_TRUE((std::is_same_v<cubed_unit, expected_unit>));
    }
}

TEST(UnitRelationsTests, MultiplyByOtherUnit) {
    UnitA1 a1(10);
    UnitA2 a2(5);

    ASSERT_FALSE((IsMultiplicationValidV<UnitA1, UnitA2>));
}


TEST(UnitRelationsTests, MultiplyDivideMix) {
    UnitA1 a(10);
    UnitA2 b(5);
    UnitB c(3);

    auto aByB = a / b;
    ASSERT_FALSE(isMultiplicationValid(aByB, c));
    ASSERT_FALSE(isDivisionValid(aByB, c));

    auto aByBTimesB = aByB * b;
    ASSERT_TRUE((std::is_same_v<decltype(aByBTimesB), UnitA1>));

    auto aByBTimesA = aByB * a;
    {
        using expected =  Unit<Product<BaseUnitA1, BaseUnitA1, Inverse<BaseUnitA2>>, std::ratio<1>, int>;
        ASSERT_TRUE((std::is_same_v<decltype(aByBTimesA), expected>));
    }

    auto aByBByB = aByB / b;
    {
        using expected =  Unit<Product<BaseUnitA1, Inverse<BaseUnitA2>, Inverse<BaseUnitA2>>, std::ratio<1>, int>;
        ASSERT_TRUE((std::is_same_v<decltype(aByBByB), expected>));
    }
}
