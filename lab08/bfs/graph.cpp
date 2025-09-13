#include<unordered_map>
#include<vector>
#include<iostream>
#include<utility>
#include<queue>
using namespace std;

// Implement a node struct if you feel 


// Implement the graph class
class Graph
{
    public:
    int vertices;
    vector<pair<int,int>> edges;
public:
    Graph(int no_of_vertices,const vector<pair<int,int>>&_edges):vertices(no_of_vertices),
        edges(_edges){
    };
};


void bfs(Graph& g, int source, unordered_map<int, int>& parent)
{
    unordered_map<int, bool> visited;
    unordered_map<int, vector<int>> adj;

    for(auto& ele: g.edges){
        adj[ele.first].push_back(ele.second);   /// undirected graph
        adj[ele.second].push_back(ele.first);
    }
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while(!q.empty()){
        int frontN = q.front();
        q.pop();

        for(auto& e:adj[frontN]){
            
            if(!visited[e]){
                visited[e] = true;
                q.push(e);
                // if(parent.find(e) == parent.end()){ 
                parent[e] = frontN;
                // }
            }  
        }
    }
};

