#include <cstdlib>
#include <cstddef>
#include "stack.h"
#pragma once

/*
 * You must NOT add ANY other includes than what is already here.
 * The purpose of this file is to implement the functioning of a queue in C++.
 * The task is to implement a Queue using stacks. This requires two stacks.
 * Ensure that ALL of them are on average constant time. Amortized O(1) is OK.
 * You must NOT change the data members or ANY of the method signatures.
 * NOR are you allowed to add any additional methods or data members.
 * You are free to use the PUBLIC methods of the Stack class here.
 */

template <typename T>
class Queue {
    class Stack<T> first_stack;
    class Stack<T> second_stack;
    // bool swit;        We don't need this var
public:
    Queue(){
        // swit = true;
    }
    ~Queue(){}
    void enqueue(T value){
        // if(!swit){
        //     while(!second_stack.isEmpty()){
        //         first_stack.push(second_stack.pop());
        //     }
        //     swit = true;
        // }
        first_stack.push(value);
    }
    T dequeue(){
        // if(swit){
        //     while(!first_stack.isEmpty()){
        //         second_stack.push(first_stack.pop());
        //     }
        //     swit = false;
        //     return second_stack.pop();
        // }else{
        //     return second_stack.pop();
        // }
        if(first_stack.isEmpty() && second_stack.isEmpty()) throw std::invalid_argument("Empty Queue Dequeue Error");

        if(second_stack.isEmpty()){
            while(!first_stack.isEmpty()){
                second_stack.push(first_stack.pop());
            }
        }

        return second_stack.pop();
    }
    T peek(){
        // if(!swit){
        //     while(!second_stack.isEmpty()){
        //         first_stack.push(second_stack.pop());
        //     }
        //     swit = true;
        // }
        // return first_stack.peek();       /// This was the wrong implementation
        
        if(first_stack.isEmpty() && second_stack.isEmpty()) throw std::invalid_argument("Empty Queue Dequeue Error");

        if(second_stack.isEmpty()){
            while (!first_stack.isEmpty())
            {
                second_stack.push(first_stack.pop());
            }
            
        }
        return second_stack.peek();
    }
    bool isEmpty(){
        return first_stack.isEmpty() && second_stack.isEmpty();
    }
    size_t getSize(){
        return first_stack.getSize() + second_stack.getSize();
        // if(swit){
        //     ;
        // }else{
        //     return ;
        // }
    }
};

// ENTER YOUR IMPLEMENTATIONS OF METHODS BELOW

