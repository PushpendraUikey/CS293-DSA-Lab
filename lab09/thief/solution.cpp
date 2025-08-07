#include <bits/stdc++.h>
using namespace std;

int findNextNode(vector<vector<int>>& adj, int s, int e){

    unordered_map<int, bool> visited;
    unordered_map<int, int> parent;
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while(!q.empty()){
        int frontN = q.front();
        q.pop();

        for(auto& i:adj[frontN]){
            if(!visited[i]){
                q.push(i);
                parent[i] = frontN;
                visited[i] = true;
            }
        }
    }

    int currNode = e;
    int req=-1;
    while(currNode != s){
        req = currNode;
        currNode = parent[currNode];
    }

    return req;
}
int posHazard(vector<vector<int>>& adj, int pos, int notpos){   //// when hazard comes
    for(auto &neigh : adj[pos]){
        if(neigh != notpos){
            return neigh;
        }
    }
    return pos;
}

int solve(vector<vector<int>>& graph) {

    unordered_map<int, int > visitedth; /// thief's path visited count to a node
    unordered_map<int, int> visitedpo; //// police's visited count to a node

    map<pair<int, int>, int> stateHistory; // Track (thiefpos, policepos)
    int thiefpo = 1;
    int policepo = 2;

    bool thief = true;  //// thief's turn

    //// parent node for every node for shortest path  

    while(true){

        if(stateHistory[{thiefpo, policepo}]>1) return 0; // Cycle detected, return draw
        stateHistory[{thiefpo, policepo}]++;


        if(thief){
            int nextpos = findNextNode(graph,thiefpo, 0);

            if(visitedpo[nextpos]>1) return 0; /// draw
            visitedpo[nextpos]++;

            if(nextpos == 0) return 1;

            // if(nextpos == policepo){  //// in case thief enter's the police's position by mistake
            //     nextpos = posHazard(graph, thiefpo, nextpos);
            // }
            thief = false;     /// reversing the turn
            
            thiefpo = nextpos; /// update the thief's position
            if(thiefpo == policepo) return 2; //// by mistake/forcefully thief entered the police's node police won 
        }else{
            int nextpos = findNextNode(graph, policepo, thiefpo);
            if(visitedth[nextpos]>1) return 0;  //// if we are repeating cycle
            visitedth[nextpos]++;
            if(nextpos == thiefpo) return 2;        /// police won, thief caught

            if(nextpos == 0){
                nextpos = posHazard(graph, policepo, nextpos);  // mistakenly entered 0;
                if(nextpos==0) return 0;
            }

            if(nextpos == thiefpo) return 2;

            thief = true; /// updating the turn
            policepo = nextpos;
        }
    }
    
    // Return the game outcome
    return -1;
}

// ChatGpt'd solution considering the Game Theoretic Analysis and DP optimization
int solve(vector<vector<int>>& graph) {
    const int THIEF_TURN = 0;
    const int OFFICER_TURN = 1;
    int n = graph.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0))); // 0=draw, 1=thief win, 2=officer win
    queue<tuple<int, int, int>> q;

    // Base cases
    for (int i = 0; i < n; i++) {
        for (int t = 0; t < 2; t++) {
            if (i != 0) {
                dp[0][i][t] = 1; // Thief at 0 wins
                q.emplace(0, i, t);
            }
            dp[i][i][t] = 2; // Officer catches thief
            q.emplace(i, i, t);
        }
    }

    // Degree count for moves
    vector<vector<vector<int>>> degree(n, vector<vector<int>>(n, vector<int>(2, 0)));
    for (int t = 0; t < n; t++) {
        for (int o = 0; o < n; o++) {
            degree[t][o][THIEF_TURN] = graph[t].size();
            degree[t][o][OFFICER_TURN] = count_if(graph[o].begin(), graph[o].end(), [](int x){ return x != 0; });
        }
    }

    // Process known results (BFS)
    while (!q.empty()) {
        auto [t_pos, o_pos, turn] = q.front();
        q.pop();
        int result = dp[t_pos][o_pos][turn];

        // Get all previous states that could have led to this state
        vector<pair<int, int>> prevs;
        if (turn == THIEF_TURN) {
            for (int prev_o : graph[o_pos]) {
                if (prev_o == 0) continue; // Officer can't go to 0
                prevs.emplace_back(t_pos, prev_o);
            }
        } else {
            for (int prev_t : graph[t_pos]) {
                prevs.emplace_back(prev_t, o_pos);
            }
        }

        for (auto [pt, po] : prevs) {
            if (dp[pt][po][1 - turn] != 0) continue;

            bool can_win = (result == (turn == THIEF_TURN ? 2 : 1));

            if (can_win) {
                dp[pt][po][1 - turn] = result;
                q.emplace(pt, po, 1 - turn);
            } else {
                degree[pt][po][1 - turn]--;
                if (degree[pt][po][1 - turn] == 0) {
                    dp[pt][po][1 - turn] = (turn == THIEF_TURN ? 1 : 2); // Opponent wins
                    q.emplace(pt, po, 1 - turn);
                }
            }
        }
    }

    return dp[1][2][THIEF_TURN]; // Starting state
}


    // graph given is already in the form of adjacency list
    // so just need a map for visited nodes
    // unordered_map<int, bool> visited;

// if(visitedth[nextpos]>3) return 0;  //// if we are repeating cycle
            // visitedth[nextpos]++;

// if(visitedpo[nextpos]>3) return 0; /// draw
            // visitedpo[nextpos]++;