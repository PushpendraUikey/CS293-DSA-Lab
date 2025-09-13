#include "graph.h"

// Implement this function to check if there is a cycle present in the graph



/// @brief DFS algorithm to detect a cycle in the graph
/// @param e   current node 
/// @param p   Parent node of curr
/// @param visited  map to keep track of already visited node
/// @param gp   graph data structure, to access adjacency list of all nodes
/// @return     tells whether graph contains cycle or not

bool isCyclicDFS(int e, int p, std::map<int, bool>&visited, 
    std::map<int, GraphNode*>& gp){

    visited[e] = true;  /// mark vist true;

        for(auto &ele : gp[e]->adj){   /// looping over adjacency list
            
            if(!visited[ele]){
                bool cyclic = isCyclicDFS(ele, e, visited, gp );
                if(cyclic) return true;
            }
            else if( ele != p){ /// if visited but not parent
                return true;
            }

        }

    return false;

}


// You're not bypassing encapsulation—you're just using a member function (isCyclePresent()) to 
// pass private data (nodes) to another function. 
// This works because member functions already have access to private members.
bool Graph::isCyclePresent(){

    std::map<int, bool> visited;

    for(auto& ele : nodes){
        if(!visited[ele.first]){
            bool cyclic = isCyclicDFS(ele.first,-1,visited, nodes);
            if(cyclic) return true;
        }
    }
    return false;
}