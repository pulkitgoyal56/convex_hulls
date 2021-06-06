// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#include "geometry/polygon.h"

#include <algorithm>
#include <numeric>

#include "geometry/line_segment.h"

namespace geometry
{
    Polygon::Polygon(const std::vector<Point> &t_apexes, int t_id) : apexes_(t_apexes), id_(t_id)
    {
        this->order_ = this->apexes_.size();

        double center_x = std::accumulate(this->apexes_.begin(), this->apexes_.end(), 0,
                                          [](double sum, const Point &point)
                                          { return sum + point.x; });
        double center_y = std::accumulate(this->apexes_.begin(), this->apexes_.end(), 0,
                                          [](double sum, const Point &point)
                                          { return sum + point.y; });
        this->center_ = Point(center_x / this->order_, center_y / this->order_);

        // arrange/sort apexes
        std::sort(this->apexes_.begin(), this->apexes_.end(),
                  [this](const Point apex_a, const Point apex_b)
                  {
                      return angle(apex_a, this->center_) < angle(apex_b, this->center_);
                  });
        this->apexes_.push_back(this->apexes_.front());

        // AREA = Σ(y[n] * (x[n+1] - x[n-1]))/2
        // https://www.mathopenref.com/coordpolygonarea.html
        this->area_ = this->apexes_.front().y * (this->apexes_.at(1).x - this->apexes_.back().x);
        for (int i = 1; i < this->order_; ++i)
            this->area_ += this->apexes_.at(i).y * (this->apexes_.at(i + 1).x - this->apexes_.at(i - 1).x);
        this->area_ = abs(area_ / 2);

        this->x_lower_bound_ = std::min_element(this->apexes_.begin(), this->apexes_.end(), [](Point const &p1, Point const &p2)
                                                { return (p1.x ? p1.x < p2.x : p2.x); })
                                   ->x;
        this->x_upper_bound_ = std::max_element(this->apexes_.begin(), this->apexes_.end(), [](Point const &p1, Point const &p2)
                                                { return (p1.x ? p1.x < p2.x : p2.x); })
                                   ->x;
        this->y_lower_bound_ = std::min_element(this->apexes_.begin(), this->apexes_.end(), [](Point const &p1, Point const &p2)
                                                { return (p1.y ? p1.y < p2.y : p2.y); })
                                   ->y;
        this->y_upper_bound_ = std::max_element(this->apexes_.begin(), this->apexes_.end(), [](Point const &p1, Point const &p2)
                                                { return (p1.y ? p1.y < p2.y : p2.y); })
                                   ->y;
    }
    bool Polygon::is_in_bounds(const Point &point) const
    {
        return !(point.x <= this->x_lower_bound_ || point.x >= this->x_upper_bound_ || point.y <= this->y_lower_bound_ || point.y >= this->y_upper_bound_);
    }
    bool Polygon::f2(const Point &point) const // {0: "outside/on" , 1: "inside"}
    {
        if (!this->is_in_bounds(point))
            return false;

        if (point == this->center_)
            return true;

        // Ray tracing algorithm to determine if a point lies inside a polygon.
        // - Dray a ray from the point towards the center of the polygon.
        // - If the ray crosses the polygon an odd number of times, the point lies inside the polygon.
        Ray ray(point, this->center_);
        bool crosses = false;
        for (int i = 0; i < this->order_; ++i)
            if (are_intersecting(LineSegment(this->apexes_.at(i), this->apexes_.at(i + 1)), ray))
                crosses = !crosses;
        return crosses;
    }
    double operator&(const Polygon &polygon_a, const Polygon &polygon_b)
    {
        std::vector<Point> contained_points;

        // Add apexes of polygon_a inside polygon_b.
        for (int k = 0; k < polygon_a.order_; ++k)
            if (bool inside = polygon_b.f2(polygon_a.apexes_.at(k)))
                contained_points.push_back(polygon_a.apexes_.at(k));

        // Add apexes of polygon_b inside polygon_a.
        for (int k = 0; k < polygon_b.order_; ++k)
            if (bool inside = polygon_a.f2(polygon_b.apexes_.at(k)))
                contained_points.push_back(polygon_b.apexes_.at(k));

        for (int i = 0; i < polygon_a.order_; ++i)
        {
            LineSegment edge_a(polygon_a.apexes_.at(i), polygon_a.apexes_.at(i + 1));
            for (int j = 0; j < polygon_b.order_; ++j)
            {
                LineSegment edge_b(polygon_b.apexes_.at(j), polygon_b.apexes_.at(j + 1));
                // Add intersection points of intersecting edge combinations.
                if (are_intersecting(edge_a, edge_b))
                    contained_points.push_back(intersection(edge_a, edge_b));
                // Add common apexes between polygon_a and polygon_b.
                if (polygon_a.apexes_.at(i) == polygon_b.apexes_.at(j))
                    contained_points.push_back(polygon_a.apexes_.at(i));
            }
        }

        if (contained_points.size())
            return Polygon(contained_points).area_;
        else
            return 0.0;
    }
}