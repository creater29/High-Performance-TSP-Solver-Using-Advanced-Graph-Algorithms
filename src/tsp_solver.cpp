#include "tsp_solver.hpp"
#include <climits>
#include <bitset>

// Dynamic Programming Implementation
int TSPSolver::solveWithDP(const std::vector<std::vector<int>>& graph) {
    const int n = graph.size();
    std::unordered_map<MemoKey, int, MemoHash> memo;

    std::function<int(int, unsigned)> dp = [&](int pos, unsigned visited) {
        if (visited == (1u << n) - 1) 
            return graph[pos][0];
        
        MemoKey key = {pos, visited};
        if (memo.find(key) != memo.end()) 
            return memo[key];
        
        int min_cost = INT_MAX;
        for (int next = 0; next < n; ++next) {
            if (!(visited & (1 << next))) {
                int new_cost = graph[pos][next] + dp(next, visited | (1 << next));
                min_cost = std::min(min_cost, new_cost);
            }
        }
        return memo[key] = min_cost;
    };

    return dp(0, 1u << 0);
}

// Branch and Bound Implementation
int TSPSolver::solveWithBranchAndBound(const std::vector<std::vector<int>>& graph) {
    const int n = graph.size();
    auto comparator = [](const BnBState& a, const BnBState& b) {
        return a.cost > b.cost; // Min-heap
    };
    
    std::priority_queue<BnBState, std::vector<BnBState>, decltype(comparator)> pq(comparator);
    pq.emplace(0, 0, 1 << 0, std::vector<int>{0});
    int best_cost = INT_MAX;

    while (!pq.empty()) {
        auto [cost, current, visited, path] = pq.top();
        pq.pop();

        if (path.size() == n) {
            int total = cost + graph[current][0];
            if (total < best_cost) best_cost = total;
            continue;
        }

        for (int next = 0; next < n; ++next) {
            if (!(visited & (1 << next))) {
                int new_cost = cost + graph[current][next];
                if (new_cost >= best_cost) continue;
                
                std::vector<int> new_path = path;
                new_path.push_back(next);
                pq.emplace(new_cost, next, visited | (1 << next), new_path);
            }
        }
    }
    return best_cost;
}

// Memoization Hash Function
size_t TSPSolver::MemoHash::operator()(const MemoKey& k) const {
    return k.second ^ (k.first << 16);
}
