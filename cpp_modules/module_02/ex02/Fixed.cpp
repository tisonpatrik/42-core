#include "Fixed.hpp"

#include <cmath>
#include <stdexcept>

// Round to the nearest raw unit, with halfway values rounded away from zero.
static int roundRawBits(double value)
{
    const double halfUnit = 0.5;

    // Conversion to int truncates toward zero; adjust by half a unit first.
    if (value < 0.0)
        value -= halfUnit;
    else
        value += halfUnit;

    return static_cast<int>(value);
}

Fixed::Fixed(void) : rawBits(0)
{
}

Fixed::Fixed(const int value) : rawBits(0)
{
    const int scale = 1 << fractionalBits;
    rawBits = value * scale;
}

Fixed::Fixed(const float value) : rawBits(0)
{
    const int scale = 1 << fractionalBits; // 2^8 = 256 raw units per whole number.
    const float scaledValue = value * scale;
    const float roundedValue = roundf(scaledValue);

    rawBits = static_cast<int>(roundedValue);
}

Fixed::Fixed(const Fixed &other) : rawBits(other.rawBits)
{
}

Fixed &Fixed::operator=(const Fixed &other)
{
    if (this != &other)
        rawBits = other.rawBits;
    return *this;
}

Fixed::~Fixed(void)
{
}

int Fixed::getRawBits(void) const
{
    return rawBits;
}

void Fixed::setRawBits(int const raw)
{
    rawBits = raw;
}

float Fixed::toFloat(void) const
{
    const int scale = 1 << fractionalBits;
    const float value = static_cast<float>(rawBits);
    return value / scale;
}

int Fixed::toInt(void) const
{
    const int scale = 1 << fractionalBits;
    return rawBits / scale;
}

bool Fixed::operator>(const Fixed &other) const
{
    return rawBits > other.rawBits;
}

bool Fixed::operator<(const Fixed &other) const
{
    return rawBits < other.rawBits;
}

bool Fixed::operator>=(const Fixed &other) const
{
    return rawBits >= other.rawBits;
}

bool Fixed::operator<=(const Fixed &other) const
{
    return rawBits <= other.rawBits;
}

bool Fixed::operator==(const Fixed &other) const
{
    return rawBits == other.rawBits;
}

bool Fixed::operator!=(const Fixed &other) const
{
    return rawBits != other.rawBits;
}

Fixed Fixed::operator+(const Fixed &other) const
{
    Fixed result;
    result.rawBits = rawBits + other.rawBits;
    return result;
}

Fixed Fixed::operator-(const Fixed &other) const
{
    Fixed result;
    result.rawBits = rawBits - other.rawBits;
    return result;
}

Fixed Fixed::operator*(const Fixed &other) const
{
    const int scale = 1 << fractionalBits;
    const double leftRawValue = rawBits;
    const double rightRawValue = other.rawBits;
    const double product = leftRawValue * rightRawValue;
    const double scaledProduct = product / scale;

    Fixed result;
    result.rawBits = roundRawBits(scaledProduct);
    return result;
}

Fixed Fixed::operator/(const Fixed &other) const
{
    if (other.rawBits == 0)
        throw std::domain_error("division by zero");

    const int scale = 1 << fractionalBits;
    const double rawValue = rawBits;
    const double scaledDividend = rawValue * scale;
    const double quotient = scaledDividend / other.rawBits;

    Fixed result;
    result.rawBits = roundRawBits(quotient);
    return result;
}

Fixed &Fixed::operator++(void)
{
    ++rawBits;
    return *this;
}

Fixed Fixed::operator++(int)
{
    Fixed previous(*this);
    ++(*this);
    return previous;
}

Fixed &Fixed::operator--(void)
{
    --rawBits;
    return *this;
}

Fixed Fixed::operator--(int)
{
    Fixed previous(*this);
    --(*this);
    return previous;
}

Fixed &Fixed::min(Fixed &first, Fixed &second)
{
    if (first <= second)
        return first;
    return second;
}

const Fixed &Fixed::min(const Fixed &first, const Fixed &second)
{
    if (first <= second)
        return first;
    return second;
}

Fixed &Fixed::max(Fixed &first, Fixed &second)
{
    if (first >= second)
        return first;
    return second;
}

const Fixed &Fixed::max(const Fixed &first, const Fixed &second)
{
    if (first >= second)
        return first;
    return second;
}

std::ostream &operator<<(std::ostream &output, const Fixed &value)
{
    return output << value.toFloat();
}
