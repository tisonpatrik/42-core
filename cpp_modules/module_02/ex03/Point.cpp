#include "Point.hpp"

Point::Point(void) : x(), y()
{
}

Point::Point(const float x, const float y) : x(x), y(y)
{
}

Point::Point(const Point &other) : x(other.x), y(other.y)
{
}

Point &Point::operator=(const Point &other)
{
    // Coordinates are const: assignment preserves this point's position.
    (void)other;
    return *this;
}

Point::~Point(void)
{
}

const Fixed &Point::getX(void) const
{
    return x;
}

const Fixed &Point::getY(void) const
{
    return y;
}
