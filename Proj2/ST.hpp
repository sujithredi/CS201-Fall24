#ifndef _ST_HPP_
#define _ST_HPP_

#include <utility>
#include "RBT.hpp"
#include "RBTPrint.hpp"

/* 
Name: Joseph Sujith Reddy Mareddy
Email: jmareddy@crimson.ua.edu
Course Section: Spring 2025 CS 201
Homework #: 2
*/

template <class Key, class Type>
class ST : public RedBlackTree<Key, Type> {
public:
    typedef RBTNode<Key, Type>* iterator;
    // Constructors
    ST() {
        RedBlackTree<Key, Type>();
    }

    // Destructor
    ~ST() {
        clear();
    }
    // access or insert specifies element
    // inserts if the key is not present and returns a reference
    // the value corresponding to that key O(LogN), N size of ST
    Type& operator[](const Key& key) {
        RBTNode<Key, Type>* node = RedBlackTree<Key, Type>::Search(key);
        if (node == nullptr) {
            node = RedBlackTree<Key, Type>::Insert(key, Type{});
        }
        return node->value;
    }

    // insert a (key, value) pair, if the key already exists
    // set the new value to the existing key O(LogN), N size of ST
    void insert(const Key& key, const Type& value) {
        RBTNode<Key, Type>* node = RedBlackTree<Key, Type>::Search(key);
        if (node == nullptr) {
            RedBlackTree<Key, Type>::Insert(key, value);
        }
        else {
            node->value = value;
        }
    }

    // remove element at the given position
    void remove(iterator position) {
        if (position != nullptr) {
            RedBlackTree<Key, Type>::RemoveNode(position);
        }
    }

    // remove element with keyvalue key and 
    // return number of elements removed (either 0 or 1) O(logN), N size of ST
    std::size_t remove(const Key& key) {
        return RedBlackTree<Key, Type>::Remove(key);
    }

    // removes all elements from the ST, after this size() returns 0
    void clear() {
        RedBlackTree<Key, Type>::DeleteTree(RedBlackTree<Key, Type>::root);
        RedBlackTree<Key, Type>::root = nullptr;
    }

    // checks if ST has no elements; true is empty, false otherwise
    bool empty() const {
        return RedBlackTree<Key, Type>::root == nullptr;
    }

    // returns number of elements in ST
    std::size_t size() const {
        if (RedBlackTree<Key, Type>::root == nullptr) {
            return 0;
        }
        else {
            return RedBlackTree<Key, Type>::root->Count();
        }
    }

    // returns number of elements that match keyvalue key
    // value returned is 0 or 1 since keys are unique O(LogN), N size of ST
    std::size_t count(const Key& key) {
        return RedBlackTree<Key, Type>::Search(key) != nullptr ? 1 : 0;
    }

    // find an element with keyvalue key and return 
    // the iterator to the element found, nullptr if not found O(LogN), N size of ST
    iterator find(const Key& key) {
        return RedBlackTree<Key, Type>::Search(key);
    }

    // check if key exists in ST O(LogN), N size of ST
    bool contains(const Key& key) {
        return RedBlackTree<Key, Type>::Search(key) != nullptr;
    }

    // return contents of ST as a vector of (key,value) pairs O(N), N size of ST
    std::vector<std::pair<Key, Type> > toVector() {
        std::vector<std::pair<Key, Type> > vec;
        toVectorRecursive(RedBlackTree<Key, Type>::root, vec);
        return vec;
    }

    // print the symbol table as Red-Black Tree O(N), N size of ST
    void displayTree() {
        std::cout << RBTPrint<Key,Type>::TreeToString(RedBlackTree<Key,Type>::root) << std::endl;
    }

    // print the symbol table in sorted order O(N), N size of ST
    void display() {
        displayRecursive(RedBlackTree<Key, Type>::root);
    }

private:
    void toVectorRecursive(RBTNode<Key, Type>* node, std::vector<std::pair<Key, Type> >& vec) {
        if (node == nullptr) {
            return;
        }
        toVectorRecursive(node->left, vec);
        vec.push_back({node->key, node->value});
        toVectorRecursive(node->right, vec);
    }

    void displayRecursive(RBTNode<Key, Type>* node) {
        if (node == nullptr) {
            return;
        }
        displayRecursive(node->left);
        std::cout << node->key << ": " << node->value << std::endl;
        displayRecursive(node->right);
    }
};

#endif
