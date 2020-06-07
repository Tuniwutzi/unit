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

