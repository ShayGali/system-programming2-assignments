// @author shay.gali@msmail.ariel.ac.il
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../complex.hpp"
#include "../node.hpp"
#include "../tree.hpp"
#include "doctest.h"

using std::cout;
using std::endl;

TEST_CASE("binary tree") {
    Node<int> root(1);
    Node<int> n2(2);
    Node<int> n3(3);
    Node<int> n4(4);
    Node<int> n5(5);
    Node<int> n6(6);
    Node<int> n7(7);

    Tree<int, 2> tree;
    tree.add_root(&root);

    tree.add_sub_node(&root, &n2);
    tree.add_sub_node(&root, &n3);
    tree.add_sub_node(&n2, &n4);
    tree.add_sub_node(&n2, &n5);
    tree.add_sub_node(&n3, &n6);
    tree.add_sub_node(&n6, nullptr);
    tree.add_sub_node(&n6, &n7);
    /*
    tree should look like this:
            1
           /  \
          2    3
         / \    \
        4   5    6
                 / \
                n   7
    */

    SUBCASE("in order traversal") {
        int expected[] = {4, 2, 5, 1, 6, 7, 3};
        int i = 0;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node, ++i) {
            CHECK(node->get_data() == expected[i]);
        }
    }

    SUBCASE("pre order traversal") {
        int expected[] = {1, 2, 4, 5, 3, 6, 7};
        int i = 0;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node, ++i) {
            CHECK(node->get_data() == expected[i]);
        }
    }

    SUBCASE("post order traversal") {
        int expected[] = {4, 5, 2, 7, 6, 3, 1};
        int i = 0;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node, ++i) {
            CHECK(node->get_data() == expected[i]);
        }
    }

    SUBCASE("bfs traversal") {
        int expected[] = {1, 2, 3, 4, 5, 6, 7};
        int i = 0;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node, ++i) {
            CHECK(node->get_data() == expected[i]);
        }
    }

    SUBCASE("dfs traversal") {
        int expected[] = {1, 2, 4, 5, 3, 6, 7};
        int i = 0;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node, ++i) {
            CHECK(node->get_data() == expected[i]);
        }
    }

    SUBCASE("heap traversal") {
        int expected[] = {1, 2, 3, 4, 5, 6, 7};
        int i = 0;
        for (auto node = tree.begin_make_heap(); node != tree.end_make_heap(); ++node, ++i) {
            CHECK(node->get_data() == expected[i]);
        }
    }

    SUBCASE("empty tree") {
        Tree<int, 2> tree;
        CHECK(tree.begin_in_order() == tree.end_in_order());
        CHECK(tree.begin_pre_order() == tree.end_pre_order());
        CHECK(tree.begin_post_order() == tree.end_post_order());
        CHECK(tree.begin_bfs_scan() == tree.end_bfs_scan());
        CHECK(tree.begin_dfs_scan() == tree.end_dfs_scan());
        CHECK(tree.begin_make_heap() == tree.end_make_heap());
    }
}

TEST_CASE("trenaury tree") {
    cout << "trenaury tree" << endl;
    Node<int> nodes[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    Tree<int, 3> tree;
    tree.add_root(&nodes[0]);

    tree.add_sub_node(&nodes[0], &nodes[1]);
    tree.add_sub_node(&nodes[0], nullptr);
    tree.add_sub_node(&nodes[0], &nodes[2]);

    tree.add_sub_node(&nodes[1], &nodes[3]);
    tree.add_sub_node(&nodes[1], &nodes[4]);
    tree.add_sub_node(&nodes[1], &nodes[5]);

    tree.add_sub_node(&nodes[2], &nodes[6]);
    tree.add_sub_node(&nodes[2], &nodes[7]);
    tree.add_sub_node(&nodes[2], &nodes[8]);

    tree.add_sub_node(&nodes[3], &nodes[9]);

    tree.add_sub_node(&nodes[8], &nodes[13]);
    tree.add_sub_node(&nodes[8], &nodes[14]);
    tree.add_sub_node(&nodes[14], nullptr);

    tree.add_sub_node(&nodes[9], &nodes[10]);
    tree.add_sub_node(&nodes[9], &nodes[11]);
    tree.add_sub_node(&nodes[9], &nodes[12]);

    SUBCASE("dfs traversal") {
        int expected[] = {1, 2, 4, 10, 11, 12, 13, 5, 6, 3, 7, 8, 9, 14, 15};
        int i = 0;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node, ++i) {
            CHECK(node->get_data() == expected[i]);
        }
    }

    SUBCASE("bfs traversal") {
        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 11, 12, 13};
        int i = 0;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node, ++i) {
            CHECK(node->get_data() == expected[i]);
        }
    }

    SUBCASE("empty tree") {
        Tree<int, 3> tree;
        CHECK(tree.begin_dfs_scan() == tree.end_dfs_scan());
        CHECK(tree.begin_bfs_scan() == tree.end_bfs_scan());
    }
}
