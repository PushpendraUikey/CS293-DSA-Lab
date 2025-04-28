#include <iostream>

// Consider the binary search algorithm presented in class. We are interested
// in determining the average execution time of the binary search. To
// accomplish this, let's conduct an experiment.

// Suppose we have an array of size 1024, which contains distinct elements
// arranged in non-increasing order. We have already analyzed the running
// time when the element being searched for is not present in the array.
// Now, let's assume that we are only searching for elements that we know
// exist in the array.

// Our goal is to experimentally calculate the average number of
// iterations required to search for all 1024 elements in the array.

// In the following,
//   -- Implement BinarySearch that can handle non-increasing array
//   -- Harness BinarySearch such that we can compute avarage number
//      of iterations


int BinarySearch ( int * S , int n , int e ) {
  int iteration_count = 0;
  // Implement binary search here
  // instead of returning position return the number
  // of executed iterations of binary search.
  int s = 0; 
  int m = s + (n-s)/2;

  while(s <= n){
    iteration_count++;
    if(S[m] == e) break;
    else if(S[m] > e){
      s = m+1;
    }else{
      n = m-1;
    }
    m = s + (n-s)/2;
  }
  return iteration_count;
}

int main() {
  unsigned size = 1024;
  int S[size];
  float average = 0;
  int i, v;
  // Initialize array S with distinct elements
  for(i=0; i<1024; i++){
    S[i] = 500000 - i*3 + 1;
  }

  // search 1024 element stored in S and compute

  for(i=0 ;i < 1024; i++){
    v = 500000 - i*3 + 1;

    average += BinarySearch(S, 1024, v);
  }

  average = average/1024;
  
  // the average number of iterations in binary search
  
  std::cout << "Average: " << average << "\n";
  return 0;
}
