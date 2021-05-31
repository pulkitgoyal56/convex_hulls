// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#include "geometry/point.h"

#include <cmath>

namespace geometry
{
    Point::Point(double t_x, double t_y) : x(t_x), y(t_y) {}
    double angle(const Point &point_a, const Point &point_b)
    {
        return atan2(point_a.y - point_b.y, point_a.x - point_b.x);
    }
    double operator==(const Point &point_a, const Point &point_b)
    {
        return ((point_a.x == point_b.x) && (point_a.y == point_b.y));
    }
}