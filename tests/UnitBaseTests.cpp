#include <gtest/gtest.h>

#include "TestUnits.hpp"
#include "CompilitimeOperatorTests.hpp"

TEST(UnitBase, Count)
{
    UnitB_m bm(5);
    UnitB b(5000);
    UnitB_k bk(5000000);

    ASSERT_EQ(bm.count(), 5);
    ASSERT_EQ(b.count(), 5000);
    ASSERT_EQ(bk.count(), 5000000);
}

TEST(UnitBase, ImplicitConversions_SameBase_CT)
{
    ASSERT_TRUE((IsAssignmentValidV<UnitB_m, UnitB_m>));
    ASSERT_TRUE((IsAssignmentValidV<UnitB_m, UnitB>));
    ASSERT_TRUE((IsAssignmentValidV<UnitB_m, UnitB_k>));

    ASSERT_FALSE((IsAssignmentValidV<UnitB, UnitB_m>));
    ASSERT_TRUE((IsAssignmentValidV<UnitB, UnitB>));
    ASSERT_TRUE((IsAssignmentValidV<UnitB, UnitB_k>));

    ASSERT_FALSE((IsAssignmentValidV<UnitB_k, UnitB_m>));
    ASSERT_FALSE((IsAssignmentValidV<UnitB_k, UnitB>));
    ASSERT_TRUE((IsAssignmentValidV<UnitB_k, UnitB_k>));
}

TEST(UnitBase, ImplicitConversions_SameBase_RT)
{
    UnitB_m bm(9);
    UnitB b(9);
    UnitB_k bk(9);

    bm = UnitB_m(15);
    ASSERT_EQ(bm.count(), 15);
    bm = UnitB(15);
    ASSERT_EQ(bm.count(), 15000);
    bm = UnitB_k(15);
    ASSERT_EQ(bm.count(), 15000000);

    b = UnitB(15);
    ASSERT_EQ(b.count(), 15);
    b = UnitB_k(15);
    ASSERT_EQ(b.count(), 15000);
    
    bk = UnitB_k(15);
    ASSERT_EQ(bk.count(), 15);
}

TEST(UnitBase, ImplicitConversions_DifferentBase_CT)
{
    ASSERT_FALSE((IsAssignmentValidV<UnitA1_m, UnitA2_m>));
    ASSERT_FALSE((IsAssignmentValidV<UnitA1_m, UnitA2>));
    ASSERT_FALSE((IsAssignmentValidV<UnitA1_m, UnitA2_k>));

    ASSERT_FALSE((IsAssignmentValidV<UnitA1, UnitA2_m>));
    ASSERT_FALSE((IsAssignmentValidV<UnitA1, UnitA2>));
    ASSERT_FALSE((IsAssignmentValidV<UnitA1, UnitA2_k>));

    ASSERT_FALSE((IsAssignmentValidV<UnitA1_k, UnitA2_m>));
    ASSERT_FALSE((IsAssignmentValidV<UnitA1_k, UnitA2>));
    ASSERT_FALSE((IsAssignmentValidV<UnitA1_k, UnitA2_k>));
    
    ASSERT_FALSE((IsAssignmentValidV<UnitA2_m, UnitA1_m>));
    ASSERT_FALSE((IsAssignmentValidV<UnitA2_m, UnitA1>));
    ASSERT_FALSE((IsAssignmentValidV<UnitA2_m, UnitA1_k>));

    ASSERT_FALSE((IsAssignmentValidV<UnitA2, UnitA1_m>));
    ASSERT_FALSE((IsAssignmentValidV<UnitA2, UnitA1>));
    ASSERT_FALSE((IsAssignmentValidV<UnitA2, UnitA1_k>));

    ASSERT_FALSE((IsAssignmentValidV<UnitA2_k, UnitA1_m>));
    ASSERT_FALSE((IsAssignmentValidV<UnitA2_k, UnitA1>));
    ASSERT_FALSE((IsAssignmentValidV<UnitA2_k, UnitA1_k>));
}

TEST(UnitBase, ImplicitConversions_DifferentBase_RT)
{
    // no implicit conversions allowed by the UnitConverter
}

TEST(UnitBase, ExplicitConversions_SameBase_CT)
{
    ASSERT_TRUE((IsCastValidV<UnitB_m, UnitB_m>));
    ASSERT_TRUE((IsCastValidV<UnitB_m, UnitB>));
    ASSERT_TRUE((IsCastValidV<UnitB_m, UnitB_k>));

    ASSERT_TRUE((IsCastValidV<UnitB, UnitB_m>));
    ASSERT_TRUE((IsCastValidV<UnitB, UnitB>));
    ASSERT_TRUE((IsCastValidV<UnitB, UnitB_k>));

    ASSERT_TRUE((IsCastValidV<UnitB_k, UnitB_m>));
    ASSERT_TRUE((IsCastValidV<UnitB_k, UnitB>));
    ASSERT_TRUE((IsCastValidV<UnitB_k, UnitB_k>));
}

TEST(UnitBase, ExplicitConversions_SameBase_RT)
{
    UnitB b(9);
    UnitB_k bk(9);

    b = static_cast<UnitB>(UnitB_m(15000));
    ASSERT_EQ(b.count(), 15);
    
    bk = static_cast<UnitB_k>(UnitB_m(15000000));
    ASSERT_EQ(b.count(), 15);
    bk = static_cast<UnitB_k>(UnitB(15000));
    ASSERT_EQ(b.count(), 15);
}

TEST(UnitBase, ExplicitConversions_DifferentBase_CT)
{
    ASSERT_TRUE((IsCastValidV<UnitA1_m, UnitA2_m>));
    ASSERT_TRUE((IsCastValidV<UnitA1_m, UnitA2>));
    ASSERT_TRUE((IsCastValidV<UnitA1_m, UnitA2_k>));

    ASSERT_TRUE((IsCastValidV<UnitA1, UnitA2_m>));
    ASSERT_TRUE((IsCastValidV<UnitA1, UnitA2>));
    ASSERT_TRUE((IsCastValidV<UnitA1, UnitA2_k>));

    ASSERT_TRUE((IsCastValidV<UnitA1_k, UnitA2_m>));
    ASSERT_TRUE((IsCastValidV<UnitA1_k, UnitA2>));
    ASSERT_TRUE((IsCastValidV<UnitA1_k, UnitA2_k>));
    
    ASSERT_TRUE((IsCastValidV<UnitA2_m, UnitA1_m>));
    ASSERT_TRUE((IsCastValidV<UnitA2_m, UnitA1>));
    ASSERT_TRUE((IsCastValidV<UnitA2_m, UnitA1_k>));

    ASSERT_TRUE((IsCastValidV<UnitA2, UnitA1_m>));
    ASSERT_TRUE((IsCastValidV<UnitA2, UnitA1>));
    ASSERT_TRUE((IsCastValidV<UnitA2, UnitA1_k>));

    ASSERT_TRUE((IsCastValidV<UnitA2_k, UnitA1_m>));
    ASSERT_TRUE((IsCastValidV<UnitA2_k, UnitA1>));
    ASSERT_TRUE((IsCastValidV<UnitA2_k, UnitA1_k>));
}

TEST(UnitBase, ExplicitConversions_DifferentBase_RT)
{
    UnitA1 a1(9);
    UnitA2 a2(9);

    a1 = static_cast<UnitA1>(UnitA2(15));
    ASSERT_EQ(a1.count(), 15 - DifferenceA1A2);
    a2 = static_cast<UnitA2>(UnitA1(15));
    ASSERT_EQ(a2.count(), 15 + DifferenceA1A2);
}

