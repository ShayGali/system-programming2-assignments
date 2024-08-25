/**
 * @author Shay Gali
 * @link shay.gali@msmail.ariel.ac.il
*/
#include <algorithm>
#include <iostream>
#include <string>

#include "../graph/Graph.hpp"

using std::string;
namespace shayg {
class Algorithms {
   public:
    /**
     * @brief Check if the graph is connected
     * @param g - the graph to check
     * @return true if the graph is connected, false otherwise
     */
    static bool isConnected(const Graph& g);

    /**
     * @brief Find the shortest path between two vertices
     * @param g - the graph to search in
     * @param src - the source vertex
     * @param dest - the destination vertex
     * @return the shortest path between the source and destination vertices in the format "src->...->dest".
     *  if there is no path between the source and destination vertices, return "-1"
     * @throws NegativeCycleException if the graph contains a negative-weight cycle
     * @throws std::invalid_argument if the source or destination vertices are not in the graph
     */
    static string shortestPath(const Graph& g, size_t src, size_t dest);

    /**
     * @brief Check if the graph contains a cycle. If the graph contains a cycle, return the cycle in the format "v1->v2->...->v1".
     * @param g - the graph to check
     * @return The cycle in the format "v1->v2->...->v1" if the graph contains a cycle. Otherwise, return "-1".
     */
    static string isContainsCycle(const Graph& g);

    /**
     * @brief Check if the graph is bipartite
     * @param g - the graph to check
     * @return If the graph is bipartite, return "The graph is bipartite: A={...}, B={...}". (the ... represents the vertices in the set)
     *     Otherwise, return "The graph is not bipartite".
     */
    static string isBipartite(const Graph& g);

    /**
     * @brief Find the negative cycle in the graph
     * @param g - the graph to search in
     * @return If the graph contains a negative cycle, return the cycle in the format "v1->v2->...->v1".
     *    Otherwise, return "No negative cycle".
     *
     */
    static string negativeCycle(const Graph& g);

    class NegativeCycleException : public std::exception {
       public:
        vector<size_t> cycle;

        NegativeCycleException(size_t detectedCycleStart, vector<int> parentList) {
            int cycleVertices = detectedCycleStart;
            
            // make sure that we in the cycle
            for (size_t i = 0; i < parentList.size(); i++) {
                cycleVertices = parentList[(size_t)cycleVertices];
            }

            vector<size_t> cycle;

            for (size_t v = (size_t)cycleVertices; true; v = (size_t)parentList[v]) {
                cycle.push_back(v);
                if (v == cycleVertices && cycle.size() > 1) {
                    break;
                }
            }

            reverse(cycle.begin(), cycle.end());

            this->cycle = cycle;
        }

        virtual const char* what() const throw() {
            return "Graph contains a negative-weight cycle";
        }
    };
};
}  // namespace shayg