#include "nctest.h"

#include <stdbool.h>

// SHOULD PASS
TEST(shouldPassWithOneAssert, "This test should pass") {
    ASSERT_TRUE(1 == 1);
}

// SHOULD PASS
TEST(shouldPassWithTwoAsserts, "This test has 2 asserts and all of them should pass")
{
    ASSERT_TRUE(2 + 2 == 4);
    ASSERT_TRUE(4 < 6);
}

// SHOULD PASS
TEST(shouldPassWithMoreThanTwoAsserts, "This test has more than 2 asserts and all of them should pass")
{
    ASSERT_TRUE(2 + 2 == 4);
    ASSERT_TRUE(4 < 6);
    ASSERT_TRUE(true);
    ASSERT_TRUE(532);
}

// SHOULD FAIL
TEST(shouldFailWithOneAssert, "This test should fail") {
    ASSERT_TRUE(1 == 2);
}

// SHOULD FAIL
TEST(shouldFailWithTwoAssertsFirstFail, "This test has 2 asserts and it should fail with the first assert failing")
{
    ASSERT_TRUE(4 > 6);
    ASSERT_TRUE(2 == 2);
}

// SHOULD FAIL
TEST(shouldFailWithTwoAssertsLastFail, "This test has 2 asserts and it should fail with the last assert failing")
{
    ASSERT_TRUE(2 == 2);
    ASSERT_TRUE(4 > 6);
}

// SHOULD FAIL
TEST(shouldFailWithMoreThanTwoAsserts, "This test has more than 2 asserts and it should fail with a middle assert failing")
{
    ASSERT_TRUE(2 == 2);
    ASSERT_TRUE(3 < 1234);
    ASSERT_TRUE(4 > 6);
    ASSERT_TRUE(4 < 6);
}
