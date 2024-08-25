// @author shay.gali@msmail.ariel.ac.il
#pragma once

#include <queue>
#include <stack>
#include <vector>

#include "node.hpp"

using std::queue;
using std::stack;
using std::vector;

template <typename T>
class in_order_iterator {
   private:
    stack<Node<T>*> stck;

   public:
    in_order_iterator(Node<T>* root) {
        // push all the left children of the root
        stck.push(nullptr);
        while (root != nullptr) {
            stck.push(root);
            if (root->get_childrens().size() > 0 && root->get_childrens().at(0) != nullptr) {  // has left child
                root = root->get_childrens().at(0);
            } else {
                root = nullptr;  // end the loop
            }
        }
    }

    T& operator*() { return stck.top()->get_data(); }

    Node<T>* operator->() { return stck.top(); }

    in_order_iterator& operator++() {
        Node<T>* node = stck.top();
        stck.pop();
        // if the node has a right child, push it and all its left children
        if (node->get_childrens().size() > 1 && node->get_childrens().at(1) != nullptr) {
            Node<T>* right_child = node->get_childrens().at(1);
            stck.push(right_child);
            // push all the left children of the right child
            Node<T>* right_child_left_child = right_child;
            while (right_child_left_child->get_childrens().size() > 0 && right_child_left_child->get_childrens().at(0) != nullptr) {
                right_child_left_child = right_child_left_child->get_childrens().at(0);
                stck.push(right_child_left_child);
            }
        }

        return *this;
    }

    bool operator==(const in_order_iterator& other) const { return stck.top() == other.stck.top(); }
    bool operator!=(const in_order_iterator& other) const {
        return !(*this == other);
    }
};

template <typename T>
class pre_order_iterator {
   private:
    stack<Node<T>*> stck;

   public:
    pre_order_iterator(Node<T>* root) {
        stck.push(nullptr);  // for the end
        if (root != nullptr) {
            // start from the root
            stck.push(root);
        }
    }

    T& operator*() { return stck.top()->get_data(); }

    Node<T>* operator->() { return stck.top(); }

    pre_order_iterator& operator++() {
        Node<T>* node = stck.top();
        stck.pop();
        // push the right child first, and then the left child (if exists)
        if (node->get_childrens().size() > 1 && node->get_childrens().at(1) != nullptr) {
            stck.push(node->get_childrens().at(1));
        }
        if (node->get_childrens().size() > 0 && node->get_childrens().at(0) != nullptr) {
            stck.push(node->get_childrens().at(0));
        }

        return *this;
    }

    bool operator==(const pre_order_iterator& other) const {
        return stck.top() == other.stck.top();
    }

    bool operator!=(const pre_order_iterator& other) const {
        return !(*this == other);
    }
};

template <typename T>
class post_order_iterator {
   private:
    vector<Node<T>*> post_order;  // the post order of the tree
    int index;                    // the index of the current node in the post order

   public:
    post_order_iterator(Node<T>* root) {
        index = 0;
        if (root == nullptr) {
            return;
        }
        stack<Node<T>*> stck;
        stck.push(root);
        Node<T>* prev = nullptr;
        while (!stck.empty()) {
            Node<T>* current = stck.top();
            // if we are going down the tree
            if (prev == nullptr || (prev->get_childrens().size() > 0 && prev->get_childrens().at(0) == current) || (prev->get_childrens().size() > 1 && prev->get_childrens().at(1) == current)) {
                if (current->get_childrens().size() > 0 && current->get_childrens().at(0) != nullptr) {         // has left child
                    stck.push(current->get_childrens().at(0));                                                  // go left
                } else if (current->get_childrens().size() > 1 && current->get_childrens().at(1) != nullptr) {  // has right child
                    stck.push(current->get_childrens().at(1));                                                  // go right
                } else {                                                                                        // leaf
                    post_order.push_back(current);
                    stck.pop();
                }
                // if we are going up the tree from left child
            } else if (current->get_childrens().size() > 0 && prev == current->get_childrens().at(0)) {
                if (current->get_childrens().size() > 1 && current->get_childrens().at(1) != nullptr) {  // has right child
                    stck.push(current->get_childrens().at(1));
                } else {
                    post_order.push_back(current);
                    stck.pop();
                }
                // if we are going up the tree from right child
            } else if (current->get_childrens().size() > 1 && prev == current->get_childrens().at(1)) {
                post_order.push_back(current);
                stck.pop();
            }
            prev = current;
        }
    }

