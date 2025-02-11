#include "tsp_solver.hpp"
#include <gtest/gtest.h>

TEST(TSPSolver, DP_Solution) {
    TSPSolver solver;
    std::vector<std::vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    EXPECT_EQ(solver.solveWithDP(graph), 80);
}

TEST(TSPSolver, BranchAndBound_Solution) {
    TSPSolver solver;
    std::vector<std::vector<int>> graph = {
        {0, 10, 15, 20},
        {5, 0, 9, 10},
        {6, 13, 0, 12},
        {8, 8, 9, 0}
    };
    EXPECT_EQ(solver.solveWithBranchAndBound(graph), 35);
}
