#pragma once
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>

class TSPSolver {
public:
    int solveWithDP(const std::vector<std::vector<int>>& graph);
    int solveWithBranchAndBound(const std::vector<std::vector<int>>& graph);

private:
    struct BnBState {
        int cost;
        int current;
        int visited;
        std::vector<int> path;
        
        BnBState(int c, int n, int v, std::vector<int> p)
            : cost(c), current(n), visited(v), path(p) {}
    };

    using MemoKey = std::pair<int, unsigned>;
    struct MemoHash {
        size_t operator()(const MemoKey& k) const;
    };
};
