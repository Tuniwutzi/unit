#include <gtest/gtest.h>

#include <jb/unit.hpp>

#include "TestUnits.hpp"
#include "CompilitimeOperatorTests.hpp"

TEST(UnitMultiplicationTests, SameBase_CT)
{
    ASSERT_FALSE((IsMultiplicationValidV<UnitB_m, UnitB_m>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitB_m, UnitB>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitB_m, UnitB_k>));
    
    ASSERT_FALSE((IsMultiplicationValidV<UnitB, UnitB_m>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitB, UnitB>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitB, UnitB_k>));
    
    ASSERT_FALSE((IsMultiplicationValidV<UnitB_k, UnitB_m>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitB_k, UnitB>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitB_k, UnitB_k>));
}

TEST(UnitMultiplicationTests, DifferentBase_CT)
{
    ASSERT_FALSE((IsMultiplicationValidV<UnitA1_m, UnitA2_m>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitA1_m, UnitA2>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitA1_m, UnitA2_k>));

    ASSERT_FALSE((IsMultiplicationValidV<UnitA1, UnitA2_m>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitA1, UnitA2>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitA1, UnitA2_k>));

    ASSERT_FALSE((IsMultiplicationValidV<UnitA1_k, UnitA2_m>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitA1_k, UnitA2>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitA1_k, UnitA2_k>));
    

    ASSERT_FALSE((IsMultiplicationValidV<UnitA2_m, UnitA1_m>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitA2_m, UnitA1>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitA2_m, UnitA1_k>));

    ASSERT_FALSE((IsMultiplicationValidV<UnitA2, UnitA1_m>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitA2, UnitA1>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitA2, UnitA1_k>));

    ASSERT_FALSE((IsMultiplicationValidV<UnitA2_k, UnitA1_m>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitA2_k, UnitA1>));
    ASSERT_FALSE((IsMultiplicationValidV<UnitA2_k, UnitA1_k>));
}

TEST(UnitMultiplicationTests, Arithmetic_CT)
{
    ASSERT_TRUE((ValidateMultiplicationResultV<UnitB, UnitB::rep, UnitB>));
    ASSERT_TRUE((ValidateMultiplicationResultV<UnitB::rep, UnitB, UnitB>));
}

TEST(UnitMultiplicationTests, Arithmetic_RT)
{
    const UnitB b(5);

    ASSERT_EQ(b * 3, UnitB(15));
    ASSERT_EQ(3 * b, UnitB(15));
}
