#include "postfix.h"
#include <gtest.h>


TEST(TPostfix, can_create_postfix_with_valid_infix) {
    ASSERT_NO_THROW(TPostfix p("(x^2 + y^3) * z + y/z"));
}

TEST(TPostfix, throws_exception_for_empty_infix) {
    ASSERT_THROW(TPostfix p(""), std::invalid_argument);
}

TEST(TPostfix, get_infix_return_valid_value) {
    TPostfix p("x + y*z - z/(x + y)");
    EXPECT_EQ("x + y*z - z/(x + y)", p.GetInfix());
}

TEST(TPostfix, can_get_postfix) {
    TPostfix p("x + y*(z - x/y)");
    EXPECT_EQ("x y z x y / - * + ", p.GetPostfix());
}

TEST(TPostfix, can_parse_and_get_operands) {
    TPostfix p("x + y*z");
    std::vector<std::string> expected_operands = { "x", "y", "z" };
    EXPECT_EQ(expected_operands, p.GetOperands());
}

TEST(TPostfix, calculate_simple_expression) {
    TPostfix p("2*x + 3*y*z");
    double expected_result = 2 * 3 + 3 * 4 * 1;
    EXPECT_DOUBLE_EQ(expected_result, p.Calculate(3, 4, 1));
}

TEST(TPostfix, calculate_with_variables) {
    TPostfix p("x*y + z");
    double expected_result = 2.0 * 3.0 + 3.0;
    EXPECT_DOUBLE_EQ(expected_result, p.Calculate(2.0, 3.0, 3.0));
}

TEST(TPostfix, throws_exception_for_division_by_zero) {
    TPostfix p("x/y");
    ASSERT_THROW(p.Calculate(5.0, 0, 0), std::runtime_error);
}