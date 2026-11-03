#include "Fixed.hpp"

#include <cmath>
#include <iostream>

Fixed::Fixed(void) : rawBits(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value) : rawBits(0)
{
    const int scale = 1 << fractionalBits;
    rawBits = value * scale;
    std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float value) : rawBits(0)
{
    const int scale = 1 << fractionalBits; // 2^8 = 256 raw units per whole number.
    const float scaledValue = value * scale;
    const float roundedValue = roundf(scaledValue);

    rawBits = static_cast<int>(roundedValue);
    std::cout << "Float constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other) : rawBits(0)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed &Fixed::operator=(const Fixed &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        rawBits = other.rawBits;
    return *this;
}

Fixed::~Fixed(void)
{
    std::cout << "Destructor called" << std::endl;
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

std::ostream &operator<<(std::ostream &output, const Fixed &value)
{
    return output << value.toFloat();
}
