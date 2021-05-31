// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#ifndef INCLUDE_GEOMETRY_RAY_H_
#define INCLUDE_GEOMETRY_RAY_H_

#include "geometry/line.h"

namespace geometry
{
    class LineSegment;
    // A ray is a semi-infinite line which starts from `start_` and extends infinitely towards `end_`
    class Ray : public Line
    {
    protected:
        Point start_, end_;

    public:
        Ray(){};
        Ray(const Point &start, const Point &end);

        virtual bool f2(const Point &point) const; // Checks if point lies on the ray.

        friend bool are_intersecting(const Ray &ray_a, const Ray &ray_b);
    };
}

#endif // INCLUDE_GEOMETRY_RAY_H_