#include <gtest/gtest.h>

#include <jb/unit.hpp>

#include "TestUnits.hpp"
#include "CompilitimeOperatorTests.hpp"

TEST(UnitComparisonTests, SameBase_CT)
{
    ASSERT_TRUE((IsComparisonValidV<UnitB_m, UnitB_m>));
    ASSERT_TRUE((IsComparisonValidV<UnitB_m, UnitB>));
    ASSERT_TRUE((IsComparisonValidV<UnitB_m, UnitB_k>));
    
    ASSERT_TRUE((IsComparisonValidV<UnitB, UnitB_m>));
    ASSERT_TRUE((IsComparisonValidV<UnitB, UnitB>));
    ASSERT_TRUE((IsComparisonValidV<UnitB, UnitB_k>));
    
    ASSERT_TRUE((IsComparisonValidV<UnitB_k, UnitB_m>));
    ASSERT_TRUE((IsComparisonValidV<UnitB_k, UnitB>));
    ASSERT_TRUE((IsComparisonValidV<UnitB_k, UnitB_k>));
}

TEST(UnitComparisonTests, SameBase_RT)
{
    UnitB_k b1_k(5), b2_k(15);
    UnitB b1(b1_k), b2(b2_k);
    UnitB_m b1_m(b1_k), b2_m(b2_k);


    ASSERT_EQ(b1_m, b1_m);
    ASSERT_EQ(b1_m, b1);
    ASSERT_EQ(b1_m, b1_k);
    
    ASSERT_EQ(b1, b1_m);
    ASSERT_EQ(b1, b1);
    ASSERT_EQ(b1, b1_k);
    
    ASSERT_EQ(b1_k, b1_m);
    ASSERT_EQ(b1_k, b1);
    ASSERT_EQ(b1_k, b1_k);


    ASSERT_NE(b1_m, b2_m);
    ASSERT_NE(b1_m, b2);
    ASSERT_NE(b1_m, b2_k);
    
    ASSERT_NE(b1, b2_m);
    ASSERT_NE(b1, b2);
    ASSERT_NE(b1, b2_k);
    
    ASSERT_NE(b1_k, b2_m);
    ASSERT_NE(b1_k, b2);
    ASSERT_NE(b1_k, b2_k);
}

TEST(UnitComparisonTests, DifferentBase_CT)
{
    ASSERT_FALSE((IsComparisonValidV<UnitA1_m, UnitA2_m>));
    ASSERT_FALSE((IsComparisonValidV<UnitA1_m, UnitA2>));
    ASSERT_FALSE((IsComparisonValidV<UnitA1_m, UnitA2_k>));

    ASSERT_FALSE((IsComparisonValidV<UnitA1, UnitA2_m>));
    ASSERT_FALSE((IsComparisonValidV<UnitA1, UnitA2>));
    ASSERT_FALSE((IsComparisonValidV<UnitA1, UnitA2_k>));

    ASSERT_FALSE((IsComparisonValidV<UnitA1_k, UnitA2_m>));
    ASSERT_FALSE((IsComparisonValidV<UnitA1_k, UnitA2>));
    ASSERT_FALSE((IsComparisonValidV<UnitA1_k, UnitA2_k>));
    

    ASSERT_FALSE((IsComparisonValidV<UnitA2_m, UnitA1_m>));
    ASSERT_FALSE((IsComparisonValidV<UnitA2_m, UnitA1>));
    ASSERT_FALSE((IsComparisonValidV<UnitA2_m, UnitA1_k>));

    ASSERT_FALSE((IsComparisonValidV<UnitA2, UnitA1_m>));
    ASSERT_FALSE((IsComparisonValidV<UnitA2, UnitA1>));
    ASSERT_FALSE((IsComparisonValidV<UnitA2, UnitA1_k>));

    ASSERT_FALSE((IsComparisonValidV<UnitA2_k, UnitA1_m>));
    ASSERT_FALSE((IsComparisonValidV<UnitA2_k, UnitA1>));
    ASSERT_FALSE((IsComparisonValidV<UnitA2_k, UnitA1_k>));
}

TEST(UnitComparisonTests, DifferentBase_RT)
{
    // currently no implicit conversions between UnitA1 and UnitA2 allowed, so no comparison possible without explicit casts
}

TEST(UnitComparisonTests, Arithmetic_CT)
{
    ASSERT_FALSE((IsComparisonValidV<UnitB, UnitB::rep>));
}