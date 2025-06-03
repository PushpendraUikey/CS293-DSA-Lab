#include <bits/stdc++.h>

using namespace std;

// The main function that returns
// the minimum cost to connect n
// ropes of lengths stored in len[0..n-1]
int minCost(int len[], int n)
{
	int cost = 0; // Initialize result

        // Write your code here
		priority_queue<int, vector<int>, greater<int>> pq;

		for(int i=0; i<n; i++){ pq.push( len[i] ) ; }

		while(pq.size()>1){
			int a = pq.top();
			pq.pop();
			int b = pq.top();
			pq.pop();

			cost += (a+b);
			pq.push(a+b);
		}

	return cost;
}


