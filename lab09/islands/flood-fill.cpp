#include "dfs.h"
// here T1 is a matrix (2D vector of char) and T2 is a char

// validate
// check the indices and additional conditions after which you would use dfs
template <typename T1, typename T2> bool DFS::validate(T1& M, int i, int j, T2& v) {
    int r = M.size();
    int c = M[0].size();

    return ((i>=0)&&(i<r)&&(j>=0)&&(j<c)&&(M[i][j]==v));
}

// terminate
// this is for premature termination of a dfs run depending on some condition
template <typename T1, typename T2> bool DFS::terminate(T1& M, int i, int j, T2& v) {
    return (M[i][j]==v);
}

// dfs
// modify the data structure (matrix M) as needed
// check for terminate if required
// use the row and col vectors to access neighbors of (i,j)
// validate the neighbour before you use dfs
// you may need to use one extra variable for temporarily storing a value
template <typename T1, typename T2> void DFS::dfs(T1& M, int i, int j, T2& v) {
    if(terminate(M,i,j,v)) return;  //// if the char to replace with is same then
        //// then it can be trapped into infinite loop
    
    char ch = M[i][j];

    M[i][j] = v;    //// update with replacement.

    for(int k=0; k<row.size(); k++){
        int newx = i + row[k];
        int newy = j + col[k];

        if(validate(M, newx, newy, ch)){
            dfs(M, newx, newy, v);
        }
    }
}
