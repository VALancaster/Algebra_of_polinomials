#include "polinom.h"
#include "polinom.cpp"
#include <gtest.h>


TEST(Polinom, can_create_polinom) {
	ASSERT_NO_THROW(Polinom polinom);
}

TEST(Polinom, can_create_polinom_from_correct_string) {
	ASSERT_NO_THROW(Polinom polinom("12x^2y+12yz-12"));
}

TEST(Polinom, can_create_empty_polinom_from_string) {
	Polinom polinom("");
	ASSERT_EQ(polinom.toString(), "0");
}


TEST(Polinom, can_assign_polinom) {
	Polinom polinom1("-5x^2+2xy-1");
	Polinom polinom2;
	polinom2 = polinom1;
	ASSERT_EQ(polinom2.toString(), "-5x^2+2xy-1");
}

TEST(Polinom, assign_identical_polinom) {
	Polinom polinom("3x^2+222xy-1");
	polinom = polinom;
	ASSERT_EQ(polinom.toString(), "3x^2+222xy-1");
}


TEST(Polinom, can_add_polynomials) {
	Polinom polinom1("3x^2y+2xy-1");
	Polinom polinom2("x^2y-2xy+4");
	Polinom result = polinom1 + polinom2;
	ASSERT_EQ(result.toString(), "4x^2y+3");
}

TEST(Polinom, can_add_empty_polynomial) {
	Polinom polinom1("53x^2y+2x-1");
	Polinom polinom2;
	Polinom result = polinom1 + polinom2;
	ASSERT_EQ(result.toString(), "53x^2y+2x-1");
}


TEST(Polinom, can_add_assign_polynomials) {
	Polinom polinom1("x^2y+2xy-1");
	Polinom polinom2("x^2y-2xy+4");
	polinom1 += polinom2;
	ASSERT_EQ(polinom1.toString(), "2x^2y+3");
}


TEST(Polinom, can_subtract_polynomials) {
	Polinom polinom1("6x^2y+3xy-1");
	Polinom polinom2("x^2y-2xy+4");
	Polinom result = polinom1 - polinom2;
	ASSERT_EQ(result.toString(), "5x^2y+5xy-5");
}

TEST(Polinom, can_subtract_empty_polynomial) {
	Polinom polinom1("x^2y+2xy-1");
	Polinom polinom2;
	Polinom result = polinom1 - polinom2;
	ASSERT_EQ(result.toString(), "x^2y+2xy-1");
}


TEST(Polinom, can_subtract_assign_polynomials) {
	Polinom polinom1("3x^2y+2xy-3");
	Polinom polinom2("x^2y-2xy+4");
	polinom1 -= polinom2;
	ASSERT_EQ(polinom1.toString(), "2x^2y+4xy-7");
}


TEST(Polinom, can_multiply_by_constant) {
	Polinom polinom("5x^2y+2xy-1");
	Polinom result = polinom * 2;
	ASSERT_EQ(result.toString(), "10x^2y+4xy-2");
}

TEST(Polinom, can_multiply_assign_by_constant) {
	Polinom polinom("2x^2y+2xy-3");
	polinom *= 2;
	ASSERT_EQ(polinom.toString(), "4x^2y+4xy-6");
}

TEST(Polinom, can_multiply_by_zero_constant) {
	Polinom polinom("124x^2y+2xy+55");
	Polinom result = polinom * 0;
	ASSERT_EQ(result.toString(), "0");
}


TEST(Polinom, can_multiply_polynomials) {
	Polinom polinom1("3x^2y+2xy-1");
	Polinom polinom2("x^2y-2xy+4");
	Polinom result = polinom1 * polinom2;
	ASSERT_EQ(result.toString(), "3x^4y^2-4x^3y^2+11x^2y-4x^2y^2+10xy-4");
}

TEST(Polinom, can_multiply_polynomials_with_zero) {
	Polinom polinom1("x^2y-32xy-1");
	Polinom polinom2;
	Polinom result = polinom1 * polinom2;
	ASSERT_EQ(result.toString(), "0");
}


TEST(Polinom, can_compare_polynomials_equal) {
	Polinom polinom1("4x^2y+3xy-1");
	Polinom polinom2("4x^2y+3xy-1");
	ASSERT_TRUE(polinom1 == polinom2);
}

TEST(Polinom, can_compare_polynomials_not_equal) {
	Polinom polinom1("3x^2y+2xy-1");
	Polinom polinom2("x^2y-2xy+4");
	ASSERT_TRUE(polinom1 != polinom2);
}


TEST(Polinom, can_evaluate_polynomial_at_point) {
	Polinom polinom("3x^2y+2xy-1");
	double result = polinom.evaluate(1, 2, 3);
	ASSERT_DOUBLE_EQ(result, 9);
}


TEST(Polinom, to_string_empty_polynom) {
	Polinom polinom;
	ASSERT_EQ(polinom.toString(), "0");
}

TEST(Polinom, to_string_single_term) {
	Polinom polinom("5xy");
	ASSERT_EQ(polinom.toString(), "5xy");
}

TEST(Polinom, to_string_polynomial_with_missing_terms) {
	Polinom polinom("x^3y-4xy+2");
	ASSERT_EQ(polinom.toString(), "x^3y-4xy+2");
}


TEST(Polinom, can_compute_derivative_of_single_term_wrt_x) {
	Polinom polinom("5x^3");
	Polinom result = polinom.derivative('x');
	ASSERT_EQ(result.toString(), "15x^2");
}

TEST(Polinom, can_compute_derivative_of_polynomial_wrt_x) {
	Polinom polinom("2x^3+1yx");
	Polinom result = polinom.derivative('x');
	ASSERT_EQ(result.toString(), "6x^2+y");
}

TEST(Polinom, can_compute_derivative_of_polynomial_wrt_y) {
	Polinom polinom("3x^2y^2+2xy");
	Polinom result = polinom.derivative('y');
	ASSERT_EQ(result.toString(), "6x^2y+2x");
}

TEST(Polinom, can_compute_derivative_of_polynomial_wrt_z) {
	Polinom polinom("z^2yx+1z");
	Polinom result = polinom.derivative('z');
	ASSERT_EQ(result.toString(), "2xyz+1");
}

TEST(Polinom, derivative_of_constant_is_zero) {
	Polinom polinom("5");
	Polinom result = polinom.derivative('x');
	ASSERT_EQ(result.toString(), "0");
}

TEST(Polinom, derivative_of_zero_is_zero) {
	Polinom polinom("0");
	Polinom result = polinom.derivative('x');
	ASSERT_EQ(result.toString(), "0");
}
