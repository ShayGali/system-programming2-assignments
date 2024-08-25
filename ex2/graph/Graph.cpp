/**
 * @author Shay Gali
 * @link shay.gali@msmail.ariel.ac.il
 */
#include "Graph.hpp"

#include <iostream>
#include <stdexcept>

using namespace shayg;

using std::invalid_argument;

void Graph::loadGraph(const vector<vector<int>>& adjMat) {
    this->adjMat = adjMat;
    /*
     * update the isWeighted and haveNegativeEdgeWeight fields.
     * create an deep copy of the adjacency list.
     */

    // check if the graph is a square matrix
    // check if the diagonal of the matrix is 0
    for (size_t i = 0; i < adjMat.size(); i++) {
        if (adjMat.size() != adjMat[i].size()) {
            throw invalid_argument("Invalid graph: The graph is not a square matrix.(" + std::to_string(i) + "th row has " + std::to_string(adjMat[i].size()) + " elements.)");
        }
        if (adjMat[i][i] != NO_EDGE) {
            throw invalid_argument("The diagonal of the matrix must be NO_EDGE. (the " + std::to_string(i) + "th node is not a NO_EDGE)");
        }
    }

    updateData();
}

void Graph::printGraph(std::ostream& out) const {
    if (this->isDirected) {
        out << "Directed graph with " << getNumVertices() << " vertices and " << getNumEdges() << " edges." << std::endl;
    } else {
        out << "Undirected graph with " << getNumVertices() << " vertices and " << getNumEdges() << " edges." << std::endl;
    }
}

void Graph::printAdjMat(std::ostream& out) const {
    for (size_t i = 0; i < getNumVertices() - 1; i++) {
        out << "[";
        for (size_t j = 0; j < getNumVertices() - 1; j++) {
            if (adjMat[i][j] != NO_EDGE) {
                out << adjMat[i][j] << ", ";
            } else {
                out << "X, ";
            }
        }
        if (adjMat[i][getNumVertices() - 1] != NO_EDGE) {
            out << adjMat[i][getNumVertices() - 1] << "]," << '\n';
        } else {
            out << "X]," << '\n';
        }
    }

    out << "[";
    for (size_t j = 0; j < getNumVertices() - 1; j++) {
        if (adjMat[getNumVertices() - 1][j] != NO_EDGE) {
            out << adjMat[getNumVertices() - 1][j] << ", ";
        } else {
            out << "X, ";
        }
    }
    if (adjMat[getNumVertices() - 1][getNumVertices() - 1] != NO_EDGE) {
        out << adjMat[getNumVertices() - 1][getNumVertices() - 1] << "]";
    } else {
        out << "X]";
    }
}

void Graph::updateData() {
    this->isDirected = false;
    this->isWeighted = false;
    this->haveNegativeEdgeWeight = false;
    this->numEdges = 0;

    for (size_t i = 0; i < getNumVertices(); i++) {
        for (size_t j = 0; j < getNumVertices(); j++) {
            if (adjMat[i][j] != NO_EDGE) {
                this->numEdges++;

                if (adjMat[i][j] != 1) {
                    this->isWeighted = true;
                }

                if (adjMat[i][j] < 0) {
                    this->haveNegativeEdgeWeight = true;
                }

                if (adjMat[i][j] != adjMat[j][i]) {
                    this->isDirected = true;
                }
            }
        }
    }

    if (!this->isDirected) {
        this->numEdges /= 2;
    }
}

// ~~~ helper functions for the operators ~~~

void Graph::modifyEdgeWeights(const function<int(int)>& func) {
    for (size_t u = 0; u < getNumVertices(); u++) {
        for (size_t v = 0; v < getNumVertices(); v++) {
            if (adjMat[u][v] != NO_EDGE) {
                int res = func(adjMat[u][v]);
                if (res == 0) {
                    adjMat[u][v] = NO_EDGE;
                } else {
                    adjMat[u][v] = res;
                }
            }
        }
    }

    updateData();
}

