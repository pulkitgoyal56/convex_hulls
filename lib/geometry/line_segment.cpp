// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#include "geometry/line_segment.h"

namespace geometry
{
    LineSegment::LineSegment(const Point &t_start, const Point &t_end) : Ray(t_start, t_end) {}
    bool LineSegment::f2(const Point &point) const // {0: "not_on/start/end" , 1: "on"}
    {
        // if (this->f(point)) // If the point doesn't lie on the line,
        //     return false;   // it doesn't lie on the line segment.

        if (((point.x - this->start_.x) * (point.x - this->end_.x) < 0) &&
            ((point.y - this->start_.y) * (point.y - this->end_.y) < 0))
            // If the point lies on the opposite side of both the ends of the line segment,
            return true; // it lies on the line segment.
        else
            return false;
    }
}
