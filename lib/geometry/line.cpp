// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#include "geometry/line.h"

namespace geometry
{
    Line::Line(double t_a, double t_b, double t_c) : a_(t_a), b_(t_b), c_(t_c) {}
    /// <ARCHIVED> -- An basic requirement, but isn't used anywhere in the active code.
    // int Line::f(const Point &point) const
    // {
    //     double value = this->a_ * point.x + this->b_ * point.y + this->c_;
    //     if (value > 0)
    //         return 1;
    //     else if (value < 0)
    //         return -1;
    //     else
    //         return 0;
    // }
    bool are_parallel(const Line &line_a, const Line &line_b)
    {
        // (a1*b2 == a2*b1)
        return (line_a.a_ * line_b.b_ == line_b.a_ * line_a.b_);
    }
    Point intersection(const Line &line_a, const Line &line_b)
    {
        // if (are_parallel(line_a, line_b))
        //     throw "Cannot find intersection; lines are parallel.";

        // x12 = (b1*c2 - b2*c1)/(a1*b2 - a2*b1)
        double x = (line_a.b_ * line_b.c_ - line_b.b_ * line_a.c_) / (line_a.a_ * line_b.b_ - line_b.a_ * line_a.b_);
        // y12 = (a1*c2 - a2*c1)/(b1*a2 - b2*a1)
        double y = (line_a.a_ * line_b.c_ - line_b.a_ * line_a.c_) / (line_a.b_ * line_b.a_ - line_b.b_ * line_a.a_);

        return Point(x, y);
    }
}