void Graph::modifyEdgeWeights(const Graph& other, const function<int(int, int)>& func) {
    if (this->getNumVertices() != other.getNumVertices()) {
        throw std::invalid_argument("The two graphs have different number of vertices.");
    }

    for (size_t u = 0; u < getNumVertices(); u++) {
        for (size_t v = 0; v < getNumVertices(); v++) {
            if (adjMat[u][v] == NO_EDGE && other.adjMat[u][v] == NO_EDGE) {  // if they are both NO_EDGE - the result edge is NO_EDGE
                adjMat[u][v] = NO_EDGE;
            } else if (adjMat[u][v] == NO_EDGE && other.adjMat[u][v] != NO_EDGE) {  // if one of them is NO_EDGE - the result edge is the other one
                adjMat[u][v] = func(0, other.adjMat[u][v]);
            } else if (adjMat[u][v] != NO_EDGE && other.adjMat[u][v] == NO_EDGE) {
                adjMat[u][v] = func(adjMat[u][v], 0);
            } else {  // if they are both not NO_EDGE - the result edge is the result of the operation
                int res = func(adjMat[u][v], other.adjMat[u][v]);
                if (res == 0 || res == NO_EDGE) {  // if the result is 0 or NO_EDGE - the result edge is NO_EDGE
                    adjMat[u][v] = NO_EDGE;
                } else {
                    adjMat[u][v] = res;
                }
            }
        }
    }

    updateData();
}

bool isSubMatrix(const vector<vector<int>>& subMatrix, const vector<vector<int>>& matrix) {
    if (subMatrix.size() > matrix.size()) {
        return false;
    }

    for (size_t i = 0; i <= matrix.size() - subMatrix.size(); i++) {
        for (size_t j = 0; j <= matrix.size() - subMatrix.size(); j++) {
            bool match = true;
            for (size_t k = 0; k < subMatrix.size(); k++) {
                for (size_t l = 0; l < subMatrix.size(); l++) {
                    if (subMatrix[k][l] != matrix[i + k][j + l]) {
                        match = false;
                        break;
                    }
                }
                if (!match) {
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
    }
    return false;
}

bool matrixEqual(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2) {
    if (mat1.size() != mat2.size()) {
        return false;
    }

    for (size_t i = 0; i < mat1.size(); i++) {
        for (size_t j = 0; j < mat1[i].size(); j++) {
            if (mat1[i][j] != mat2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// ~~~~ operators ~~~~

Graph Graph::operator*(const Graph& other) const {
    if (this->getNumVertices() != other.getNumVertices()) {
        throw std::invalid_argument("The two graphs have different number of vertices.");
    }

    Graph g = *this;

    // do matrix multiplication on the adjacency matrices
    // adjList[i][j] = sum(adjList[i][k] * adjList[k][j]) for all k
    // the diagonal of the matrix must be NO_EDGE
    for (size_t i = 0; i < getNumVertices(); i++) {
        for (size_t j = 0; j < getNumVertices(); j++) {
            if (i == j) {  // the diagonal of the matrix must be NO_EDGE
                continue;
            }
            int sum = 0;
            for (size_t k = 0; k < getNumVertices(); k++) {
                if (adjMat[i][k] != NO_EDGE && other.adjMat[k][j] != NO_EDGE) {
                    sum += adjMat[i][k] * other.adjMat[k][j];
                }
            }
            if (sum != 0) {
                g.adjMat[i][j] = sum;
            } else {
                g.adjMat[i][j] = NO_EDGE;
            }
        }
    }

    g.updateData();
    return g;
}

bool Graph::operator<(const Graph& other) const {
    // if they both empty graphs (no vertices and edges) return false
    if (this->adjMat.empty() && other.adjMat.empty()) {
        return false;
    }

    // if the current graph is empty and the other graph is not empty, return true (A is submatrix of B)
    if (this->adjMat.empty()) {
        return true;
    }

    // if the other graph is empty and the current graph is not empty, return false
    if (other.adjMat.empty()) {
        return false;
    }

    // if the two graphs have the same adjacency matrix, return false
    if (this->adjMat == other.adjMat) {
        return false;
    }

    // check if the adjacency matrix of the current graph is submatrix of the adjacency matrix of the other graph
    if (isSubMatrix(this->adjMat, other.adjMat)) {
        return true;
    }

    if (isSubMatrix(other.adjMat, this->adjMat)) {
        return false;
    }

    // A is not a submatrix of B - check the number of edges

    // compare the number of edges
    size_t edgeA = this->getNumEdges();
    size_t edgeB = other.getNumEdges();

    if (edgeA < edgeB) {
        return true;
    }

    if (edgeA > edgeB) {
        return false;
    }

    // if the number of edges is the same
    return getNumVertices() < other.getNumVertices();
}

std::ostream& shayg::operator<<(std::ostream& os, const Graph& graph) {  //~~~ the shayg:: is needed because the operator is defined in the shayg namespace ~~~//
    // graph.printGraph(os);
    graph.printAdjMat(os);
    return os;
}