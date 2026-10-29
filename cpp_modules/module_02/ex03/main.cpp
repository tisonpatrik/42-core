#include "Point.hpp"

#include <cassert>
#include <iostream>

static void testPointConstruction()
{
    const Point origin;
    const Point source(-1.5f, 2.25f);

    const Point copy(source);

    assert(origin.getX().getRawBits() == 0);
    assert(origin.getY().getRawBits() == 0);
    assert(copy.getX().toFloat() == -1.5f);
    assert(copy.getY().toFloat() == 2.25f);
}

static void testPointAssignmentPreservesCoordinates()
{
    Point target(1.0f, 2.0f);
    const Point source(3.0f, 4.0f);

    Point &result = (target = source);

    assert(&result == &target);
    assert(target.getX().toFloat() == 1.0f);
    assert(target.getY().toFloat() == 2.0f);
    assert(source.getX().toFloat() == 3.0f);
    assert(source.getY().toFloat() == 4.0f);
}

static void testInsideInBothDirections()
{
    const Point a(0.0f, 0.0f);
    const Point b(4.0f, 0.0f);
    const Point c(0.0f, 4.0f);
    const Point point(1.0f, 1.0f);

    const bool counterclockwise = bsp(a, b, c, point);
    const bool clockwise = bsp(a, c, b, point);

    assert(counterclockwise);
    assert(clockwise);
    assert(bsp(b, c, a, point));
    assert(bsp(c, a, b, point));
    assert(bsp(c, b, a, point));
    assert(bsp(b, a, c, point));
}

static void testOutsideEachEdge()
{
    const Point a(0.0f, 0.0f);
    const Point b(4.0f, 0.0f);
    const Point c(0.0f, 4.0f);

    const bool below = bsp(a, b, c, Point(1.0f, -1.0f));
    const bool above = bsp(a, b, c, Point(3.0f, 3.0f));
    const bool left = bsp(a, b, c, Point(-1.0f, 1.0f));

    assert(!below);
    assert(!above);
    assert(!left);
}

static void testEdgesAreExcluded()
{
    const Point a(0.0f, 0.0f);
    const Point b(4.0f, 0.0f);
    const Point c(0.0f, 4.0f);

    const bool onAB = bsp(a, b, c, Point(2.0f, 0.0f));
    const bool onBC = bsp(a, b, c, Point(2.0f, 2.0f));
    const bool onCA = bsp(a, b, c, Point(0.0f, 2.0f));

    assert(!onAB);
    assert(!onBC);
    assert(!onCA);
}

static void testVerticesAreExcluded()
{
    const Point a(0.0f, 0.0f);
    const Point b(4.0f, 0.0f);
    const Point c(0.0f, 4.0f);

    const bool atA = bsp(a, b, c, a);
    const bool atB = bsp(a, b, c, b);
    const bool atC = bsp(a, b, c, c);

    assert(!atA);
    assert(!atB);
    assert(!atC);
}

static void testDegenerateTriangles()
{
    const Point a(0.0f, 0.0f);
    const Point b(2.0f, 2.0f);
    const Point c(4.0f, 4.0f);

    const bool onLine = bsp(a, b, c, Point(1.0f, 1.0f));
    const bool offLine = bsp(a, b, c, Point(1.0f, 2.0f));
    const bool repeatedVertex = bsp(a, a, c, Point(1.0f, 2.0f));
    const bool identicalVertices = bsp(a, a, a, a);

    assert(!onLine);
    assert(!offLine);
    assert(!repeatedVertex);
    assert(!identicalVertices);
}

static void testNegativeCoordinates()
{
    const Point a(-4.0f, -4.0f);
    const Point b(0.0f, -4.0f);
    const Point c(-4.0f, 0.0f);

    const bool inside = bsp(a, b, c, Point(-3.0f, -3.0f));
    const bool outside = bsp(a, b, c, Point(-1.0f, -1.0f));
    const bool onEdge = bsp(a, b, c, Point(-2.0f, -2.0f));

    assert(inside);
    assert(!outside);
    assert(!onEdge);
}

static void testSmallTriangle()
{
    const float step = 1.0f / 256.0f;
    const Point a(0.0f, 0.0f);
    const Point b(3 * step, 0.0f);
    const Point c(0.0f, 3 * step);

    const bool inside = bsp(a, b, c, Point(step, step));
    const bool onEdge = bsp(a, b, c, Point(2 * step, step));
    const bool outside = bsp(a, b, c, Point(2 * step, 2 * step));

    assert(inside);
    assert(!onEdge);
    assert(!outside);
}

static void testOneStepFromEdge()
{
    const float step = 1.0f / 256.0f;
    const Point a(0.0f, 0.0f);
    const Point b(4.0f, 0.0f);
    const Point c(0.0f, 4.0f);

    const bool inside = bsp(a, b, c, Point(2.0f, 2.0f - step));
    const bool onEdge = bsp(a, b, c, Point(2.0f, 2.0f));
    const bool outside = bsp(a, b, c, Point(2.0f, 2.0f + step));

    assert(inside);
    assert(!onEdge);
    assert(!outside);
}

static void testLargeTriangle()
{
    const Point a(-1000000.0f, -1000000.0f);
    const Point b(1000000.0f, -1000000.0f);
    const Point c(0.0f, 1000000.0f);

    const bool inside = bsp(a, b, c, Point(0.0f, 0.0f));
    const bool outside = bsp(a, b, c, Point(1000000.0f, 1000000.0f));

    assert(inside);
    assert(!outside);
}

int main(void)
{
    testPointConstruction();
    testPointAssignmentPreservesCoordinates();
    testInsideInBothDirections();
    testOutsideEachEdge();
    testEdgesAreExcluded();
    testVerticesAreExcluded();
    testDegenerateTriangles();
    testNegativeCoordinates();
    testSmallTriangle();
    testOneStepFromEdge();
    testLargeTriangle();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
