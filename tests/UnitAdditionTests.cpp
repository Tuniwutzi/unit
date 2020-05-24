#include <gtest/gtest.h>

#include <jb/unit.hpp>

#include "TestUnits.hpp"
#include "CompilitimeOperatorTests.hpp"

TEST(UnitAdditionTests, SameBase_CT)
{
    ASSERT_TRUE((ValidateAdditionResultV<UnitB_m, UnitB_m, UnitB_m>));
    ASSERT_TRUE((ValidateAdditionResultV<UnitB_m, UnitB, UnitB_m>));
    ASSERT_TRUE((ValidateAdditionResultV<UnitB_m, UnitB_k, UnitB_m>));
    
    ASSERT_TRUE((ValidateAdditionResultV<UnitB, UnitB_m, UnitB_m>));
    ASSERT_TRUE((ValidateAdditionResultV<UnitB, UnitB, UnitB>));
    ASSERT_TRUE((ValidateAdditionResultV<UnitB, UnitB_k, UnitB>));
    
    ASSERT_TRUE((ValidateAdditionResultV<UnitB_k, UnitB_m, UnitB_m>));
    ASSERT_TRUE((ValidateAdditionResultV<UnitB_k, UnitB, UnitB>));
    ASSERT_TRUE((ValidateAdditionResultV<UnitB_k, UnitB_k, UnitB_k>));
}

TEST(UnitAdditionTests, SameBase_RT)
{
    const UnitB_k b1_k(5), b2_k(15);
    const UnitB b1(b1_k), b2(b2_k);
    const UnitB_m b1_m(b1_k), b2_m(b2_k);

    const UnitB_m result(20000000);


    ASSERT_EQ(b1_m + b2_m, result);
    ASSERT_EQ(b1_m + b2, result);
    ASSERT_EQ(b1_m + b2_k, result);

    ASSERT_EQ(b1 + b2_m, result);
    ASSERT_EQ(b1 + b2, result);
    ASSERT_EQ(b1 + b2_k, result);

    ASSERT_EQ(b1_k + b2_m, result);
    ASSERT_EQ(b1_k + b2, result);
    ASSERT_EQ(b1_k + b2_k, result);
}

TEST(UnitAdditionTests, DifferentBase_CT)
{
    ASSERT_FALSE((IsAdditionValidV<UnitA1_m, UnitA2_m>));
    ASSERT_FALSE((IsAdditionValidV<UnitA1_m, UnitA2>));
    ASSERT_FALSE((IsAdditionValidV<UnitA1_m, UnitA2_k>));

    ASSERT_FALSE((IsAdditionValidV<UnitA1, UnitA2_m>));
    ASSERT_FALSE((IsAdditionValidV<UnitA1, UnitA2>));
    ASSERT_FALSE((IsAdditionValidV<UnitA1, UnitA2_k>));

    ASSERT_FALSE((IsAdditionValidV<UnitA1_k, UnitA2_m>));
    ASSERT_FALSE((IsAdditionValidV<UnitA1_k, UnitA2>));
    ASSERT_FALSE((IsAdditionValidV<UnitA1_k, UnitA2_k>));
    

    ASSERT_FALSE((IsAdditionValidV<UnitA2_m, UnitA1_m>));
    ASSERT_FALSE((IsAdditionValidV<UnitA2_m, UnitA1>));
    ASSERT_FALSE((IsAdditionValidV<UnitA2_m, UnitA1_k>));

    ASSERT_FALSE((IsAdditionValidV<UnitA2, UnitA1_m>));
    ASSERT_FALSE((IsAdditionValidV<UnitA2, UnitA1>));
    ASSERT_FALSE((IsAdditionValidV<UnitA2, UnitA1_k>));

    ASSERT_FALSE((IsAdditionValidV<UnitA2_k, UnitA1_m>));
    ASSERT_FALSE((IsAdditionValidV<UnitA2_k, UnitA1>));
    ASSERT_FALSE((IsAdditionValidV<UnitA2_k, UnitA1_k>));
}

TEST(UnitAdditionTests, Arithmetic_CT)
{
    ASSERT_FALSE((IsAdditionValidV<UnitB, UnitB::rep>));
}
