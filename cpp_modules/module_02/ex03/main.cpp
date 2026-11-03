#include "Point.hpp"

#include <cassert>
#include <iostream>

static void testPoint()
{
    const Point origin;
    const Point source(-1.5f, 2.25f);
    const Point copy(source);
    Point assigned;

    assert(origin.getX().getRawBits() == 0);
    assert(origin.getY().getRawBits() == 0);
    assert(copy.getX().toFloat() == -1.5f);
    assert(copy.getY().toFloat() == 2.25f);
    assert(&(assigned = copy) == &assigned);
    assert(assigned.getX().getRawBits() == 0);
    assert(assigned.getY().getRawBits() == 0);
}

int main(void)
{
    testPoint();

    const Point a(0.0f, 0.0f);
    const Point b(4.0f, 0.0f);
    const Point c(0.0f, 4.0f);
    const Point inside(1.0f, 1.0f);

    assert(bsp(a, b, c, inside));
    assert(bsp(a, c, b, inside));
    assert(!bsp(a, b, c, Point(3.0f, 3.0f)));
    assert(!bsp(a, b, c, Point(-1.0f, 1.0f)));
    assert(!bsp(a, b, c, Point(1.0f, -1.0f)));
    assert(!bsp(a, b, c, Point(2.0f, 0.0f)));
    assert(!bsp(a, b, c, Point(2.0f, 2.0f)));
    assert(!bsp(a, b, c, Point(0.0f, 2.0f)));
    assert(!bsp(a, b, c, a));
    assert(!bsp(a, b, c, b));
    assert(!bsp(a, b, c, c));
    assert(!bsp(a, a, c, inside));
    assert(!bsp(a, Point(2.0f, 2.0f), Point(4.0f, 4.0f), inside));

    std::cout << "All tests passed." << std::endl;
    return 0;
}
