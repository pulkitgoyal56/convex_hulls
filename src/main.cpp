// This code follows the C++ Core Guidelines.
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>

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
        cout << "[INFO] INPUT FILE - " << argv[1] << endl;

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

        int n = convex_hulls.size();

        set<int, greater<int>> removed_hulls;
        for (int i = n; i > 0; --i)
            for (int j = i - 1; j > 0; --j)
            {
                double common_area = convex_hulls[i] & convex_hulls[j];
                if (convex_hulls[i].area_ < (2 * common_area))
                    removed_hulls.insert(i);
                if (convex_hulls[j].area_ < (2 * common_area))
                    removed_hulls.insert(j);
            }

        json output = input;
        for (const int id : removed_hulls)
            output["convex hulls"].erase(id);

        string destination = string(argv[1]).insert(string(argv[1]).rfind("/") + 1, "result_");
        cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "[INFO] OUTPUT FILE - " << destination << endl;

        ofstream output_file(destination);
        output_file << setw(3) << output;

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