    T& operator*() { return post_order[index]->get_data(); }

    Node<T>* operator->() { return post_order[index]; }

    post_order_iterator& operator++() {
        index++;
        return *this;
    }

    bool operator==(const post_order_iterator& other) const { return post_order.size() - index == other.post_order.size() - other.index; }
    bool operator!=(const post_order_iterator& other) const {
        return !(*this == other);
    }
};

template <typename T>
class bfs_scan_iterator {
   private:
    queue<Node<T>*> q;

   public:
    bfs_scan_iterator(Node<T>* root) {
        if (root == nullptr) {
            return;
        }
        // start from the root
        q.push(root);
    }

    T operator*() { return q.front()->get_data(); }
    Node<T>* operator->() { return q.front(); }

    bfs_scan_iterator& operator++() {
        Node<T>* node = q.front();
        q.pop();

        // push all the children of the node
        for (size_t i = 0; i < node->get_childrens().size(); i++) {
            if (node->get_childrens().at(i) != nullptr) {
                q.push(node->get_childrens().at(i));
            }
        }

        return *this;
    }

    bool operator==(const bfs_scan_iterator& other) const { return q.size() == other.q.size(); }
    bool operator!=(const bfs_scan_iterator& other) const {
        return !(*this == other);
    }
};

template <typename T>
class dfs_scan_iterator {
   private:
    stack<Node<T>*> stck;

   public:
    dfs_scan_iterator(Node<T>* root) {
        if (root == nullptr) {
            return;
        }
        // start from the root
        stck.push(root);
    }

    const T& operator*() { return stck.top()->get_data(); }

    Node<T>* operator->() { return stck.top(); }

    dfs_scan_iterator& operator++() {
        Node<T>* node = stck.top();
        stck.pop();
        // push all the children of the node in reverse order
        for (int i = node->get_childrens().size() - 1; i >= 0; i--) {
            if (node->get_childrens().at(i) != nullptr) {
                stck.push(node->get_childrens().at(i));
            }
        }
        return *this;
    }

    bool operator==(const dfs_scan_iterator& other) const { return stck.size() == other.stck.size(); }
    bool operator!=(const dfs_scan_iterator& other) const {
        return !(*this == other);
    }
};

template <typename T>
class make_heap_iterator {
   private:
    vector<Node<T>*> heap;  // for the heap nodes
    int i;                  // the index of the current node in the heap

   public:
    make_heap_iterator(Node<T>* root) {
        i = 0;
        if (root == nullptr) {
            return;
        }

        // put all the nodes in the tree in a vector
        for (auto it = bfs_scan_iterator<T>(root); it != bfs_scan_iterator<T>(nullptr); ++it) {
            heap.push_back(it.operator->());
        }

        // make the vector a heap
        std::make_heap(heap.begin(), heap.end(), [](Node<T>* a, Node<T>* b) { return a->get_data() > b->get_data(); });
    }

    T& operator*() { return heap[i]->get_data(); }

    Node<T>* operator->() { return heap[0]; }

    make_heap_iterator& operator++() {
        std::pop_heap(heap.begin(), heap.end() - i, [](Node<T>* a, Node<T>* b) { return a->get_data() > b->get_data(); });
        i++;
        return *this;
    }

    bool operator==(const make_heap_iterator& other) const { return heap.size() - i == other.heap.size() - other.i; }
    bool operator!=(const make_heap_iterator& other) const {
        return !(*this == other);
    }
};