#include <gtest/gtest.h>

#include <jb/unit.hpp>

#include "TestUnits.hpp"
#include "CompilitimeOperatorTests.hpp"

TEST(UnitSubtractionTests, SameBase_CT)
{
    ASSERT_TRUE((ValidateSubtractionResultV<UnitB_m, UnitB_m, UnitB_m>));
    ASSERT_TRUE((ValidateSubtractionResultV<UnitB_m, UnitB, UnitB_m>));
    ASSERT_TRUE((ValidateSubtractionResultV<UnitB_m, UnitB_k, UnitB_m>));
    
    ASSERT_TRUE((ValidateSubtractionResultV<UnitB, UnitB_m, UnitB_m>));
    ASSERT_TRUE((ValidateSubtractionResultV<UnitB, UnitB, UnitB>));
    ASSERT_TRUE((ValidateSubtractionResultV<UnitB, UnitB_k, UnitB>));
    
    ASSERT_TRUE((ValidateSubtractionResultV<UnitB_k, UnitB_m, UnitB_m>));
    ASSERT_TRUE((ValidateSubtractionResultV<UnitB_k, UnitB, UnitB>));
    ASSERT_TRUE((ValidateSubtractionResultV<UnitB_k, UnitB_k, UnitB_k>));
}

TEST(UnitSubtractionTests, SameBase_RT)
{
    const UnitB_k b1_k(5), b2_k(15);
    const UnitB b1(b1_k), b2(b2_k);
    const UnitB_m b1_m(b1_k), b2_m(b2_k);

    const UnitB_m result(-10000000);

    ASSERT_EQ(b1_m - b2_m, result);
    ASSERT_EQ(b1_m - b2, result);
    ASSERT_EQ(b1_m - b2_k, result);

    ASSERT_EQ(b1 - b2_m, result);
    ASSERT_EQ(b1 - b2, result);
    ASSERT_EQ(b1 - b2_k, result);

    ASSERT_EQ(b1_k - b2_m, result);
    ASSERT_EQ(b1_k - b2, result);
    ASSERT_EQ(b1_k - b2_k, result);
}

TEST(UnitSubtractionTests, DifferentBase_CT)
{
    ASSERT_FALSE((IsSubtractionValidV<UnitA1_m, UnitA2_m>));
    ASSERT_FALSE((IsSubtractionValidV<UnitA1_m, UnitA2>));
    ASSERT_FALSE((IsSubtractionValidV<UnitA1_m, UnitA2_k>));

    ASSERT_FALSE((IsSubtractionValidV<UnitA1, UnitA2_m>));
    ASSERT_FALSE((IsSubtractionValidV<UnitA1, UnitA2>));
    ASSERT_FALSE((IsSubtractionValidV<UnitA1, UnitA2_k>));

    ASSERT_FALSE((IsSubtractionValidV<UnitA1_k, UnitA2_m>));
    ASSERT_FALSE((IsSubtractionValidV<UnitA1_k, UnitA2>));
    ASSERT_FALSE((IsSubtractionValidV<UnitA1_k, UnitA2_k>));
    

    ASSERT_FALSE((IsSubtractionValidV<UnitA2_m, UnitA1_m>));
    ASSERT_FALSE((IsSubtractionValidV<UnitA2_m, UnitA1>));
    ASSERT_FALSE((IsSubtractionValidV<UnitA2_m, UnitA1_k>));

    ASSERT_FALSE((IsSubtractionValidV<UnitA2, UnitA1_m>));
    ASSERT_FALSE((IsSubtractionValidV<UnitA2, UnitA1>));
    ASSERT_FALSE((IsSubtractionValidV<UnitA2, UnitA1_k>));

    ASSERT_FALSE((IsSubtractionValidV<UnitA2_k, UnitA1_m>));
    ASSERT_FALSE((IsSubtractionValidV<UnitA2_k, UnitA1>));
    ASSERT_FALSE((IsSubtractionValidV<UnitA2_k, UnitA1_k>));
}

TEST(UnitSubtractionTests, Arithmetic_CT)
{
    ASSERT_FALSE((IsSubtractionValidV<UnitB, UnitB::rep>));
}
