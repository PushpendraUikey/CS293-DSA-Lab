/*
    In this problem, you will implement a Deque class that will be inherited by a Queue and a Stack class.
    The Deque class will have the following functions:

    1. Constructors: Take arguments like the capacity of the deque, scaling factor etc.
    2. Destructor: Deallocate the dynamic array that stores the deque.

    3. push_back: Push data to the back of the deque.
    4. pop_front: Remove and return the front element of the deque.
    5. push_front: Push data to the front of the deque.
    6. pop_back: Remove and return the back element of the deque.
    7. peek_front: Return the front element of the deque without removing it.
    8. peek_back: Return the back element of the deque without removing it.

    9. get_capacity: Return the capacity of the deque.
    10. get_size: Return the size of the deque.
    11. is_empty: Return true if the deque is empty, and false otherwise.

    NOTE: The Deque class should be able to resize itself when it is full and auto_resize is true. The capacity
    of the deque should be scaled by the resize factor. 

    -> Rescaling should only happen when the deque is full and auto_resize is true. If the existing array is not full,
    but the back of the array is the end of the array, then you need to work in a circular manner and keep track of the 
    start and end of the array. 

    You need to implement the Deque, Queue, and Stack classes as described above. 
    Overload << operator so that cout works. You need to implement the overloaded << operator for the Queue
    class. You need to implement the overloaded << operator for the Stack class. You need to implement the copy
    constructor for the Queue class. You need to implement the copy constructor for the Stack class. You need to
    make the necessary member functions of the Deque class public in the Queue and Stack classes.

    Read about class inheritance and friend functions. Understand copy constructors and how to use them before you 
    attempt this problem.

    Run your code:
    g++ deque_inheritance.cpp -o deque_inheritance
    ./deque_inheritance
    
    Use command line inputs from the Inputs floder to test your code and validate against the Outputs folder.
*/


# include "bits/stdc++.h"

using namespace std;

template <typename T>
class Deque
{
    // Write a "Friend" function that overloads the "<<"" operator, and can be used to "cout" a deque.
    // Read about friend functions. Note that friend functions have access to private, public and 
    // protected members! 
    friend ostream& operator<<(ostream& out, const Deque& dq)
    { 
        // TODO: Complete the overloading function. 
        // HINT: You just have to populate the ostream (output stream) with the members of the deque
        // array!
        if(dq.size==dq.capacity){ // when deque is full, front and back are same
            int j=0;
            int i = dq.front;
            while(j<dq.size){
                out << dq.arr[i] << ' ';
                j++;
                i = (i + 1) % dq.capacity;
            }
        }else{
            for(int i = dq.front; i != dq.back; i = (i + 1) % dq.capacity){
                out << dq.arr[i] << ' ';
            }
        }

      return out;
    }

// Think about why we are declaring these variables as protected and not private. Read about 
// different ways of scoping and their functions and uses in class inheritance. 
protected:
// TODO: Suitably initialize the queue parameters (Feel free to add any other variables as needed) 
    T* arr;
    int capacity;
    int size;
    bool auto_resize;
    int resize_factor;
    int front;
    int back;

public:
    Deque(int cap, bool resize = true, int resize_factor = 2) 
    {                                           
        // TODO: Implement the constructor that initializes the Deque with a given capacity
        // and optionally the resize factor
        this -> capacity = cap;
        this -> auto_resize = resize;
        this -> resize_factor = resize_factor;
        this -> size = 0;
        this -> front = 0;
        this -> back = 0;
        this -> arr = new T[capacity];
    }

    Deque(bool resize = true, int resize_factor = 2)
    {
        // TODO: Implement the constructor that initializes the Deque with a default capacity
        // and optionally given the resize factor
        this -> capacity = 10;
        this -> auto_resize = resize;
        this -> resize_factor = resize_factor;
        this -> size = 0;
        this -> front = 0;
        this -> back = 0;
        this -> arr = new T[this->capacity];
    }

