// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#include "geometry/polygon.h"

#include <numeric>
#include <iostream>

#include "geometry/line_segment.h"

namespace geometry
{
    Polygon::Polygon(const std::vector<Point> &apexes, int id) : apexes_(apexes), id_(id)
    {
        this->order_ = this->apexes_.size();

        if (this->order_ < 3)
            throw "Polygon cannot be constructed; less than 3 apexes provided.";

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

        // AREA = Σ(y[n] * (x[n+1] - x[n-1]))/2
        // https://www.mathopenref.com/coordpolygonarea.html
        this->area_ = this->apexes_.front().y * (this->apexes_.at(1).x - this->apexes_.back().x) + this->apexes_.back().y * (this->apexes_.front().x - this->apexes_.at(this->apexes_.size() - 2).x);
        for (int i = 1; i < this->apexes_.size() - 1; ++i)
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

        std::cout << "<> NEW POLYGON"
                  << " | ID - " << this->id_
                  << " | ORDER - " << this->order_
                  << " | CENTER - " << this->center_
                  << " | AREA - " << this->area_
                  << " | X_BOUND - "
                  << "[" << this->x_lower_bound_ << ", " << this->x_upper_bound_ << "]"
                  << " | Y_BOUND - "
                  << "[" << this->y_lower_bound_ << ", " << this->y_upper_bound_ << "]"
                  << std::endl;
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
        Ray ray(point, this->center_);
        int crosses = are_intersecting(LineSegment(this->apexes_.back(), this->apexes_.front()), ray);
        if (crosses && (intersection(LineSegment(this->apexes_.back(), this->apexes_.front()), ray) == this->apexes_.back()))
            --crosses;
        for (int i = 1; i < this->order_; ++i)
            if (are_intersecting(LineSegment(this->apexes_.at(i - 1), this->apexes_.at(i)), ray))
                if (!(intersection(LineSegment(this->apexes_.at(i - 1), this->apexes_.at(i)), ray) == this->apexes_.at(i - 1)))
                    ++crosses;
        return crosses % 2;
    }
    double operator&(const Polygon &polygon_a, const Polygon &polygon_b)
    {
        std::vector<Point> contained_points;

        std::cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
        std::cout << "[] INTERSECTING [" << polygon_a.id_ << " & " << polygon_b.id_ << "]" << std::endl;

        // Add apexes of polygon_a inside polygon_b
        for (int k = 0; k < polygon_a.order_; ++k)
        {
            std::cout << "<> TRYING " << k + 1 << "/" << polygon_a.order_ << std::endl;
            std::cout << " > " << polygon_a.apexes_.at(k) << " | " << polygon_b.f2(polygon_a.apexes_.at(k)) << std::endl;
            if (bool inside = polygon_b.f2(polygon_a.apexes_.at(k)))
                contained_points.push_back(polygon_a.apexes_.at(k));
        }

        std::cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
        std::cout << "[] INTERSECTING [" << polygon_b.id_ << " & " << polygon_a.id_ << "]" << std::endl;

        // Add apexes of polygon_b inside polygon_a
        for (int k = 0; k < polygon_b.order_; ++k)
        {
            std::cout << "<> TRYING " << k + 1 << "/" << polygon_b.order_ << std::endl;
            std::cout << " > " << polygon_b.apexes_.at(k) << " | " << polygon_a.f2(polygon_b.apexes_.at(k)) << std::endl;
            if (bool inside = polygon_a.f2(polygon_b.apexes_.at(k)))
                contained_points.push_back(polygon_b.apexes_.at(k));
        }

        for (int i = 0; i < polygon_a.order_ - 1; ++i)
        {
            LineSegment edge_a(polygon_a.apexes_.at(i), polygon_a.apexes_.at(i + 1));
            for (int j = 0; j < polygon_b.order_ - 1; ++j)
            {
                LineSegment edge_b(polygon_b.apexes_.at(j), polygon_b.apexes_.at(j + 1));
                if (are_intersecting(edge_a, edge_b))
                    // Add intersection points of intersecting edge combinations.
                    contained_points.push_back(intersection(edge_a, edge_b));
                if (polygon_a.apexes_.at(i) == polygon_b.apexes_.at(j))
                    // Add common apexes.
                    contained_points.push_back(polygon_a.apexes_.at(i));
            }
        }

        if (contained_points.size())
            return Polygon(contained_points).area_;
        else
            return 0.0;
    }
}
