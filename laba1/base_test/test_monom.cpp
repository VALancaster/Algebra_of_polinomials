#include "monom.h"
#include "monom.cpp"
#include <gtest.h>


TEST(Monom, can_create_monom_with_valid_coeff_and_degrees) {
	ASSERT_NO_THROW(Monom monom(5.0, 2, 1, 3));
}

TEST(Monom, throws_when_create_monom_with_negative_degree) {
	ASSERT_THROW(Monom monom(3.5, 2, -1, 0), std::invalid_argument);
}

TEST(Monom, throws_when_create_monom_with_degree_exceeding_max) {
	ASSERT_THROW(Monom monom(1.0, MAX_DEGREE + 1, 0, 0), std::invalid_argument);
}


TEST(Monom, can_create_monom_from_string_with_valid_format) {
	ASSERT_NO_THROW(Monom monom("3.5x^2y^3z"));
}

TEST(Monom, throws_when_create_monom_from_string_with_invalid_variable) {
	ASSERT_THROW(Monom monom("4x^3y^2t"), std::invalid_argument);
}

TEST(Monom, throws_when_create_monom_from_string_with_invalid_degree) {
	ASSERT_THROW(Monom monom("3x^-1y^2z"), std::invalid_argument);
}

TEST(Monom, correctly_parses_negative_coeff_in_string) {
	Monom monom("-4.2x^1y^3z^2");
	EXPECT_EQ(monom.evaluate(1, 1, 1), -4.2);
}


TEST(Monom, operator_less_than_works_correctly) {
	Monom monom1(2, 2, 3, 1);
	Monom monom2(5, 1, 2, 4);
	EXPECT_TRUE(monom2 < monom1);
}

TEST(Monom, operator_greater_than_works_correctly) {
	Monom monom1(1, 4, 1, 2);
	Monom monom2(2, 3, 2, 1);
	EXPECT_TRUE(monom1 > monom2);
}

TEST(Monom, operator_equality_works_correctly) {
	Monom monom1(3.0, 2, 2, 2);
	Monom monom2(3.0, 2, 2, 2);
	EXPECT_TRUE(monom1 == monom2);
}

TEST(Monom, operator_inequality_works_correctly) {
	Monom monom1(7.5, 3, 0, 1);
	Monom monom2(6.5, 3, 0, 1);
	EXPECT_TRUE(monom1 != monom2);
}


TEST(Monom, can_multiply_monomials_within_valid_degrees) {
	Monom monom1(1.5, 3, 2, 0);
	Monom monom2(-2.0, 1, 1, 1);
	Monom result = monom1 * monom2;
	EXPECT_EQ(result.evaluate(1, 1, 1), -3.0);
	EXPECT_EQ(result.toString(), "-3x^4y^3z");
}

TEST(Monom, throws_when_multiplication_exceeds_max_degree) {
	Monom monom1(2.0, MAX_DEGREE - 1, 0, 0);
	Monom monom2(1.0, 2, 0, 0);
	ASSERT_THROW(monom1 * monom2, std::invalid_argument);
}


TEST(Monom, evaluates_correctly_for_given_variables) {
	Monom monom(3.0, 1, 2, 1);
	EXPECT_EQ(monom.evaluate(2, 3, 2), 3.0 * std::pow(2, 1) * std::pow(3, 2) * std::pow(2, 1));
}

TEST(Monom, evaluates_to_zero_when_coefficient_is_zero) {
	Monom monom(0.0, 1, 1, 1);
	EXPECT_EQ(monom.evaluate(2, 2, 2), 0.0);
}


TEST(Monom, to_string_works_correctly) {
	Monom monom(1.2, 1, 1, 2);
	EXPECT_EQ(monom.toString(), "1.2xyz^2");
}

TEST(Monom, to_string_handles_zero_coefficient) {
	Monom monom(0.0, 4, 3, 2);
	EXPECT_EQ(monom.toString(), "");
}

TEST(Monom, to_string_skips_zero_degrees) {
	Monom monom(1.0, 1, 0, 2);
	EXPECT_EQ(monom.toString(), "xz^2");
}

TEST(Monom, degree_hash_computes_correctly) {
	Monom monom(3, 2, 1, 3);
	int expectedHash = (2 * 100 * 100) + (1 * 100) + 3;
	EXPECT_EQ(monom.getDegreeHash(), expectedHash);
}
