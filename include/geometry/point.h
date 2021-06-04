// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#ifndef INCLUDE_GEOMETRY_POINT_H_
#define INCLUDE_GEOMETRY_POINT_H_

#include <ostream>

namespace geometry
{
    struct Point
    {
        double x, y;

        Point(){};
        Point(double t_x, double t_y);

        friend double angle(const Point &point_a, const Point &point_b); // Returns the angle that a vector from point_b to point_a makes with the x-axis.
        friend double operator==(const Point &point_a, const Point &point_b);

        friend std::ostream &operator<<(std::ostream &os, const Point &point)
        {
            return os << "(" << point.x << ", " << point.y << ")";
        }
    };
}

#endif // INCLUDE_GEOMETRY_POINT_H_