// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#ifndef INCLUDE_GEOMETRY_LINE_H_
#define INCLUDE_GEOMETRY_LINE_H_

#include "geometry/point.h"

namespace geometry
{
    class Line
    {
    protected:
        double a_, b_, c_; //AX + BY + C = 0

    public:
        Line(){};
        Line(double t_a, double t_b, double t_c);

        int f(const Point &point) const;

        friend bool are_parallel(const Line &line_a, const Line &line_b);
        friend Point intersection(const Line &line_a, const Line &line_b);
    };
}

#endif // INCLUDE_GEOMETRY_LINE_H_