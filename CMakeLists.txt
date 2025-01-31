cmake_minimum_required(VERSION 3.10)
project(RTCC C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# find_package(criterion REQUIRED)
set(INCLUDE_DIRS include)

set(SOURCE_FILES
    src/tuple.c
    src/canvas.c
    src/algorithms.c
    src/matrix.c
    src/globaldefs.c
)

set(TEST_SOURCES
    tests/tupletest.c
    tests/colortest.c
    tests/canvastest.c
    tests/matrixtest.c
    tests/transformationstest.c
    tests/intersectionstest.c
)

enable_testing()

add_executable(rtccTests ${TEST_SOURCES} ${SOURCE_FILES})
target_link_libraries(rtccTests criterion m)
target_include_directories(rtccTests PRIVATE ${INCLUDE_DIRS})

add_executable(rtccCanvas tests/main.c ${SOURCE_FILES})
target_link_libraries(rtccCanvas m)
target_include_directories(rtccCanvas PRIVATE ${INCLUDE_DIRS})