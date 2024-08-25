// @author shay.gali@msmail.ariel.ac.il

#pragma once
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::to_string;
using std::vector;

/**
 * Converts a string to a string. (overload the std::to_string function for string class)
 * T should have a to_string function.
 * T should have << operator.
 */
string to_string(const string &str) {
    return str;
}

/**
 * Represents a node in a tree, a node can have any type of data and any number of children.
 */
template <typename T>
class Node {
   public:
    T data;
    vector<Node<T> *> children;

   public:
    Node(T data) : data(data) {}

    const vector<Node<T> *> &get_childrens() const { return children; }

    const T &get_data() const { return data; }

    T &get_data() { return data; }

    void add_child(Node<T> *child) {
        children.push_back(child);
    }

    void remove_children() {
        children.clear();
    }

    /**
     * Returns a string representation of the node.
     * every string data that is longer than 11 characters will be shortened to 8 characters and "..." will be added to the end.
     */
    string to_short_string() const {
        string s;
        if (std::is_floating_point<T>::value) {
            std::ostringstream strs;
            strs << get_data();
            s = strs.str();
        } else {
            s = to_string(get_data());
        }

        if (s.length() > 11) {
            return s.substr(0, 8) + "...";
        }
        return s;
    }

    /**
     * Returns a string representation of the node.
     */
    string to_str() const {
        string s;
        if (std::is_floating_point<T>::value) {
            std::ostringstream strs;
            strs << get_data();
            s = strs.str();
        } else {
            s = to_string(get_data());
        }
        return s;
    }
};
