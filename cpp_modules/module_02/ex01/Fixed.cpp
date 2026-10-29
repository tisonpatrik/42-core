#include "Fixed.hpp"

#include <cmath>
#include <iostream>

Fixed::Fixed(void) : rawBits(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value) : rawBits(value * (1 << fractionalBits))
{
    std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float value)
    : rawBits(static_cast<int>(roundf(value * (1 << fractionalBits))))
{
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
    return static_cast<float>(rawBits) / (1 << fractionalBits);
}

int Fixed::toInt(void) const
{
    return rawBits / (1 << fractionalBits);
}

std::ostream &operator<<(std::ostream &output, const Fixed &value)
{
    return output << value.toFloat();
}
