#include <iostream>
#include <set>
#include <map>
#include <vector>
#include "rdtsc.h"

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


# define REPEAT 1000
# define VSIZE_MIN   2
# define VSIZE_RANGE 70

int main() {
  std::map<int,float> m;  // to store times

  // for( unsigned size = VSIZE_MIN; size < VSIZE_RANGE; size++ ) {
  //     m[size] = 0.0;
  // }

  ClockCounter time;      // it measures the time.
  // Sample 100 times to reduce system noise;
  for( unsigned l = 1; l < 100; l++ ) {

    // SIZE RANGE
    for( unsigned size = VSIZE_MIN; size < VSIZE_RANGE; size++ ) {
      time.start();

      // how much time will it take to fill the vector and know that large size would mean
      // it will take more time to relocate.
      for( unsigned r = 0; r < REPEAT; r++ ) {
        std::vector<int> s;
        for(int i=size; i>=1; i--)
          s.push_back(i);
      }

      // Save runtime
      m[size] += (time.stop()*1.0)/(REPEAT*size);   // average time of insertion an element to a vector
      // if size is removed(i.e. only REPEAT is there) then it will show average relocation time
    }
  }
  for( auto pr : m ) {
    std::cout << pr.first << " " << pr.second/100 << "\n";
  }
  return 0;

}
/* It is intuitively obvious that smaller sizes have frequent relocation as compared to larger size
thus if performance for relocation alone is tested then it will have upward trend in the graph. */