    Deque(const Deque& dq)
    {
        // TODO: Implement the copy constructor for the Deque. 
        // What you need to do is copy the contents of the Deque 
        // object dq to the new Deque object being instantiated.
        this -> capacity = dq.capacity;
        this -> auto_resize = dq.auto_resize;
        this -> resize_factor = dq.resize_factor;
        this -> size = dq.size;
        this -> front = dq.front;
        this -> back = dq.back;
        this -> arr = new T[this->capacity];
        for(int i=0; i<size; i++){
            this -> arr[i] = dq.arr[(dq.front+i)%dq.capacity];
        }
    }

    ~Deque()
    {
        // TODO: Implement the destructor
        if(arr != NULL)  delete[] arr;
        arr = nullptr;
    }

    int get_capacity()
    {
        // TODO: Implement a getter for the capacity of the Deque
        return this->capacity;
      return 0; //Dummy
    }

    int get_size()
    {
        // TODO: Implement a getter for the size of the Deque
        return this->size;
      return 0; //Dummy
    }

    bool is_empty()
    {
        if(size == 0 ) return true;
      return false; //Dummy
    }  

// ATTENTION S'il vous plait !!
// We DO NOT want to use Deque as a data structure for the purpose of this lab,
// but want to be able to inherit it's functions selectively and create our 
// Stack and Queue. Therefore, we do not make the following functions public.
// There is no selective inheritance in C++. So, we have to use the "using" keyword
protected:
    bool push_back(T data)
    {
        // TODO: Implement the push_back method to push the data into the back of the deque
        // If the deque is full and auto_resize is true, scale the capacity of the deque
        // Returns true if push succeds else returns false
        if(size==capacity && auto_resize){
            resize();
        }

        // if(front == -1 && back == 0 && size < capacity){      /// first element insertion;
        //     arr[back++] = data;
        //     front++;
        //     size++;

        //     return true;
        // }else
        // if(abs(back-front)>0 && size < capacity){
        if(size < capacity){
            arr[back] = data;
            back = (back+1)%capacity;
            size++;
            return true;
        }
        return false;
    }

    T pop_front()
    {
        // TODO: Implement the pop_front method to pop the data from the front of the deque
        // Throw exception if the deque is empty
        if(size==0) throw invalid_argument("deque is empty!");

        T val = arr[front];
        front = (front + 1)%capacity;
        size--;

        return val;
    }

    bool push_front(T data)
    {
        // TODO: Implement the push_front method to push the data into the front of the deque
        // If the deque is full and auto_resize is true, scale the capacity of the deque
        // Returns true if push succeds else returns false
        if(size==capacity && auto_resize){
            resize();
        }

        // if(abs(back-front)>0 && size < capacity){
        if(size < capacity){
            // if(front==-1){
            //     front = capacity-1;
            //     arr[front] = data;
            //     size++;
            //     return true;
            // }else{
            front = (capacity + front - 1)%capacity;
            arr[front] = data;
            size++;
            return true;
            // }
        }
      return false;
    }

    T pop_back()
    {
        // TODO: Implement the pop_back method to pop the data from the back of the deque
        // Throw exception if the deque is empty
        if(size == 0) throw invalid_argument("deque is empty!");

        back = (capacity + back - 1) % capacity;
        T val = arr[back];
        size--;

        return val;
    }

    T peek_front()
    {
        // TODO: Implement the peek_front method to return the front element of the deque
        // Throw exception if the deque is empty
        if(size == 0) throw invalid_argument("deque is empty!");
        return arr[front];
    }

    T peek_back()
    {
        // TODO: Implement the peek_back method to return the last element of the deque
        // Throw exception if the deque is empty
        if(size == 0) throw invalid_argument("deque is empty!");
        return arr[(capacity+back-1)%capacity];
    }
    void resize(){

        int newcapacity = capacity * resize_factor;
        T* newArr = new T[newcapacity];
        
        for(int i=0;i < size; i++){
            newArr[i] = arr[(front+i) % capacity];
        }

        front = 0;
        back = size;
        capacity = newcapacity;

        delete [] arr;

        arr = newArr;
    }
};

