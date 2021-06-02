# README

> NOTE: This project follows the [C++ Core Guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

## Directory Structure

* `bin/` - Binaries
* `build/` - Build files
* `docs/` - Docs
* `include/` - Header files
* `lib/` - Implementations
* `src/` - Application code
* `tools/` - Complementary tools
* [`CMakeLists.txt`](CMakeLists.txt)

## Compiling and Running

``` sh
mkdir -p $PROJECT_ROOT/build && cd $PROJECT_ROOT/build && cmake ..
make && ../bin/Convex_Hulls $PROJECT_ROOT/docs/convex_hulls.json
```
