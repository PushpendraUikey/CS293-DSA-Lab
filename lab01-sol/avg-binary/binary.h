#include <iostream>
#include <vector>
#include <compare> // for std::totally_ordered
#include <concepts> // Template constraint checks

/*
You are to implement binary search.
Read up on C++ concepts here: https://en.cppreference.com/w/cpp/language/constraints
Use concepts to replace the work "typename" before "T" in all four function signatures.
You can also use a "requires" condition, mentioned in the same link.
Then, implement the binary search function yourself.
Handle corner cases appropriately, ensuring that the algorithm runs in O(log n) time.
Implement the O(n) version as well, for benchmarking.
*/

/*
template <std::totally_ordered T>:
To constrain templates so that only types that behave like fully 
orderable values (like int, double, etc.) are allowed.
That means if T is an object than it has to have the full support 
to all the comparison operators: <, <=, >, >=, ==, !=. 
*/


template <std::totally_ordered T> bool binarySearch(std::vector<T> &data, T src) {
    int left = 0;
    int right = data.size() - 1;
    if (data[left] > src || data[right] < src) {
        return false;
    }
    while (left + 1 < right) {
        int mid = (left + right)/2;
        if (data[mid] < src) {
            left = mid;
        } else if (data[mid] > src) {
            right = mid;
        } else {
            return true;
        }
    }
    if (data[left] == src || data[right] == src) {
        return true;
    }
    return false;
}

template <std::totally_ordered T> bool linearSearch(std::vector<T> &data, T src) {
    for (T elem : data) {
        if (elem == src) {
            return true;
        }
    }
    return false;
}


// OPTIONAL: Try implementing the lower bound function and benchmarking those.
// The lower bound function returns the largest element in the array that is less than or equal to the given value
// Binary Search approach for sorted arrays
template <std::totally_ordered T> T lowerBound(std::vector<T> &data, T src) {
    int left = 0;
    int right = data.size() - 1;
    if (data[left] > src) {
        return src;
    }
    if (data[right] < src) {
        return data[right];
    }
    while (left + 1 < right) {
        int mid = (left + right)/2;
        if (data[mid] < src) {
            left = mid;
        } else if (data[mid] > src) {
            right = mid;
        } else {
            return data[mid];
        }
    }
    if (data[right] <= src) {   // checked the right first because it is larger than left.
        return data[right];
    }
    return data[left];
}

// This linear version works for unsorted arrays as well.
template <std::totally_ordered T> T linearLowerBound(std::vector<T> &data, T src) {
    T low_bound = data[0];
    for (auto elem : data) {
        if (elem > src) {   // if the element is greater than src, skip it
            continue;
        }
        if (low_bound < elem) { // picks the larger of two
            low_bound = elem;
        }
    }
    return min(low_bound, src);
}

// Upper bound: smallest ele in the array that is greater than equal to the given element.
template <std::totally_ordered T> T upperBound(std::vector<T>& data, T src){
    int left = 0;
    int right = data.size()-1;
    if (data[left] >= src){
        return data[left];
    }
    if(data[right] < src){
        return src;
    }

    while(left + 1 >= right){
        int mid = (left + right)/2;
        if(data[mid] < src){
            left = mid;
        } else if(data[mid] > src){
            right = mid;
        } else {
            return data[mid];
        }
    }
    if(data[left] >= src){
        return data[left];
    }
    return data[right];
}