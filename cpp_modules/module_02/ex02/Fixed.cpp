#include "Fixed.hpp"

#include <cmath>
#include <stdexcept>

// Round to the nearest raw unit, with halfway values rounded away from zero.
static int roundRawBits(double value)
{
    return static_cast<int>(value + (value < 0.0 ? -0.5 : 0.5));
}

Fixed::Fixed(void) : rawBits(0)
{
}

Fixed::Fixed(const int value) : rawBits(value * (1 << fractionalBits))
{
}

Fixed::Fixed(const float value)
    : rawBits(static_cast<int>(roundf(value * (1 << fractionalBits))))
{
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
    return static_cast<float>(rawBits) / (1 << fractionalBits);
}

int Fixed::toInt(void) const
{
    return rawBits / (1 << fractionalBits);
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
    Fixed result;
    result.rawBits = roundRawBits(static_cast<double>(rawBits)
                                 * other.rawBits / (1 << fractionalBits));
    return result;
}

Fixed Fixed::operator/(const Fixed &other) const
{
    if (other.rawBits == 0)
        throw std::domain_error("division by zero");

    Fixed result;
    result.rawBits = roundRawBits(static_cast<double>(rawBits)
                                 * (1 << fractionalBits) / other.rawBits);
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
    return first <= second ? first : second;
}

const Fixed &Fixed::min(const Fixed &first, const Fixed &second)
{
    return first <= second ? first : second;
}

Fixed &Fixed::max(Fixed &first, Fixed &second)
{
    return first >= second ? first : second;
}

const Fixed &Fixed::max(const Fixed &first, const Fixed &second)
{
    return first >= second ? first : second;
}

std::ostream &operator<<(std::ostream &output, const Fixed &value)
{
    return output << value.toFloat();
}
