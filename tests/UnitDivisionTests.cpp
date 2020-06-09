#include <gtest/gtest.h>

#include "TestUnits.hpp"
#include "CompilitimeOperatorTests.hpp"

TEST(UnitDivisionTests, SameBase_CT)
{
    ASSERT_FALSE((IsDivisionValidV<UnitB_m, UnitB_m>));
    ASSERT_FALSE((IsDivisionValidV<UnitB_m, UnitB>));
    ASSERT_FALSE((IsDivisionValidV<UnitB_m, UnitB_k>));
    
    ASSERT_FALSE((IsDivisionValidV<UnitB, UnitB_m>));
    ASSERT_FALSE((IsDivisionValidV<UnitB, UnitB>));
    ASSERT_FALSE((IsDivisionValidV<UnitB, UnitB_k>));
    
    ASSERT_FALSE((IsDivisionValidV<UnitB_k, UnitB_m>));
    ASSERT_FALSE((IsDivisionValidV<UnitB_k, UnitB>));
    ASSERT_FALSE((IsDivisionValidV<UnitB_k, UnitB_k>));
}

TEST(UnitDivisionTests, DifferentBase_CT)
{
    ASSERT_FALSE((IsDivisionValidV<UnitA1_m, UnitA2_m>));
    ASSERT_FALSE((IsDivisionValidV<UnitA1_m, UnitA2>));
    ASSERT_FALSE((IsDivisionValidV<UnitA1_m, UnitA2_k>));

    ASSERT_FALSE((IsDivisionValidV<UnitA1, UnitA2_m>));
    ASSERT_FALSE((IsDivisionValidV<UnitA1, UnitA2>));
    ASSERT_FALSE((IsDivisionValidV<UnitA1, UnitA2_k>));

    ASSERT_FALSE((IsDivisionValidV<UnitA1_k, UnitA2_m>));
    ASSERT_FALSE((IsDivisionValidV<UnitA1_k, UnitA2>));
    ASSERT_FALSE((IsDivisionValidV<UnitA1_k, UnitA2_k>));
    

    ASSERT_FALSE((IsDivisionValidV<UnitA2_m, UnitA1_m>));
    ASSERT_FALSE((IsDivisionValidV<UnitA2_m, UnitA1>));
    ASSERT_FALSE((IsDivisionValidV<UnitA2_m, UnitA1_k>));

    ASSERT_FALSE((IsDivisionValidV<UnitA2, UnitA1_m>));
    ASSERT_FALSE((IsDivisionValidV<UnitA2, UnitA1>));
    ASSERT_FALSE((IsDivisionValidV<UnitA2, UnitA1_k>));

    ASSERT_FALSE((IsDivisionValidV<UnitA2_k, UnitA1_m>));
    ASSERT_FALSE((IsDivisionValidV<UnitA2_k, UnitA1>));
    ASSERT_FALSE((IsDivisionValidV<UnitA2_k, UnitA1_k>));
}

TEST(UnitDivisionTests, Arithmetic_CT)
{
    ASSERT_TRUE((ValidateDivisionResultV<UnitB, UnitB::rep, UnitB>));
    ASSERT_FALSE((IsDivisionValidV<UnitB::rep, UnitB>));
}

TEST(UnitDivisionTests, Arithmetic_RT)
{
    const UnitB b(6);

    ASSERT_EQ(b / 3, UnitB(2));
}
