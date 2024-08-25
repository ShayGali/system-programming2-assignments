// @author shay.gali@msmail.ariel.ac.il
#include <algorithm>
#include <iostream>
#include <string>

#include "complex.hpp"
#include "node.hpp"
#include "tree.hpp"

using std::cout;
using std::endl;
using std::string;

void traverse_demo() {
    Node<double> root_node = Node(1.1);
    Node<double> n1 = Node(1.2);
    Node<double> n2 = Node(1.3);
    Node<double> n3 = Node(1.4);
    Node<double> n4 = Node(1.5);
    Node<double> n5 = Node(1.6);

    {
        Tree<double> tree;  // Binary tree that contains doubles.
        tree.add_root(&root_node);

        tree.add_sub_node(&root_node, &n1);
        tree.add_sub_node(&root_node, &n2);
        tree.add_sub_node(&n1, &n3);
        tree.add_sub_node(&n1, &n4);
        tree.add_sub_node(&n2, &n5);

        // The tree should look like:
        /**
         *       1.1
         *     /       \
         *    1.2      1.3
         *   /  \      /
         *  1.4  1.5  1.6
         */

        cout << "In order scan:\n";
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
            cout << node->get_data() << ", ";
        }  // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
        cout << endl;

        cout << "Pre order scan:\n";
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
            cout << node->get_data() << ", ";
        }  // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
        cout << endl;

        cout << "Post order scan:\n";
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
            cout << node->get_data() << ", ";
        }  // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
        cout << endl;

        cout << "BFS scan:\n";
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
            // cout << node->get_data() << ", ";
            cout << *node << ", ";
        }  // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
        cout << endl;

        cout << "DFS scan:\n";
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
            cout << node->get_data() << ", ";
        }  // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
        cout << endl;

        for (auto node : tree) {
            cout << node << ", ";
        }  // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
        cout << endl;
    }

    {
        Tree<double, 3> three_ary_tree;  // 3-ary tree.
        three_ary_tree.add_root(&root_node);
        three_ary_tree.add_sub_node(&root_node, &n1);
        three_ary_tree.add_sub_node(&root_node, &n2);
        three_ary_tree.add_sub_node(&root_node, &n3);
        three_ary_tree.add_sub_node(&n1, &n4);
        three_ary_tree.add_sub_node(&n2, &n5);

        // The tree should look like:
        /**
         *       root = 1.1
         *     /      |     \
         *    1.2    1.3    1.4
         *   /        |
         *  1.5      1.6
         */

        cout << "DFS scan:\n";
        for (auto node = three_ary_tree.begin_dfs_scan(); node != three_ary_tree.end_dfs_scan(); ++node) {
            cout << node->get_data() << ", ";
        }  // prints: 1.1, 1.2, 1.5, 1.3, 1.6, 1.4
        cout << endl;

        cout << "BFS scan:\n";
        for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node) {
            cout << node->get_data() << ", ";
        }  // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
        cout << endl;
    }
}

int main() {
    cout << "Traverse demo:\n";
    traverse_demo();

    cout << "Simple tree GUI:" << endl;

    Node<int> nodes[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

    Tree<int, 2> tree;

    tree.add_root(&nodes[0]);

    for (int i = 1; i < 15; i++) {
        tree.add_sub_node(&nodes[(i - 1) / 2], &nodes[i]);
    }

    cout << "BFS scan:\n";
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        cout << it->get_data() << " ";
    }
    cout << endl;

    cout << "in-order scan:\n";
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        cout << it->get_data() << " ";
    }
    cout << endl;

    cout << tree;

    {
        cout << "String tree GUI:" << endl;
        Node<string> root("root");
        Node<string> r1_1("r1_1");
        Node<string> r1_2("r1_2");
        Node<string> r2_1_1("r2_1_1");
        Node<string> r2_1_2("HOIIIIIIIIIIIIIII");

        Tree<string> s_tree;
        s_tree.add_root(&root);
        s_tree.add_sub_node(&root, &r1_1);
        s_tree.add_sub_node(&root, &r1_2);
        s_tree.add_sub_node(&r1_1, &r2_1_1);
        s_tree.add_sub_node(&r1_1, &r2_1_2);

        cout << s_tree;
    }

    {
        cout << "Complex tree GUI:\n";
        Node<Complex> root(Complex(0, 1.1));
        Node<Complex> n1(Complex(-1.2, -1.2));
        Node<Complex> n2(Complex(0.3, -1.3));
        Node<Complex> n3(Complex(1.4, 1.4));
        Node<Complex> n4(Complex(-3.5, 1.5));
        Node<Complex> n5(Complex(1.6, 0));
        Node<Complex> n6(Complex(1.7, 1));
        Node<Complex> n7(Complex(1.8, 1.8));

        Tree<Complex, 4> complex_tree;
        complex_tree.add_root(&root);
        complex_tree.add_sub_node(&root, &n1);
        complex_tree.add_sub_node(&root, &n2);
        complex_tree.add_sub_node(&root, &n3);
        complex_tree.add_sub_node(&n1, &n4);
        complex_tree.add_sub_node(&n1, &n5);
        complex_tree.add_sub_node(&n2, &n6);
        complex_tree.add_sub_node(&n2, &n7);

        cout << "DFS scan:\n";
        for (auto it = complex_tree.begin_dfs_scan(); it != complex_tree.end_dfs_scan(); ++it) {
            cout << *it << "\n";
        }
        cout << endl;

        complex_tree.draw(300, 50);  // Starting position of the root
    }
    return 0;
}