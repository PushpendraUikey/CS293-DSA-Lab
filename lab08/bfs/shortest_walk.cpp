#include "graph.cpp"


// we need shortest path between two consecutive stations each time we move to the next station

void bfs_w(int src,int dest,unordered_map<int, vector<int>>&adj, 
        unordered_map<int, int>&parent){
    
    unordered_map<int, bool> visited;
    queue<int> q;
    q.push(src);
    visited[src] = true;
    parent[src] = -1;

    while(!q.empty()){
        int frontN = q.front();
        q.pop();
        if(frontN==dest) break; // shortest path in an undirected unweighted graph comes from bfs
        for(auto& e : adj[frontN]){
            if(!visited[e]){
                q.push(e);
                visited[e] = true;
                parent[e] = frontN;
            }
        }
    }    
}

void pathConstruct(int dest, vector<int>& path, unordered_map<int,int>&parent){
    vector<int> temp;
    for(int i=dest; i!=-1; i=parent[i]){
        temp.push_back(i);
    }
    // reverse(temp.begin(), temp.end());
    for(int i=temp.size()-1;i>=0; i--){
        path.push_back(temp[i]);
    }
    // path.insert(path.end(), temp.begin(),temp.end());
}

void shortest_walk(Graph g,vector<int>&stations, vector<int>& path)
{
    int start = 0;
    unordered_map<int, vector<int>> adj;

    for(auto& ele: g.edges){
        adj[ele.first].push_back(ele.second);   // undirected graph
        adj[ele.second].push_back(ele.first);
    }
    
    if(stations.size()<2){
        path.push_back(stations[0]);
        return;
    }

    for(int i=0; i<stations.size()-1; i++){
        unordered_map<int, int> parent;

        bfs_w(stations[i],stations[i+1], adj, parent);

        pathConstruct(stations[i+1],path,parent);

        if(i<stations.size()-2){    // to remove repeated nodes 
            path.pop_back();
        }
    }
}
    // for(int i=1; i<stations.size(); i++){
    //     bfs_walk(adj, stations[i-1], stations[i], path);
    //     if(i<stations.size()-1) path.pop_back();    /// remove dest as it is going to be add in next cycle
    // }
