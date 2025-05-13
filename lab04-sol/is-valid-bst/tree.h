#include <compare>
// The <compare> header introduces three-way comparison (spaceship operator <=>), which 
// simplifies comparisons and ordering.
#include <concepts>
// std::integral<T> → Ensures T is an integer type.
// std::floating_point<T> → Ensures T is a floating-point type.
// std::totally_ordered<T> → Ensures T supports comparison (<, >, ==, etc.).
#include <memory>
#pragma once        // include once.

/* This file defines the structure of a node in a binary tree.
 * Your task is present in the files "employee.h", and "is_valid_bst.h".
 * You should complete both tasks, without modifying anything in this file.
 *
 * BONUS: If you change "weak_ptr" to "shared_ptr" in the member "parent",
 * what do you think will happen? Why?
 */

template <std::totally_ordered T>
struct node_t {
    T value;
    std::shared_ptr<struct node_t> left_child = nullptr;
    std::shared_ptr<struct node_t> right_child = nullptr;
    std::weak_ptr<struct node_t> parent;

    node_t() = default;
    node_t(T val) : value(val) {}
    ~node_t() = default;
};

/*
Using std::weak_ptr for parent prevents memory leaks by breaking potential cyclic dependencies in a 
tree structure where each node has bidirectional references. The std::shared_ptr for children maintains 
ownership, while the std::weak_ptr for parent allows safe, non-owning access.
*/