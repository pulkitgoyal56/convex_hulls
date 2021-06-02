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
    bool Ray::f2(const Point &point) const // {0: "not_on/start" , 1: "on"}
    {
        // if (this->f(point)) // If the point doesn't lie on the line,
        //     return false;   // it doesn't lie on the ray.

        if (((point.x - this->start_.x) * (this->end_.x - this->start_.x) > 0) &&
            ((point.y - this->start_.y) * (this->end_.y - this->start_.y) > 0))
            // If the point and the 'end' of the ray lie lie on the same side of the ray's starting point
            return true; // the point lies on the ray.
        else
            return false;
    }
    bool are_intersecting(const Ray &ray_a, const Ray &ray_b)
    {
        if (are_parallel(ray_a, ray_b))
            return false;

        Point apparent_point_of_intersection = intersection(ray_b, ray_a);
        if (ray_a.f2(apparent_point_of_intersection) && ray_b.f2(apparent_point_of_intersection))
            return true;
        else
            return false;

        /// <ARCHIVED>
        // if (are_parallel(ray_a, ray_b))
        // // If the lines are parallel, and
        // {
        //     // (c1*b2 == c2*b1)
        //     if ((ray_a.c_ * ray_b.b_ == ray_b.c_ * ray_a.b_) &&
        //         // the lines are collinear, and
        //         (ray_a.f2(ray_b.start_) || ray_a.f2(ray_b.end_) ||
        //          ray_b.f2(ray_a.start_) || ray_b.f2(ray_a.end_)))
        //         // if any of the two line segments contains at least one of the end points of the other line,
        //         return true; // they intersect.
        //     else
        //         return false;
        // }
        // else if ((line_segment_a.f2(line_segment_b.start_) == line_segment_a.f2(line_segment_b.end_)) ||
        //          (line_segment_b.f2(line_segment_a.start_) == line_segment_b.f2(line_segment_a.end_)))
        //     // If both points of a line segment lie on the same side of the other line segment, or vice-versa,
        //     return false; // they don't intersect.
        // else
        //     return true;
    }
}