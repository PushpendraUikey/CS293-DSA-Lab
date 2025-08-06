#include "graph.h" // needed

// you may or may not use this dfs function
// but the end result has to be stored in stack Graph::S
void Graph::dfs(int s) {
    nodes[s]->visited = true;

    for(auto& e:nodes[s]->adj){ // go through adj list
        if(!nodes[e.first]->visited){
            dfs(e.first);
        }
    }
    S.push(s);
}

// this function is to be implemented
void Graph::topoSort() {
    for(auto& e:nodes){
        if(!e.second->visited){ /// if not visited then call dfs
            dfs(e.first);
        }
    }
    resetVisit();   //// works is done so reset visited 
}
