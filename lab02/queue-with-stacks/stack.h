#include <cstdlib>
#include <cstddef>
#pragma once    // alternative to #ifndef/#define/#endif trick

/*
 * You must NOT add ANY other includes than this.
 * The purpose of this file is to implement the functioning of a stack in C++.
 * Implement all the method functions in this file, your way.
 * Ensure that ALL of them are on average constant time. Amortized O(1) is OK.
 * You must NOT change the method signature of any of the methods.
 * You may add any additional methods or data members as you need.
 * Those methods and data members should be protected.
 */

template <typename T>
class Stack {
    // ADD ANY ADDITIONAL DATA MEMBERS OR METHODS HERE
    T* arr ;
    int size;
    int top;

    void resize(){
        int newsize = size + 10;
        T* newA = new T[newsize];

        for(int i=0; i<size; i++){
            newA[i] = arr[i];
        }
        
        size = newsize;
        delete [] arr;

        arr = newA;
    }

    // DO NOT CHANGE THE METHOD SIGNATURES BELOW
public:
    Stack(){
        size = 10;
        top = -1;
        arr = new T[size];
    }
    ~Stack(){
        if(arr != NULL){
            delete[] arr;
            arr = nullptr;
        }
    }
    void push(T value){
        if(top==size-1){
            resize();
        }
        arr[++top] = value;
    }
    T pop(){
        if(top==-1) return -1;
        T val = arr[top--];
        return val;
    }
    T peek(){
        if(top==-1) return -1;
        return arr[top];
    }
    bool isEmpty(){
        if(top==-1) return true;
        return false;
    }
    size_t getSize(){
        return top+1;
    }
};

// ENTER YOUR IMPLEMENTATIONS OF METHODS BELOW

