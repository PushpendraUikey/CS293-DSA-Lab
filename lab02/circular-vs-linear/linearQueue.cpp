#include <stdlib.h>
#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty(){
    if(tail==head) return true;
    return false;  
  }

template <typename T> bool DynamicQueue<T> :: isFull(){
    if(tail-head == N) return true;
    return false;
   }

template <typename T> void DynamicQueue<T> :: grow() {
    unsigned int newsize = nextSize();
    T* newA = new T[newsize];

    for(int i=0; i<tail; i++){
      newA[i] = A[(head+i)%N];
    }
    tail = tail-head;
    head = 0;
    N = newsize;

    delete[] A;

    A = newA;
  }

template <typename T> unsigned int DynamicQueue<T> :: size(){
    return tail-head;
  }

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
    if(isFull()) {
      grow();
    }else if(tail==N){
      for(int i=0; i<tail-head; i++){
        A[i] = A[(head+i)%N];
      }
      tail = tail-head;
      head = 0;
    }
    A[tail++] = x;
  }

template <typename T> bool DynamicQueue<T> :: QDelete(T* x){
    if(isEmpty()) return false;
    *x = A[head++];
    return true;
  }
