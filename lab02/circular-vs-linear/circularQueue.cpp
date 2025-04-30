#include <stdlib.h>
#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
  if(head == tail) return true;
  return false;
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  if((tail+1)%N==head) return true;
  return false;
}

template <typename T> void DynamicQueue<T> :: grow() {
  unsigned int newsize = nextSize();
  T* newA = new T[newsize];

    for(int i=head; i != tail ; i = (i+1)%N){
      newA[i] = A[i];
    }
    // head = 0;
    // tail = N;
    N = newsize;

    delete[] A;

    A = newA;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
  return (tail-head+N)%N;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
  if(isFull()){
    grow();
  }
  A[tail] = x;
  tail = (tail+1)%N;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T* x) {
  if(isEmpty()){
    return false;
  }
  *x = A[head];
  head = (head+1)%N;

  return true; // dummy return
}
