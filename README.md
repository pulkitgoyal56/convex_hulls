# README

> NOTE: This project follows the [C++ Core Guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

## Theory

### Pseudocode

``` psuedocode
for every combination of convex hulls:
    make a list of all apexes of either of the convex hull that lie inside the other;
        There are three categories of these points.
            1. Common apexes between the two convex hulls
            2. Those that lie on the edge of the other convex hull
            3. Those that lie properly inside the other convex hull
    add to this list, the intersection points of all the combinations between their edges;
```

## Directory Structure

* `bin/` - Binaries
* `build/` - Build files
* `docs/` - Docs
* `include/` - Header files
* `lib/` - Implementations
* `src/` - Application code
* `tools/` - Complementary tools
* [`CMakeLists.txt`](./CMakeLists.txt)
* [`convex_hulls.json`](./convex_hulls.json)
* [`result_convex_hulls.json`](./result_convex_hulls.json)

## Compiling and Running

``` sh
PG_PROJECT_ROOT="<path/to/the/project/root>"
# or
cd <path/to/the/project/root>
PG_PROJECT_ROOT=$(pwd)
```

``` sh
cmake -S $PG_PROJECT_ROOT -B $PG_PROJECT_ROOT/build
```

``` sh
make -C $PG_PROJECT_ROOT/build && $PG_PROJECT_ROOT/bin/Convex_Hulls $PG_PROJECT_ROOT/convex_hulls.json
```

### Visualization (optional)

Convex Hulls listed in a JSON file can be visualized using the [*visualize.py*](./tools/visualize.py) Python script in the [*tools/*](./tools) directory.  

> Install requirements
>> *matplotlib*

``` sh
cd $PG_PROJECT_ROOT
pip install -r ./tools/requirements.txt
```

> Run script

``` sh
cd $PG_PROJECT_ROOT
python ./tools/visualize.py
```
