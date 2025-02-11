cmake_minimum_required(VERSION 3.12)
project(TSP_Solver)

set(CMAKE_CXX_STANDARD 17)

add_library(tsp_solver 
    src/tsp_solver.cpp 
    src/graph_utils.cpp
)

find_package(GTest REQUIRED)
add_executable(test_tsp_solver tests/test_tsp_solver.cpp)
target_link_libraries(test_tsp_solver tsp_solver GTest::GTest GTest::Main)
