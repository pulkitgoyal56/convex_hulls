---
author: Pulkit Goyal
date: Jun 19, 2021
---

# CONVEX HULLS

> Problem Statement - [./docs/MaaS_General-Challenge_Directions.pdf](./docs/MaaS_General-Challenge_Directions.pdf)  
> NOTE: This project follows the [C++ Core Guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

---

1. [Theory](#theory)
   1. [Pseudocode (High Level)](#pseudocode-high-level)
2. [Class Hierarchy](#class-hierarchy)
3. [Directory Structure](#directory-structure)
4. [Running](#running)
   1. [Install Requirements (C++)](#install-requirements-c)
   2. [Setup](#setup)
   3. [Generate Build Files](#generate-build-files)
   4. [Compile/Build](#compilebuild)
   5. [Execute](#execute)
   6. [Visualize (optional)](#visualize-optional)
      1. [Install Requirements (Python)](#install-requirements-python)
      2. [Run Script](#run-script)
5. [Results](#results)

---

## Theory

### Pseudocode (High Level)

``` psuedocode
for every combination of convex hulls:
    make a list of all apexes of either of the convex hull that lie inside the other;
        There are three categories of these points.
            1. Common apexes between the two convex hulls
            2. Those that lie on the edge of the other convex hull
            3. Those that lie properly inside the other convex hull
    add to this list, the intersection points of all the combinations between their edges;
```

---

## Class Hierarchy

* [`struct Point`](./include/geometry/point.h)  
* [`class Line`](./include/geometry/line.h)  
  * [`class Ray: Line`](./include/geometry/ray.h)  
    * [`class LineSegment: Ray`](./include/geometry/line_segment.h)  
* [`class Polygon`](./include/geometry/polygon.h)  

---

## Directory Structure

* [`bin/`](./bin) -- Binaries
* [`build/`](./build) -- Build files
* [`docs/`](./docs) -- Docs
* [`include/`](./include) -- Header files
* [`lib/`](./lib) -- Implementations
* [`src/`](./src) -- Application code
* [`tools/`](./tools) -- Complementary tools
* [`CMakeLists.txt`](./CMakeLists.txt)
* [`convex_hulls.json`](./convex_hulls.json) -- Input file
* [`result_convex_hulls.json`](./result_convex_hulls.json) -- Output file

---

## Running

> NOTE: Documentation relevant for Unix-like OS.  

>> This program was developed on *MacOS Big Sur 11.2.3* using  
>>> | `Apple clang version 12.0.0 (clang-1200.0.32.27)`  
>>> | `cmake version 3.19.6`  

>> Also tested on *Ubuntu 20.04.02 LTS on Windows 10 x86_64* using
>>> | `g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0`  
>>> | `cmake version 3.16.3`  

### Install Requirements (C++)

> C++ compiler like `g++` or `clang`  

``` sh
sudo apt install build-essential ## install gcc/g++
```

> *CMake* (*v3.10* or above)  

``` sh
sudo apt install cmake
```

### Setup

``` sh
PG_PROJECT_ROOT="<path/to/the/project/root>"
　## or
cd <path/to/the/project/root>
PG_PROJECT_ROOT=$(pwd)
```

### Generate Build Files

``` sh
cmake -S $PG_PROJECT_ROOT -B $PG_PROJECT_ROOT/build
```

### Compile/Build

``` sh
make -C $PG_PROJECT_ROOT/build
```

### Execute

``` sh
$PG_PROJECT_ROOT/bin/Convex_Hulls $PG_PROJECT_ROOT/convex_hulls.json
```

### Visualize (optional)

Convex Hulls listed in a JSON file can be visualized using the [*visualize.py*](./tools/visualize.py) Python script in the [*tools/*](./tools) directory.  

> NOTE: This script was developed in Python3.8 on MacOS

#### Install Requirements (Python)

> *matplotlib*

``` sh
cd $PG_PROJECT_ROOT
pip install -r ./tools/requirements.txt
```

#### Run Script

``` sh
cd $PG_PROJECT_ROOT
python ./tools/visualize.py
```

---

## Results

> Input - [`convex_hulls.json`](./convex_hulls.json).  
![*Input Convex Hulls*](./tools/visualize_convex_hulls.png)
> Output - [`result_convex_hulls.json`](./result_convex_hulls.json).  
![*Output Convex Hulls*](./tools/visualize_result_convex_hulls.png)
