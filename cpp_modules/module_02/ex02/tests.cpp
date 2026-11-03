#include "Fixed.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

static void testBasics()
{
    const Fixed integer(-10);
    const Fixed fraction(-2.75f);
    const Fixed copy(fraction);
    Fixed assigned;

    assigned = copy;
    assert(integer.toInt() == -10);
    assert(fraction.toInt() == -2);
    assert(fraction.toFloat() == -2.75f);
    assert(assigned.getRawBits() == -704);
    assigned.setRawBits(0);
    assert(assigned.getRawBits() == 0 && copy.getRawBits() == -704);

    std::ostringstream output;
    output << fraction;
    assert(output.str() == "-2.75");
}

static void testComparisonsAndArithmetic()
{
    const Fixed a(2.5f);
    const Fixed b(0.5f);

    assert(a > b && !(b > a));
    assert(b < a && !(a < b));
    assert(a >= a && !(b >= a));
    assert(b <= a && !(a <= b));
    assert(a == Fixed(2.5f) && !(a == b));
    assert(a != b && !(a != Fixed(2.5f)));
    assert((a + b).toFloat() == 3.0f);
    assert((a - b).toFloat() == 2.0f);
    assert((a * b).toFloat() == 1.25f);
    assert((a / b).toFloat() == 5.0f);
}

static void testIncrementDecrement()
{
    Fixed value;

    assert(value.getRawBits() == 0);
    assert(&(++value) == &value);
    assert(value.getRawBits() == 1);
    assert((value++).getRawBits() == 1);
    assert(value.getRawBits() == 2);
    assert(&(--value) == &value);
    assert(value.getRawBits() == 1);
    assert((value--).getRawBits() == 1);
    assert(value.getRawBits() == 0);
}

static void testMinMax()
{
    Fixed low(-2);
    Fixed high(3);
    const Fixed constLow(low);
    const Fixed constHigh(high);

    assert(&Fixed::min(low, high) == &low);
    assert(&Fixed::min(high, low) == &low);
    assert(&Fixed::max(low, high) == &high);
    assert(&Fixed::max(high, low) == &high);
    assert(&Fixed::min(constLow, constHigh) == &constLow);
    assert(&Fixed::max(constHigh, constLow) == &constHigh);
}

int main(void)
{
    testBasics();
    testComparisonsAndArithmetic();
    testIncrementDecrement();
    testMinMax();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
