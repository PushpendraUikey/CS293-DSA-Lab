#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <vector>
#include <iterator>
#include "rdtsc.h"

typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef unsigned long long ticks;

using namespace std;


// In this exercise, we will compare the performance of arrays and vectors.

// The key difference between arrays and vectors is that the size of an
// array is not flexible, while the size of a vector can be adjusted. For
// example, using vector.push_back(a) can extend the length of the vector
// by 1. However, this flexibility comes with an overhead cost for automatic
// size maintenance. Our objective is to measure this cost by calculating the
// average access time to the container.

// We will use the following simple test program:

//  1. Declare the container.
//  2. Assign container[i] = i for i ranging from 0 to N.
//  3. Find the maximum value stored in the container and return the value.

// The above program will have 2N accesses to the container
// (N writes and N reads). So average access time = runtime/(2N)

// If the container is an array, the size needs to be declared in advance.
// In the case of vectors, we will use push_back to insert elements and
// simulate the flexible size of vectors.

// For arrays, write the following two versions of the test:
//  1. Locally declared array.
//  2. Globally declared array.

// For vectors, write the following four versions of the test:
//  1. Local vector.
//  2. Local vector with reserve ( refer to the C++ manual for the
//                                 reserve function).
//  3. Local vector with access to the vector using an iterator.
//     For example, for(int v : vector).
//  4. Global vector.

// Run your experiments for N = 2 2*64 2*64*64 2*64*64*64 2*64*64*64*64
// and compute average runtime

// For measuring time use "rdtsc.h"
// It has class, ClockCounter, which measure time by counting clock of CPU.

// Run your code for various compiplation levels -O0,-O1,-O2,-O3

//----------------------------------------------------------------------------

int test_local(size_t N) {
  vector<int> bigarray;
  for(unsigned int k = 0; k<N; ++k)
    bigarray.push_back(k);
  int sum = 0;
  for(unsigned int k = 0; k<N; ++k)
    { if( bigarray[k] > sum ) sum = bigarray[k]; }
  return sum;
}

//==================================

int test_local_reserve( size_t N ) {
  vector<int> bigarray;
  bigarray.reserve(N);  //reserve does not change the vector's size but only its capacity.
                        //you reserve space without storing elements so as to avoid rellocation
  for(unsigned int k = 0; k<N; ++k)
    bigarray.push_back(k);
  int sum = 0;
  for(unsigned int k = 0; k<N; ++k)
    { if( bigarray[k] > sum ) sum = bigarray[k]; }
  return sum;
}

//==================================

int test_local_iter(size_t N) {
  vector<int> bigarray;
  for(unsigned int k = 0; k<N; ++k)
    bigarray.push_back(k);
  int sum = 0;
  // for( int i : bigarray )
  //   { if( i > sum ) sum = i; }
  for( auto it = bigarray.begin(); it != bigarray.end(); ++it )
    { if( *it > sum ) sum = *it; }
  return sum;
}

//==================================
vector<int> bigarray;

int test_static(size_t N) {
  static vector<int> bigarray;
  bigarray.clear();// Once declared you can't redclare any static vector hence, clear it's space to reuse it.
  for(unsigned int k = 0; k<N; ++k)
    bigarray.push_back(k);
  int sum = 0;
  for(unsigned int k = 0; k<N; ++k)
    { if( bigarray[k] > sum ) sum = bigarray[k]; }
  return sum;
}



//==================================

int test_array(size_t N) {
  int* bigarray = (int*) malloc( sizeof(int)*N ); // dynamic allocation of memory in heap
  for(unsigned int k = 0; k<N; ++k)
    bigarray[k] = k;
  int sum = 0;
  for(unsigned int k = 0; k<N; ++k)
    { if( bigarray[k] > sum ) sum = bigarray[k]; }
  free( bigarray );   // frees the memory allocated dynamically
  return sum;
}

//==================================

int test_array_pre_allocated( int* bigarray, size_t N) {
  for(unsigned int k = 0; k<N; ++k)
    bigarray[k] = k;
  int sum = 0;
  for(unsigned int k = 0; k<N; ++k)
    { if( bigarray[k] > sum ) sum = bigarray[k]; }
  return sum;
}

//----------------------------------------------------------------------------

