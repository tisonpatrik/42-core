#include "Point.hpp"

static long double orientation(const Point &a, const Point &b,
                               const Point &point)
{
    // Keep raw products unscaled so even one-step triangles retain their area.
    const long double abX = static_cast<long double>(b.getX().getRawBits())
        - a.getX().getRawBits();
    const long double abY = static_cast<long double>(b.getY().getRawBits())
        - a.getY().getRawBits();
    const long double apX = static_cast<long double>(point.getX().getRawBits())
        - a.getX().getRawBits();
    const long double apY = static_cast<long double>(point.getY().getRawBits())
        - a.getY().getRawBits();

    return abX * apY - abY * apX;
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
    const long double ab = orientation(a, b, point);
    const long double bc = orientation(b, c, point);
    const long double ca = orientation(c, a, point);

    return (ab > 0 && bc > 0 && ca > 0)
        || (ab < 0 && bc < 0 && ca < 0);
}
