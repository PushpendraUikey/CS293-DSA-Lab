#include <iostream>
#include <map>
#include <vector>
#include "rdtsc.h"
using namespace std;

// Let's consider vectors again. When a vector is declared without specifying
// a size, it starts empty. However, there needs to be some initial allocation
// of space in anticipation of new elements being added. As we begin filling
// the vector, there will come a point when the allocated memory runs out.
// At this stage, the vector needs to allocate more memory. Your task is to
// write code that detects at what size the new allocation occurs and determine
// the amount of extra memory being allocated.

// Hint: Keep in mind that when a vector requires more memory, it not only
//   needs additional space but also needs to be relocated to ensure continuous
//   storage of the vector. This relocation process takes some time to execute.



int main() {
  // if output file would be empty, gnuplot would complain
  // So we need to dump some dummy data
  std::cout << "0 0\n";
  std::cout << "1 1\n";

  vector<int> v;

  int cap = 0;
  for(int i=0; i<=32; i++){
    v.push_back(i);
    int c = v.capacity();
    if(c != cap){
      cout <<v.size() <<' ' << c - cap <<  endl; 
      cap = c;
    }
    
  }

  return 0;
}
