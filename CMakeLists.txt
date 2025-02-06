cmake_minimum_required(VERSION 3.10)
project(RTCC C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# find_package(criterion REQUIRED)
set(INCLUDE_DIRS include)

set(SOURCE_FILES
    src/extras/algorithms.c
    src/extras/globaldefs.c

    src/graphics/canvas.c

    src/maths/tuple.c
    src/maths/matrix.c
    src/maths/geometries.c

    src/physics/light.c
    src/physics/ray.c
    src/physics/intersections.c
)

set(TEST_SOURCES
    tests/canvastest.c
    tests/colortest.c
    tests/intersectionstest.c
    tests/materialstest.c
    tests/matrixtest.c
    tests/spheretest.c
    tests/transformationstest.c
    tests/tupletest.c
    tests/lightingtest.c
)

enable_testing()

add_executable(rtccTests ${TEST_SOURCES} ${SOURCE_FILES})
target_link_libraries(rtccTests criterion m)
target_include_directories(rtccTests PRIVATE ${INCLUDE_DIRS})

add_executable(rtccMain tests/main.c ${SOURCE_FILES})
target_link_libraries(rtccMain m)
target_include_directories(rtccMain PRIVATE ${INCLUDE_DIRS})