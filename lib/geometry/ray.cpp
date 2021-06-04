// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#include "geometry/ray.h"

namespace geometry
{
    Ray::Ray(const Point &t_start, const Point &t_end) : start_(t_start), end_(t_end)
    {
        this->a_ = (this->end_.y - this->start_.y);
        this->b_ = (this->start_.x - this->end_.x);
        this->c_ = (this->start_.y * this->end_.x - this->start_.x * this->end_.y);
    }
    bool Ray::f2(const Point &point) const // {0: "not_on" , 1: "on (including start point)"}
    {
        // if (this->f(point)) // If the point doesn't lie on the line,
        //     return false;   // it doesn't lie on the ray.
        /// This above commented because, in the context of this problem, this function is used only for points already known to lie on the line.

        // If the point and the 'end' of the ray lie on the same side of the ray's starting point,
        if (((point.x - this->start_.x) * (this->end_.x - this->start_.x) >= 0))
            // && ((point.y - this->start_.y) * (this->end_.y - this->start_.y) >= 0))
            return true; // the point lies on the ray.
        else
            return false;
    }
    bool are_intersecting(const Ray &ray_a, const Ray &ray_b)
    {
        if (are_parallel(ray_a, ray_b))
            return false;

        // Find point of intersection of the corresponding lines of ray_a and ray_b.
        Point apparent_point_of_intersection = intersection(ray_b, ray_a);
        // If the point of intersection lies on both the rays,
        if (ray_a.f2(apparent_point_of_intersection) && ray_b.f2(apparent_point_of_intersection))
            return true; // they intersect.
        else
            return false;

        /// <ARCHIVED>
        // // - Alternative method that does not involve finding the intersection point to determine if two line_segments are intersecting.
        // // - Not being used because it does not generalised; not applicable for when a ray is involved.
        // // If both points of a line segment lie on the same side of the other line segment, or vice-versa,
        // if ((line_segment_a.f(line_segment_b.start_) == line_segment_a.f(line_segment_b.end_)) ||
        //     (line_segment_b.f(line_segment_a.start_) == line_segment_b.f(line_segment_a.end_)))
        //     return false; // they don't intersect.
        // else
        //     return true;
    }
}