// Before you go on to this part, read about class inheritance and understand the 3 types below:

// Public inheritance: public->public, protected->protected
// Protected inheritance: public->protected, protected->protected
// Private inheritance (default): public->private, protected->private

//To access private members of the base class, you need to declare derived class as a friend class

// Now, create the Queue class, and you must derive it from Deque. Why implement everything again!

template<typename T>
class Queue : public Deque<T>
{
    // TODO: Write a similar friend function to overload << as Deque
    
public:
    // TODO: Inherit the constructor that initializes the queue with a given capacity
    // and optionally the resize factor from Deque
    Queue(int cap, bool resize = true, int resize_factor = 2) : Deque<T>(cap, resize, resize_factor)
    {}

    // TODO: Inherit the constructor that initializes the queue with a default capacity
    // and optionally given the resize factor from Deque
    Queue(bool resize = true, int resize_factor = 2) : Deque<T>(resize, resize_factor)
    {}

    // TODO: Write a custom copy constructor for the Queue. It must take a const reference to a
    // Queue object and copy its contents to the new Queue object being created.
    // HINT: You can use the copy constructor of the Deque class to copy the contents of the Deque

    Queue(const Queue& q): Deque<T>(q){}    // upcasting to Deque<T> and calling copy constructor of Deque<T>


    // NOTE: Since Queue inherits from Deque, and Deque already has a destructor that correctly
    // deallocates the dynamic array arr, you don't need to write an additional destructor for Queue 

    // TODO: Make the (protected) member functions from Deque that are needed publicly by a 
    // Queue as Public members
    // HINT: do it by "using" 
    using Deque<T>:: push_back;
    using Deque<T>:: pop_front;
    using Deque<T>:: peek_front;
};

// Now, create the Stack class, and you must derive it from Deque. Why implement everything again!

template<typename T>
class Stack : public Deque<T>
{
    // TODO: Write a similar friend function to overload << as Deque
    
public:
    // TODO: Inherit the constructor that initializes the queue with a given capacity
    // and optionally the resize factor from Deque
    Stack(int cap, bool resize = true, int resize_factor = 2): Deque<T>(cap, resize, resize_factor) 
    {}

    // TODO: Inherit the constructor that initializes the queue with a default capacity
    // and optionally given the resize factor from Deque
    Stack(bool resize = true, int resize_factor = 2): Deque<T>(resize, resize_factor)
    {}

    // TODO: Write a custom copy constructor for the Stack. It must take a const reference to a
    // Stack object and copy its contents to the new Stack object being created.
    // HINT: You can use the copy constructor of the Deque class to copy the contents of the Deque
    Stack(const Stack& s): Deque<T>(s){ }
    /*
    const allows binding to base class reference.
    Why after upcasting nothing is changed for s?
    const Stack& s = ...;
    const Deque<T>& ref = s;  // Temporary base view only for copy constructor of Deque.
    */

    // NOTE: Since Stack inherits from Deque, and Deque already has a destructor that correctly
    // deallocates the dynamic array arr, you don't need to write an additional destructor for Stack 

    // TODO: Make the (protected) member functions from Deque that are needed publicly by a 
    // Stack as Public members
    // HINT: do it by "using" the necessary functions
    using Deque<T>:: push_back;
    using Deque<T>:: peek_back;
    using Deque<T>:: pop_back;
};

/*
Summary of "using" keyword in C++:
    Namespace: Brings all or specific members of a namespace into scope.
    Type Aliasing: Creates aliases for long or complex type names.
    Constructor Inheritance: Inherits constructors from a base class.
    Member Function Visibility: Exposes base class methods when name hiding occurs.
    Nested Types: Brings nested types from a base class into the derived class.
    using can promote the access level of protected or private methods to public.
    It does not work for data members; their access level remains unchanged.
*/