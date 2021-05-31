// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#ifndef INCLUDE_GEOMETRY_POLYGON_H_
#define INCLUDE_GEOMETRY_POLYGON_H_

#include <vector>

#include "geometry/point.h"

namespace geometry
{
    class Polygon
    {
    private:
        std::vector<Point> apexes_;
        double x_lower_bound_, x_upper_bound_;
        double y_lower_bound_, y_upper_bound_;

    public:
        int id_;
        int order_;
        double area_;
        Point center_;

        Polygon(){};
        Polygon(const std::vector<Point> &apexes, int _id = -1);

        bool is_in_bounds(const Point &point) const;
        bool f2(const Point &point) const; // Checks if point lies inside the polygon.

        friend double operator&(const Polygon &polygon_a, const Polygon &polygon_b); // from intersection (∩) in set theory
    };
}

#endif // INCLUDE_GEOMETRY_POLYGON_H_