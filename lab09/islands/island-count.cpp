#include "dfs.h"
// here T1 is a matrix (2D vector of int) and T2 is a matrix (2D vector of bool)

// validate
// check the indices and additional conditions after which you would use dfs
template <typename T1, typename T2> bool DFS::validate(T1& M, int i, int j, T2& v) {
    int r = M.size();
    int c = M[0].size();

    return ((i>=0)&&(i<r)&&(j>=0)&&(j<c)&&(M[i][j]==1)&&(!v[i][j]));
}

// this function need not be used for island count problem
template <typename T1, typename T2> bool DFS::terminate(T1& M, int i, int j, T2& v) {
    return false;
}

// dfs
// modify the data structure (matrix M and/or v) as needed
// you can solve this without modifying M
// use the row and col vectors to access neighbors of (i,j)
// validate the neighbour before you use dfs
template <typename T1, typename T2> void DFS::dfs(T1& M, int i, int j, T2& v) {
    
    v[i][j] = true;

    /// recurr for all connected neighbours
    for(int k=0; k<row.size(); k++ ){
        int newi = i+row[k];
        int newj = j+col[k];
        if(validate(M,newi, newj,v)){
            dfs(M, newi, newj, v);
        }
    }
}