// "ignore this:" is merely a label for clarity and doesn't affect the code logic; 
//  it’s there for the developer's or user's understanding.
//Each "\" at the end of a line tells the preprocessor to continue reading the next 
//line as part of the same macro definition.
#define print_sum( time, idx1, idx2, sum, NM ) {        \
       cerr<< "ignore this:"<< sum << "\r";             \
       results[idx1][idx2] = (time.stop()*1.0/(NM) );   \
   }

#define SCALE_LIMIT 5
double results[SCALE_LIMIT][6];

void print_results( const char * msg, unsigned methodIdx ) {
  cerr << msg << ":";
  for( unsigned i = 0; i < SCALE_LIMIT; i++ ) {
    cerr << results[i][methodIdx] << "\t:";
  }
  cerr << endl;
}

//----------------------------------------------------------------------------
//20+5 = 25 1+6+6+6+6

int main() {
  ClockCounter time;
  const size_t NM = 2 * 1024 * 1024;
 cerr.precision(3);
 size_t N = 2;//00 * 1000;

 cerr << "----------------      C++ TEST       -------------------:\n";
 cerr << "----------------:-------:-------:-------:-------:-------:\n";
 cerr << "container length";
 for( unsigned i=0; i+1< SCALE_LIMIT; i++ ) {
   cerr << ":"<< N << "\t"; N = N*64;
 }
 cerr << ":"<< N << endl;

 N = 2;
 for( unsigned idx = 0; idx < SCALE_LIMIT; idx++ ) {
    const size_t M = NM/N;
    int sum = 0;

    // local array - on stack
    time.start();
    sum = 0;
    for(unsigned int k = 0; k<M; ++k) { sum += test_local(N); }
    print_sum( time, idx, 0, sum, NM ); cerr << "=" << flush;

    // global array - on heap
    time.start(); sum = 0;
    int* bigarray = (int*) malloc( sizeof(int)*N );
    for(unsigned int k = 0; k<M; ++k) {
      sum += test_array_pre_allocated( bigarray, N );
    }
    free( bigarray );
    print_sum( time, idx, 5, sum, NM ); cerr  << "======" << flush;

    time.start(); sum = 0;
    for(unsigned int k = 0; k<M; ++k) { sum += test_local_reserve(N); }
    print_sum( time, idx, 1, sum, NM ); cerr  << "==" << flush;

    time.start(); sum = 0;
    for(unsigned int k = 0; k<M; ++k) { sum += test_static(N); }
    print_sum( time, idx, 2, sum, NM ); cerr  << "===" << flush;

    time.start(); sum = 0;
    for(unsigned int k = 0; k<M; ++k) { sum += test_local_iter(N); }
    print_sum( time, idx, 3, sum, NM ); cerr  << "====" << flush;


    time.start(); sum = 0;
    for(unsigned int k = 0; k<M; ++k) { sum += test_array(N); }
    print_sum( time, idx, 4, sum, NM ); cerr  << "======" << flush;

    N = N*64;
  }
  cerr << "\r"; //Overwriting Debug Output: Since the \r character brings the cursor back to the start of 
  // the line, it continuously overwrites the output on the same line instead of adding new lines.
  cerr << "----------------:-------:-------:-------:-------:-------:\n";
  print_results( "local array\t", 4 );
  print_results( "global array\t", 5 );
  print_results( "local vector\t", 0 );
  print_results( "lo. vec. reserve", 1 );
  print_results( "global vector\t", 2 );
  print_results( "lo. vec. iter\t", 3 );
  cerr << "----------------:-------:-------:-------:-------:-------:\n";

  return 0;
}

/*
the `flush` manipulator forces the output buffer to be written to the output stream immediately.
In this case, `cerr` (standard error) is being flushed.

### Why `flush` is Used Here
Normally, output streams like `cout` and `cerr` are buffered to improve performance. Instead of 
sending each character directly to the output, they accumulate in a buffer and are sent all at 
once, which is faster for larger outputs. The `flush` command forces this buffer to be cleared 
immediately, ensuring that any pending output is written right away.

### Purpose of `flush` in This Code
Using `flush` here ensures that `"======"` is displayed immediately after the `print_sum` macro 
executes. This is often done in debugging and logging to make sure that all previous outputs are 
visible on the console at that exact point in the program's execution, rather than waiting for the 
buffer to fill or the program to reach the next newline or end of output.

In this context, `flush` provides real-time feedback about the program's progress by:
1. Ensuring any debug or timing information in `cerr` is output right away.
2. Making sure that `"======"` appears immediately after the `print_sum` output to clearly 
indicate the end of the section or test case, which can aid readability in logs.
*/