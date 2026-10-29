#include "Fixed.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

static void testConversions()
{
    const Fixed zero;
    const Fixed integer(-10);
    const Fixed fraction(-2.75f);

    const float value = fraction.toFloat();
    const int truncated = fraction.toInt();

    assert(zero.getRawBits() == 0);
    assert(integer.getRawBits() == -2560);
    assert(integer.toInt() == -10);
    assert(value == -2.75f);
    assert(truncated == -2);
}

static void testCopies()
{
    Fixed original(2.5f);
    Fixed assigned;

    const Fixed copy(original);
    Fixed &result = (assigned = original);
    original.setRawBits(0);
    const Fixed &alias = assigned;
    assigned = alias;

    assert(&result == &assigned);
    assert(copy.toFloat() == 2.5f);
    assert(assigned.toFloat() == 2.5f);
    assert(original.getRawBits() == 0);
}

static void testComparisons()
{
    const Fixed low(-2.5f);
    const Fixed equal(-2.5f);
    const Fixed high(1.25f);

    assert(low < high);
    assert(!(high < low));
    assert(!(low < equal));
    assert(high > low);
    assert(!(low > high));
    assert(!(low > equal));
    assert(low <= high);
    assert(low <= equal);
    assert(!(high <= low));
    assert(high >= low);
    assert(low >= equal);
    assert(!(low >= high));
    assert(low == equal);
    assert(!(low == high));
    assert(low != high);
    assert(!(low != equal));
}

static void testArithmetic()
{
    const Fixed first(2.5f);
    const Fixed second(0.5f);

    const Fixed sum = first + second;
    const Fixed difference = first - second;
    const Fixed product = first * second;
    const Fixed quotient = first / second;

    assert(sum.toFloat() == 3.0f);
    assert(difference.toFloat() == 2.0f);
    assert(product.toFloat() == 1.25f);
    assert(quotient.toFloat() == 5.0f);
    assert(first.toFloat() == 2.5f);
    assert(second.toFloat() == 0.5f);
}

static void testNegativeArithmetic()
{
    const Fixed negative(-2.5f);
    const Fixed positive(0.5f);

    const Fixed sum = negative + positive;
    const Fixed difference = negative - positive;
    const Fixed product = negative * positive;
    const Fixed quotient = positive / negative;

    assert(sum.toFloat() == -2.0f);
    assert(difference.toFloat() == -3.0f);
    assert(product.toFloat() == -1.25f);
    assert(quotient.getRawBits() == -51);
}

static void testRawPrecision()
{
    Fixed value;
    value.setRawBits(16777217);
    Fixed step;
    step.setRawBits(1);
    const Fixed one(1);

    const Fixed sum = value + step;
    const Fixed difference = value - step;
    const Fixed product = value * one;
    const Fixed quotient = value / one;

    assert(sum.getRawBits() == 16777218);
    assert(difference.getRawBits() == 16777216);
    assert(product.getRawBits() == 16777217);
    assert(quotient.getRawBits() == 16777217);
    assert(sum > value);
    assert(value > difference);
}

static void testArithmeticScaling()
{
    const Fixed thousand(1000);
    const Fixed million(1000000);
    const Fixed two(2);

    const Fixed product = thousand * thousand;
    const Fixed quotient = million / two;

    assert(product.toInt() == 1000000);
    assert(quotient.toInt() == 500000);
}

static void testHalfStepRounding()
{
    const Fixed step(1.0f / 256.0f);
    const Fixed negativeStep(-1.0f / 256.0f);
    const Fixed half(0.5f);
    const Fixed two(2);

    const Fixed positiveProduct = step * half;
    const Fixed negativeProduct = negativeStep * half;
    const Fixed positiveQuotient = step / two;
    const Fixed negativeQuotient = negativeStep / two;

    assert(positiveProduct.getRawBits() == 1);
    assert(negativeProduct.getRawBits() == -1);
    assert(positiveQuotient.getRawBits() == 1);
    assert(negativeQuotient.getRawBits() == -1);
}

static void testIncrement()
{
    Fixed value;

    Fixed &reference = ++value;
    const Fixed previous = value++;

    assert(&reference == &value);
    assert(previous.getRawBits() == 1);
    assert(value.getRawBits() == 2);
}

static void testDecrement()
{
    Fixed value;

    Fixed &reference = --value;
    const Fixed previous = value--;

    assert(&reference == &value);
    assert(previous.getRawBits() == -1);
    assert(value.getRawBits() == -2);
}

static void testMutableMinMax()
{
    Fixed low(-2);
    Fixed high(3);

    Fixed &minimum = Fixed::min(high, low);
    Fixed &maximum = Fixed::max(low, high);
    minimum.setRawBits(-1);
    maximum.setRawBits(1);

    assert(&minimum == &low);
    assert(&maximum == &high);
    assert(&Fixed::min(low, high) == &low);
    assert(&Fixed::max(high, low) == &high);
    assert(low.getRawBits() == -1);
    assert(high.getRawBits() == 1);
}

static void testConstMinMax()
{
    const Fixed low(-2);
    const Fixed high(3);

    const Fixed &minimum = Fixed::min(high, low);
    const Fixed &maximum = Fixed::max(low, high);

    assert(&minimum == &low);
    assert(&maximum == &high);
    assert(&Fixed::min(low, high) == &low);
    assert(&Fixed::max(high, low) == &high);
    assert(Fixed::min(low, low) == low);
    assert(Fixed::max(high, high) == high);
}

static void testStreamInsertion()
{
    const Fixed value(-2.5f);
    std::ostringstream output;

    std::ostream &result = (output << value << " " << Fixed(3));

    assert(&result == &output);
    assert(output.str() == "-2.5 3");
}

static void testDivisionByZero()
{
    const Fixed value(1);
    const Fixed zero;
    bool rejected = false;

    try
    {
        value / zero;
    }
    catch (const std::domain_error &)
    {
        rejected = true;
    }

    assert(rejected);
}

int main(void)
{
    testConversions();
    testCopies();
    testComparisons();
    testArithmetic();
    testNegativeArithmetic();
    testRawPrecision();
    testArithmeticScaling();
    testHalfStepRounding();
    testIncrement();
    testDecrement();
    testMutableMinMax();
    testConstMinMax();
    testStreamInsertion();
    testDivisionByZero();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
