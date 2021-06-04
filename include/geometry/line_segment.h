// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#ifndef INCLUDE_GEOMETRY_LINE_SEGMENT_H_
#define INCLUDE_GEOMETRY_LINE_SEGMENT_H_

#include "geometry/ray.h"

namespace geometry
{
    // A line_segment is a ray that ends at `end_`.
    class LineSegment : public Ray
    {
    public:
        LineSegment(){};
        LineSegment(const Point &t_start, const Point &t_end);

        bool f2(const Point &point) const; // Checks if point lies on the line segment.
    };
}

#endif // INCLUDE_GEOMETRY_LINE_SEGMENT_H_