// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#include <iostream>

#include <fstream>

#include "nlohmann/json.hpp"
#include "geometry/polygon.h"
#include "geometry/line_segment.h"

// Using the `using namespace` directive as there is no ambiguity between `std` and `geometry` -- SF.6
using namespace std;
using namespace geometry;
using json = nlohmann::json; //for convenience

int main(int argc, char **argv)
{
    try
    {
        if (argc != 2)
            throw "NO INPUT FILE SPECIFIED";
        ifstream input_file(argv[1]);
        if (!input_file.is_open())
            throw "INPUT FILE COULDN'T BE OPENED";

        cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << fixed << setprecision(2);
        cout << "[INFO] INPUT FILE - " << argv[1] << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";

        json input;
        input_file >> input;

        vector<Polygon> convex_hulls;
        for (const auto convex_hull : input["convex hulls"])
        {
            vector<Point> apexes;
            for (const auto apex : convex_hull["apexes"])
                apexes.push_back(Point(apex["x"], apex["y"]));

            convex_hulls.push_back(Polygon(apexes, convex_hull["ID"]));
        }

        cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";

        int n = convex_hulls.size();

        vector<bool> removed_hulls(n);
        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                double common_area = convex_hulls[i] & convex_hulls[j];
                removed_hulls.at(convex_hulls[i].id_) = removed_hulls.at(convex_hulls[i].id_) | (convex_hulls[i].area_ < (2 * common_area));
                removed_hulls.at(convex_hulls[j].id_) = removed_hulls.at(convex_hulls[j].id_) | (convex_hulls[j].area_ < (2 * common_area));
            }
        }

        cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";

        for (int k = 0; k < n; ++k)
            if (!removed_hulls.at(k))
                cout << k << " ";

        cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "[INFO] DONE." << endl;
    }
    catch (const char *msg)
    {
        cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "[ERROR] " << msg << endl;
        return 1;
    }
}