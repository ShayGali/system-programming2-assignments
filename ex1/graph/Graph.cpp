/**
 * @author Shay Gali
 * @link shay.gali@msmail.ariel.ac.il
 */
#include "Graph.hpp"

#include <iostream>
#include <stdexcept>

using namespace shayg;

using std::invalid_argument;

Graph::Graph(bool isDirected) {
    this->isDirected = isDirected;

    // by default, the graph is not weighted and does not have negative edge weight
    // will be updated in the loadGraph method
    this->isWeighted = false;
    this->haveNegativeEdgeWeight = false;
}

void Graph::loadGraph(const vector<vector<int>> &ajdList) {

    // by default, the graph is not weighted and does not have negative edge weight
    this->isWeighted = false;
    this->haveNegativeEdgeWeight = false;

    this->ajdList = ajdList;
    /*
     * update the isWeighted and haveNegativeEdgeWeight fields.
     * create an deep copy of the adjacency list.
     */

    // check if the graph is a square matrix
    // check if the diagonal of the matrix is 0
    for (size_t i = 0; i < ajdList.size(); i++) {
        if (ajdList.size() != ajdList[i].size()) {
            throw invalid_argument("Invalid graph: The graph is not a square matrix.(" + std::to_string(i) + "th row has " + std::to_string(ajdList[i].size()) + " elements.)");
        }
        if (ajdList[i][i] != NO_EDGE) {
            throw invalid_argument("The diagonal of the matrix must be NO_EDGE. (the " + std::to_string(i) + "th node is not a NO_EDGE)");
        }

    }

    // update the isWeighted and haveNegativeEdgeWeight fields if needed
    // check if a directed graph is a symmetric matrix
    for (size_t i = 0; i < ajdList.size(); i++) {
        for (size_t j = 0; j < ajdList[i].size(); j++) {
            if (ajdList[i][j] != NO_EDGE) {
                if (ajdList[i][j] != 1) {
                    this->isWeighted = true;
                }
                if (ajdList[i][j] < 0) {
                    this->haveNegativeEdgeWeight = true;
                }
            }

            if (!this->isDirected && ajdList[i][j] != ajdList[j][i]) {
                throw invalid_argument("Invalid graph: The graph is not symmetric.(mat[" + std::to_string(i) + "][" + std::to_string(j) + "] = " + std::to_string(ajdList[i][j]) + " and mat[" + std::to_string(j) + "][" + std::to_string(i) + "] = " + std::to_string(ajdList[j][i]) + ")");
            }
        }
    }
}

void Graph::printGraph() const {
    int count_edges = 0;
    for (size_t i = 0; i < ajdList.size(); i++) {
        for (size_t j = 0; j < ajdList[i].size(); j++) {
            if (ajdList[i][j] != NO_EDGE) {
                count_edges++;
            }
        }
    }
    if (this->isDirected) {
        std::cout << "Directed graph with " << ajdList.size() << " vertices and " << count_edges << " edges." << std::endl;
    } else {
        std::cout << "Undirected graph with " << ajdList.size() << " vertices and " << count_edges / 2 << " edges." << std::endl;
    }
}

vector<vector<int>> Graph::getGraph() const { return this->ajdList; }

bool Graph::isDirectedGraph() const { return this->isDirected; }
bool Graph::isWeightedGraph() const { return this->isWeighted; }

bool Graph::isHaveNegativeEdgeWeight() const { return this->haveNegativeEdgeWeight; }