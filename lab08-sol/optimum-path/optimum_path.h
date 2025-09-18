#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <limits>
#include <concepts>

// You should NOT add ANY other includes.
// DO NOT add "using namespace std;" as it is a bad practice.

template <typename T>
concept numeric = std::is_arithmetic_v<T>;
// A concept in C++ is a compile-time constraint that defines requirements for template 
// parameters. It helps in template 
// type checking by restricting the types that can be used in templates

template <typename Value, numeric Cost>
class graph_t {
    // You should NOT modify ANYTHING in this structure.
public:
    class std::vector<Value> vertices;
    class std::vector<std::vector<std::pair<int, Cost>>> edges;
    // The class keyword above is unneccessary, redundant but valid,
    // The keyword emphasizes that std::vector<Value> is a class type. This can sometimes help 
    // disambiguate in complex template or dependent type scenarios.

    graph_t() = default;
    graph_t(const std::vector<Value>& __vertices) : 
        vertices(__vertices), edges(__vertices.size()) {}   // edges initialize with size[that repre outer vector]
    graph_t(const std::vector<Value>& __vertices, 
            const std::vector<std::tuple<int, int, Cost>>& __edges) : 
        vertices(__vertices), edges(__vertices.size()) {
        for (const auto& [from, to, cost] : __edges) {
            add_edge(from, to, cost);
        }
    }

    // Copy constructor/assignment = copying from existing object.
    // Move constructor/assignment = transferring from temporaries/rvalues.
    graph_t(const graph_t&) = default;
    graph_t(graph_t&&) = default;
    graph_t& operator=(const graph_t&) = default;
    graph_t& operator=(graph_t&&) = default;
    virtual ~graph_t() = default; // safe polymor
    void add_edge(const int& from, const int& to, const Cost& cost) {
        this->edges[from].push_back({to, cost});
    }
};

                                            // Default comparator is less(minimum)
template <typename Value, numeric Cost, class Compare = std::less<Cost>>
class optimum_path_querier {
    // You should NOT modify public function signatures and constructors.
public:
    optimum_path_querier(const graph_t<Value, Cost> &graph, const int& start, 
        std::function<Cost(const Cost&, const Value&, const Cost&)> add_costs);// lamda method as arg
    std::vector<int> get_optimum_path(const int& end);
protected:
    // TODO: Write your data structures and subroutines here
    class std::vector<std::pair<Cost, int>> optimum_path_step;
    // End TODO
};

template <typename Value, numeric Cost, class Compare>
optimum_path_querier<Value, Cost, Compare>::optimum_path_querier(
        const graph_t<Value, Cost> &graph, const int& start, 
        std::function<Cost(const Cost&, const Value&, const Cost&)> add_costs) {    // lambda function for cost computation.
    // TODO: Write your code here
    Compare compare;
    std::priority_queue<
    std::pair<Cost, int>,                   // elements stored
    std::vector<std::pair<Cost, int>>,      // Underlying container
    std::function<bool(const std::pair<Cost, int>&,
                       const std::pair<Cost, int>&)>>   // Comparator type
    costs_to([&compare](const std::pair<Cost, int>& a,  // Comparator instance
                        const std::pair<Cost, int>& b) {
        return !compare(a.first, b.first);
        /*The priority queue expects the comparator to return true if a should come after b. That’s why it’s wrapped as !compare(a.first, b.first)*/      
    });         // lambda comparator is used as inline functor.

    // pq initialization condition.
    if (compare(0, std::numeric_limits<Cost>::max())) {     // min-heap type implementation
        costs_to.push({0, start});                          // starting node with cost 0
        this->optimum_path_step.resize(graph.vertices.size(), // everything is INF initially
                std::make_pair(std::numeric_limits<Cost>::max(), -1));
        this->optimum_path_step[start] = std::make_pair(0, start); // cost to reach start 0
    } else {                    // max-heap type implementation.
        costs_to.push({std::numeric_limits<Cost>::max(), start}); // start with INF cost
        this->optimum_path_step.resize(graph.vertices.size(), // everything is 0 initially
                std::make_pair(0, -1));
        this->optimum_path_step[start] = std::make_pair(
                std::numeric_limits<Cost>::max(), start);
    }
    
    // Similar to Dijkstra's algorithm
    while (!costs_to.empty()) {
        auto [cost, from] = costs_to.top(); // front
        costs_to.pop();
        for (const auto& [to, edge_cost] : graph.edges[from]) {
            Cost new_cost = add_costs(cost, graph.vertices[from], edge_cost);

            // if new_cost is not better than old cost then skip (Decided by compare)
            if (!compare(new_cost, this->optimum_path_step[to].first)) {
                continue;
            }
            this->optimum_path_step[to] = {new_cost, from};
            costs_to.push({new_cost, to});  // update the pq with new minimal cost
        }
    }
}

template <typename Value, numeric Cost, class Compare>
std::vector<int> optimum_path_querier<Value, Cost, Compare>::get_optimum_path(
        const int& end) {

    if (this->optimum_path_step[end].second == -1) {
        return {};
    }
    std::vector<int> path;
    int current = end;
    for (; this->optimum_path_step[current].second != current; 
            current = this->optimum_path_step[current].second) {
        path.push_back(current);
    }
    path.push_back(current);
    std::reverse(path.begin(), path.end());
    return path;
}