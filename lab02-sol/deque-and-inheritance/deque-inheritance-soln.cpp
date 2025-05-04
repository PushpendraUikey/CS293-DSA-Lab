# include "bits/stdc++.h"
using namespace std;

template <typename T>
class Deque
{
    friend ostream& operator<<(ostream& out, const Deque& dq)
    { 
        T* arr = dq.arr;
        if (dq.size == 0) {
            return out;
        }
        for(int i=dq.index_front; i<dq.index_front+dq.size; i++)
        {
            out << arr[i%dq.capacity] << " ";   // accumulation of output into the buffer
        }
        return out;
    }

protected:
    T* arr = NULL;
    int capacity = 5;
    int resize_factor = 2;
    int size = 0;
    int index_front = 0;
    int index_back = -1;
    bool auto_resize = true;

public:
    Deque(int cap, bool resize = true, int resize_factor = 2) 
    {                                           
        auto_resize = resize;
        capacity = cap;
        this->resize_factor = resize_factor;
        arr = new T[capacity];
    }

    Deque(bool resize = true, int resize_factor = 2)
    {
        arr = new T[capacity];
        auto_resize = resize;
        this->resize_factor = resize_factor;
    }

    Deque(const Deque& dq)
    {
        capacity = dq.capacity;
        resize_factor = dq.resize_factor;
        size = dq.size;
        index_front = dq.index_front;
        index_back = dq.index_back;
        auto_resize = dq.auto_resize;
        arr = new T[capacity];
        for(int i=index_front; i<index_front+size; i++)
        {
            arr[i%capacity] = dq.arr[i%capacity];
        }
    }

    ~Deque()
    {
        if(arr)
            delete[] arr;
    }

    void print()
    {
        for(int i=index_front; i<index_front+size; i++)
        {
            cout << arr[i%capacity] << " ";
        }
        cout << endl;
    }

    bool is_empty()
    {
        if(size == 0)
            return true;
        else return false;
    } 

    int get_capacity()
    {
        return capacity;
    }

    int get_size()
    {
        return size;
    }
protected:
//Returns true if push succeds else returns false
    bool push_back(T data)
    {
        if (size >= capacity)
        {
            if(auto_resize == false)
                return 0;
            else 
            {   
                capacity = resize_factor*capacity;
                T* arr2 = arr;      // this is pointer sharing

                //nothrow is a special option that instructs new not to throw an exception if the memory allocation fails. 
                //Instead, it will return a nullptr (i.e., NULL) if it cannot allocate the requested memory
                arr = new(nothrow) T[capacity];
                if(!arr) 
                    return 0;
                for(int i=index_front; i<index_front+size; i++)
                {
                    arr[i-index_front] = arr2[i%capacity];  // pretty nice logic to reallocate array from start index(0)
                }
                index_back=size;
                index_front=0;
                arr[size] = data;
                size++;
                delete[] arr2;
                arr2 = NULL;
            }
        }
        else
        {
            index_back = (index_back+1)%capacity;
            arr[index_back] = data;
            size++;
        }
        return 1;
    }

//Throw exception if the queue is empty
    T pop_front()
    {
        if(is_empty())
            throw;

        T num_pop = arr[index_front];
        index_front = (index_front+1)%capacity;
        size--;
        return num_pop;
    }

//Returns true if push succeds else returns false
    bool push_front(T data)
    {
        if (size >= capacity)
        {
            if(auto_resize == false)
                return 0;
            else 
            {   
                capacity = resize_factor*capacity;
                T* arr2 = arr;
                arr = new(nothrow) T[capacity];
                if(!arr) 
                    return 0;
                for(int i=index_front; i<index_front+size; i++)
                {
                    arr[i-index_front+1] = arr2[i%capacity];    //started allocating data from 1st index so that element pushed in front we'd keep it in 0th index
                }
                index_back=size;
                index_front=0;
                arr[0] = data;
                size++;
                delete[] arr2;
                arr2 = NULL;
            }
        }
        else
        {
            index_front = (index_front-1+capacity)%capacity;    // front_index decrement(it is pointing to data)
            arr[index_front] = data;
            size++;
        }
        return 1;
    }

    T pop_back()
    {
        if(is_empty())
            throw;

        T num_pop = arr[index_back];
        index_back = (index_back-1+capacity)%capacity;
        size--;
        return num_pop;
    }

//Throw exception if the queue is empty
    T peek_front()
    {
        if(is_empty())
        {
            throw;
        }
        return arr[index_front];
    }

//Throw exception if the queue is empty
    T peek_back()
    {
        if(is_empty())
        {
            throw;
        }
        return arr[index_back];
    }
};

//Public inheritance: public->public, protected->protected
//Protected inheritance: public->protected, protected->protected
//Private inheritance (default): public->private, protected->private

//To access private members of the base class, need to declare derived class as a friend class

template<typename T>
class Queue : public Deque<T>
{
public:
    Queue(int cap, bool resize = true, int resize_factor = 2) 
        : Deque<T>(cap, resize, resize_factor) 
    {}

    Queue(bool resize = true, int resize_factor = 2)
        : Deque<T>(resize, resize_factor) 
    {}

    Queue(const Queue& q)
        : Deque<T>(q)
    {}

    // To create a function called 'push' in Queue, make a wrapper
    bool push(T data) {
        return push_back(data);
    }
//Improved Readability: You can directly use methods from the base class in the derived 
//class without additional qualification. like don't need to qualify with Deque<T>:: each time on access
    using Deque<T>::push_back;
    using Deque<T>::pop_front;
    using Deque<T>::peek_front;
};

template<typename T>
class Stack : public Deque<T>
{
public:
    Stack(int cap, bool resize = true, int resize_factor = 2) 
        : Deque<T>(cap, resize, resize_factor) 
    {}

    Stack(bool resize = true, int resize_factor = 2)
        : Deque<T>(resize, resize_factor) 
    {}

    Stack(const Stack& q)
        : Deque<T>(q)
    {}

    using Deque<T>::push_back;
    using Deque<T>::pop_back;
    using Deque<T>::peek_back;
};