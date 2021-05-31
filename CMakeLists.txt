cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(DCMAKE_BUILD_TYPE Debug)

project(Convex_Hulls)

include_directories(include)

add_executable(Convex_Hulls
    src/main.cpp
    lib/geometry/polygon.cpp
    lib/geometry/line_segment.cpp
    lib/geometry/ray.cpp
    lib/geometry/line.cpp
    lib/geometry/point.cpp
)
