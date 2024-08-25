// @author shay.gali@msmail.ariel.ac.il

#pragma once

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <cmath>

#include "CustomEllipseItem.hpp"
#include "node.hpp"
#include "tree_iterators.hpp"

/**
 * @brief A base class for a tree.
 * Have common methods for all trees.

 */
template <typename T, size_t K>
class BaseTree {
   protected:
    Node<T>* root;

   public:
    BaseTree() : root(nullptr) {
    }

    ~BaseTree() {
        bfs_scan_iterator<T> it = begin_bfs_scan();
        bfs_scan_iterator<T> prev = it;
        bfs_scan_iterator<T> end = end_bfs_scan();
        while (it != end) {
            prev = it;
            ++it;
            prev->remove_children();
        }
        root = nullptr;
    }

    /**
     * @brief Add a root to the tree. If a root already exists, it will be replaced.
     */
    void add_root(Node<T>* root) {
        this->root = root;
    }

    /**
     * @brief Get a node in the tree, and anthor node, and put the second node as a child of the first node.
     *
     * If the parent node already has a left child, the new node will be added as the right child (and can override the existing right child).
     * Else, the new node will be added as the left child.
     */

    void add_sub_node(Node<T>* parent, Node<T>* child) {
        if (parent->get_childrens().size() >= K) {
            throw std::runtime_error("Parent already has " + std::to_string(K) + " children, can't add more.");
        }
        parent->add_child(child);
    }

    // override the << operator
    friend std::ostream& operator<<(std::ostream& os, const BaseTree<T, K>& tree) {
        tree.draw(300, 50);
        return os;
    }

    bfs_scan_iterator<T> begin() {
        return begin_bfs_scan();
    }

    bfs_scan_iterator<T> end() {
        return end_bfs_scan();
    }

    bfs_scan_iterator<T> begin_bfs_scan() {
        return bfs_scan_iterator<T>(root);
    }

    bfs_scan_iterator<T> end_bfs_scan() {
        return bfs_scan_iterator<T>(nullptr);
    }

    dfs_scan_iterator<T> begin_dfs_scan() {
        return dfs_scan_iterator<T>(root);
    }

    dfs_scan_iterator<T> end_dfs_scan() {
        return dfs_scan_iterator<T>(nullptr);
    }

    void draw(int x, int y, int circleSize = 75, int horizontalSpacing = 350, int verticalSpacing = 150) const {
        int argc = 0;
        char** argv = {nullptr};
        QApplication app(argc, argv);
        QGraphicsScene scene;
        QGraphicsView view(&scene);
        view.setBackgroundBrush(Qt::white);

        draw(&scene, root, x, y, circleSize, horizontalSpacing, verticalSpacing);

        view.show();

        app.exec();
    }

   private:
    void draw(QGraphicsScene* scene, Node<T>* node, int x, int y, int circleSize, int horizontalSpacing, int verticalSpacing,  int depth = 0) const {
        if (!node) return;

        // Create and add the custom ellipse item to the scene
        CustomEllipseItem* ellipse = new CustomEllipseItem(x, y, circleSize, circleSize, QString::fromStdString(node->to_str()));
        items.push_back(ellipse);
        scene->addItem(ellipse);

        // add a text item to the scene that contains the node's data
        QGraphicsTextItem* text = scene->addText(QString::fromStdString(node->to_short_string()));
        text->setPos(x + circleSize / 2 - text->boundingRect().width() / 2, y + circleSize / 2 - text->boundingRect().height() / 2);

        // calculate the horizontal spacing between children nodes
        int depthFactor = std::pow(2, depth);                                                   // Exponential growth factor(2^depth)
        int adjustedHorizontalSpacing = std::max(horizontalSpacing / depthFactor, circleSize);  // Ensure spacing doesn't become too small

        // Calculate the x position of the first child node
        int childX = x - (node->get_childrens().size() - 1) * adjustedHorizontalSpacing / 2;

        // Draw the children nodes
        for (Node<T>* child : node->get_childrens()) {
            if (child == nullptr) {  // if the child is nullptr, just add the horizontal spacing and continue
                childX += adjustedHorizontalSpacing;
                continue;
            }

            // Draw the line between the parent and the child
            scene->addLine(x + circleSize / 2, y + circleSize, childX + circleSize / 2, y + verticalSpacing, QPen(Qt::black));

            // Recursively draw child nodes with more aggressively adjusted spacing
            draw(scene, child, childX, y + verticalSpacing, circleSize, horizontalSpacing, verticalSpacing, items, depth + 1);
            childX += adjustedHorizontalSpacing;
        }
    }
};

/**
 * This is a generic tree class, it can be used with any type of data.
 * This class extends the BaseTree class and adds methods for iterating the tree in different orders.
 * There is another specialization for K = 2, which change the iterators.
 */
template <typename T, size_t K = 2>
class Tree : public BaseTree<T, K> {
   public:
    dfs_scan_iterator<T> begin_in_order() {
        return dfs_scan_iterator<T>(this->root);
    }

    dfs_scan_iterator<T> end_in_order() {
        return dfs_scan_iterator<T>(nullptr);
    }

    dfs_scan_iterator<T> begin_pre_order() {
        return dfs_scan_iterator<T>(this->root);
    }

    dfs_scan_iterator<T> end_pre_order() {
        return dfs_scan_iterator<T>(nullptr);
    }

    dfs_scan_iterator<T> begin_post_order() {
        return dfs_scan_iterator<T>(this->root);
    }

    dfs_scan_iterator<T> end_post_order() {
        return dfs_scan_iterator<T>(nullptr);
    }
};

/**
 * A specialization for K = 2, which change the iterators.
 */
template <typename T>
class Tree<T, 2> : public BaseTree<T, 2> {
   public:
    in_order_iterator<T> begin_in_order() {
        return in_order_iterator<T>(this->root);
    }

    in_order_iterator<T> end_in_order() {
        return in_order_iterator<T>(nullptr);
    }

    pre_order_iterator<T> begin_pre_order() {
        return pre_order_iterator<T>(this->root);
    }

    pre_order_iterator<T> end_pre_order() {
        return pre_order_iterator<T>(nullptr);
    }

    post_order_iterator<T> begin_post_order() {
        return post_order_iterator<T>(this->root);
    }

    post_order_iterator<T> end_post_order() {
        return post_order_iterator<T>(nullptr);
    }

    make_heap_iterator<T> begin_make_heap() {
        return make_heap_iterator<T>(this->root);
    }

    make_heap_iterator<T> end_make_heap() {
        return make_heap_iterator<T>(nullptr);
    }
};