#include "postfix.h"
#include <gtest.h>


TEST(TPostfix, can_create_postfix_with_valid_infix) {
    ASSERT_NO_THROW(TPostfix p("(a+b)*c+b/d"));
}

TEST(TPostfix, throws_exception_for_empty_infix) {
    ASSERT_THROW(TPostfix p(""), std::invalid_argument);
}

TEST(TPostfix, get_infix_return_valid_value) {
    TPostfix p("a+b*c-d/(a+e)");
    EXPECT_EQ("a+b*c-d/(a+e)", p.GetInfix());
}

TEST(TPostfix, can_get_postfix) {
    TPostfix p("a+b*(c-d/e)");
    EXPECT_EQ("a b c d e / - * + ", p.GetPostfix());
}

TEST(TPostfix, can_parse_and_get_operands) {
    TPostfix p("a+b*c");
    std::vector<std::string> expected_operands = { "a", "b", "c" };
    EXPECT_EQ(expected_operands, p.GetOperands());
}

TEST(TPostfix, calculate_simple_expression) {
    TPostfix p("2+3*4");
    double expected_result = 14.0;
    EXPECT_DOUBLE_EQ(expected_result, p.Calculate(0, 0, 0));
}

TEST(TPostfix, calculate_with_variables) {
    TPostfix p("x*y+z");
    double expected_result = 9.0;
    EXPECT_DOUBLE_EQ(expected_result, p.Calculate(2.0, 3.0, 3.0));
}

TEST(TPostfix, throws_exception_for_division_by_zero) {
    TPostfix p("5/0");
    ASSERT_THROW(p.Calculate(0, 0, 0), std::runtime_error);
}
