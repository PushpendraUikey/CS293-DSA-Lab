#include "graph.cpp"

void path_(vector<int>& path,unordered_map<int, int> &parent, int source, int destination);
void shortest_walk(Graph& g,vector<int>&stations, vector<int>& path)
{
    path.push_back(stations[0]);
    for (int i=0;i<stations.size()-1;i++){
      unordered_map<int, int> parent;
      parent.clear();
      g.clear_visited();
      bfs(g,stations[i],parent);
     
      vector<int> temp;
      path_(temp,parent,stations[i],stations[i+1]);
      path.insert(path.end(),temp.begin(),temp.end());
    }
    return;
}

void path_(vector<int>& path,unordered_map<int, int> &parent, int source, int destination)
{

  vector<int> temp;
  int i=destination;
  while(i!=source){
   
    temp.push_back(i);
    i=parent[i];
  }
  for (size_t i = 0; i < temp.size(); i++)
  {
    path.push_back(temp[temp.size()-i-1]);
  }
  return;
}

// Below here is the optimized implementation of the shortest_walk as to avoid 
// the bfs call if the "ancestor" relation between consecutive stations holds.

// void shortest_walk(Graph g, vector<int>& stations, vector<int>& path) {
//   if(stations.empty())
//       return;
  
//   // Start at the first station.
//   int currStation = stations[0];
//   path.push_back(currStation);
  
//   // Compute initial BFS tree with currStation as source.
//   unordered_map<int, int> parent;
//   g.clear_visited();
//   bfs(g, currStation, parent);

//   // Process each consecutive station.
//   for (int i = 1; i < stations.size(); i++) {
//       int target = stations[i];
      
//       // Check if currStation is an ancestor of target in the current BFS tree.
//       bool canReuse = false;
//       int temp = target;
//       // Follow parent chain until we hit currStation or run out.  [checking for the ancestor relation]
//       while (parent.find(temp) != parent.end() && temp != currStation) {
//           temp = parent[temp];
//       }
//       if (temp == currStation)
//           canReuse = true;
      
//       // If not, we need to recompute BFS from the current station.
//       if (!canReuse) {
//           parent.clear();
//           g.clear_visited();
//           bfs(g, currStation, parent);
//       }
      
//       // Reconstruct path from currStation to target using the parent mapping.
//       vector<int> subpath;
//       int cur = target;
//       while (cur != currStation) {
//           subpath.push_back(cur);
//           cur = parent[cur];
//       }
      
//       // Append subpath (excluding currStation, which is already in path).
//       for (int i=subpath.size()-1; i>=0; i--){
//           path.push_back(subpath[i]);
//       }
      
//       // Update current station to target for the next iteration.
//       currStation = target;
//   }
// }
