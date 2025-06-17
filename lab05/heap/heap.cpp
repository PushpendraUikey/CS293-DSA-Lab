#include <iostream>

/*
In this exercise, we will implement heap as discussed in the class.
We need to implement the following functions.


ONLY THIS FILE MUST BE MODIFIED FOR SUBMISSION

You may edit main.cpp for writing more test cases.
But your code must continue to work with the original main.cpp


THERE IS ONLY ONE TEST CASE ONLY FOR YOUR UNDERSTANDING.

-- You may need to generate more random tests to get your tests right
-- Print will not work until you have a good printing function
*/


#include "heap.h"

// The implementation of Heap data structure here is 0-based indexing.

int Heap::parent(int i) {
  int p;
  if(i&1) p = i/2;
  else p = i/2 - 1;

  if(p >= 0) return p;
  return -1;
}

int Heap::left(int i) {
  unsigned l = 2 * i + 1;
  if(l <= sz) return l;
  return -1;
}

int Heap::right(int i) {
  unsigned r = 2 * i + 2;
  if(r <= sz) return r;
  return -1; 
}

int Heap::max() {
  if(sz>0) return store[0];
  return -1; 
}

void Heap::swap(int& i, int& j) {
  swap_count++;
  int temp = i;
  i = j;
  j = temp;
}

void Heap::insert(int v) {
    if(sz <= store.size()) store[sz] = v;
    else store.push_back(v);

    sz = sz + 1;
    int index = sz;

    while(index>0){
      int p = parent(index);

      if(p >= 0 && store[p] > store[index]){
        swap(store[p], store[index]);
        index = p;
      }else return;
    }
}

void Heap::heapify(int i) {
  unsigned t = i;
  unsigned large = i;
  unsigned left = 2*i+1;
  unsigned right = 2*i+2;

  if(left < sz && store[left] > store[large]){
    large = left;
  }
  if(right < sz && store[right] > store[large]){
    large = right;
  }

  if(t != large){
    swap(store[t], store[large]);
    heapify(large);
  }
}


void Heap::deleteMax() {
  if(sz==0) return;
  swap(store[0], store[sz-1]);
  sz--;
  heapify(0);
}

void Heap::buildHeap() {
  for(unsigned i=0; i < sz; i++){
    heapify(i);
  }
}

void Heap::heapSort() {
  unsigned size = sz;
  unsigned l = sz;
  buildHeap();

  while(l-->0){
    deleteMax();
  }
  sz = size;
}


