#include "postfix.h"
#include <gtest.h>


TEST(TPostfix, can_create_postfix_with_valid_infix)
{
	ASSERT_NO_THROW(TPostfix p("(a+b)*c+b/d"));
}

TEST(TPostfix, get_infix_return_valid_value)
{
	TPostfix p("a+b*c-d/(a+e)");
	EXPECT_EQ("a+b*c-d/(a+e)", p.GetInfix());
}

TEST(TPostfix, can_get_postfix)
{
	TPostfix p("a+b*(c-d/e)");
	EXPECT_EQ("a b c d e / - * + ", p.GetPostfix());
}

TEST(TPostfix, can_calculate_correct_value)
{
	TPostfix p("a+b*c");
	map<string, double> values = { {"a", 7}, {"b", 2}, {"c", 1} };
	EXPECT_EQ(9, p.Calculate(values));
}

TEST(TPostfix, can_get_postfix_with_brackets)
{
	TPostfix p("(a+b)*c");
	EXPECT_EQ("a b + c * ", p.GetPostfix());
}

TEST(TPostfix, can_get_infix_with_brackets)
{
	TPostfix p("(a+b)/c");
	EXPECT_EQ("(a+b)/c", p.GetInfix());
}

TEST(TPostfix, can_calculate_correct_value_with_brackets)
{
	TPostfix p("(a+b)*c");
	map<string, double> values = { {"a", 7}, {"b", 2}, {"c", 2} };
	EXPECT_EQ(18, p.Calculate(values));
}

TEST(TPostfix, can_get_operands)
{
	TPostfix p("(a+b)*c/d");
	vector<string> op = { "a","b","c","d" };
	EXPECT_EQ(op, p.GetOperands());
}

TEST(TPostfix, can_handle_empty_expression)
{
	ASSERT_ANY_THROW(TPostfix p(""));
}
