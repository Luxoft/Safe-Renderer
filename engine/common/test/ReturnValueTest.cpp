/******************************************************************************
**
**     File:        ReturnValueTest.cpp
**     Description:
**
**     ------------------------------------------------------------------------
**
**     Copyright Luxoft GmbH 2017
**
**     The copyright of the computer program(os) herein is the property of
**     Luxoft GmbH. The programs(s) may be used and/or copied only with the
**     written permission of Luxoft GmbH or in accordance with the terms and
**     conditions stipulated in the agreement/contract under which the
**     program(s) have been supplied.
**
******************************************************************************/

#include <gtest/gtest.h>

#include <ReturnValue.h>


class ReturnValueTest : public ::testing::Test
{
};

TEST_F(ReturnValueTest, boolean_true)
{
    lsr::ReturnValue<bool, true> ret;
    EXPECT_TRUE(ret);
    ret = false;
    EXPECT_FALSE(ret);
    ret = true;
    EXPECT_TRUE(ret);

    lsr::ReturnValue<bool, true> ret2 = true;
    EXPECT_TRUE(ret2);

    lsr::ReturnValue<bool, true> ret3 = false;
    EXPECT_FALSE(ret3);
}

TEST_F(ReturnValueTest, boolean_false)
{
    lsr::ReturnValue<bool, false> ret;
    EXPECT_FALSE(ret);
    ret = true;
    EXPECT_TRUE(ret);
    ret = false;
    EXPECT_FALSE(ret);

    lsr::ReturnValue<bool, false> ret2 = true;
    EXPECT_TRUE(ret2);

    lsr::ReturnValue<bool, false> ret3 = false;
    EXPECT_FALSE(ret3);
}

TEST_F(ReturnValueTest, int_42)
{
    lsr::ReturnValue<int, 42> ret;
    EXPECT_EQ(42, ret);
    ret = 5;
    EXPECT_EQ(5, ret);
    ret = 0;
    EXPECT_EQ(0, ret);

    lsr::ReturnValue<int, 42> ret2 = 55;
    EXPECT_EQ(55, ret2);
}

enum Foo
{
    Foo_1,
    Foo_2,
};

TEST_F(ReturnValueTest, enum_foo2)
{
    lsr::ReturnValue<Foo, Foo_2> ret;
    EXPECT_EQ(Foo_2, ret);
    ret = Foo_1;
    EXPECT_EQ(Foo_1, ret);
    ret = Foo_2;
    EXPECT_EQ(Foo_2, ret);

    lsr::ReturnValue<Foo, Foo_2> ret2 = Foo_1;
    EXPECT_EQ(Foo_1, ret2);
}
