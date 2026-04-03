# NCTest
This is my small testing framework/library for my C projects. Currently doesn't support C++ yet.

## Usage
You should write your tests in your test files in a format as given below:
```
TEST(testLabel, "a test description") {
    // your test logic with asserts and so on
    ...
}
```

Examples:
```
TEST(shouldPassWithOneAssert, "This test should pass") {
    ASSERT_TRUE(1 == 1);
}

TEST(shouldFailWithTwoAssertsFirstFail, "This test has 2 asserts and it should fail with the first assert failing")
{
    ASSERT_TRUE(4 > 6);
    ASSERT_TRUE(2 == 2);
}

TEST(shouldPassWithTwoAsserts, "This test has 2 asserts and all of them should pass")
{
    ASSERT_TRUE(2 + 2 == 4);
    ASSERT_TRUE(4 < 6);
}
```

### IMPORTANT!!!
The below listed actions will lead to **compile time error or undefined behavior**:
- Using `TEST` macro inside a function
- Using `ASSERT_*` macros outside of a `TEST` macro function body

## TODO
- Add support for C++
