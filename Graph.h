#ifndef WORDLADDER_GRAPH_H
#define WORDLADDER_GRAPH_H

#include <map>
#include <stdexcept>
#include <iostream>
#include <queue>
#include <set>

template<typename T>
class Graph {
    /*
     * This class represents a graph using an adjacency list representation.
     */
private:
    std::vector<T> vertices;
    std::map<T, std::vector<T>>adjacencyList;
    std::map<T, int> verticesIndex;

public:


    Graph() = default;

    void addVertex(T newVertex) {
        /*
         * This function adds a vertex to the graph.
         * in: name-the name of the vertex to be added
         * out: -
         */
        if (std::count(vertices.begin(), vertices.end(), newVertex) != 0)
            throw std::invalid_argument("The vertex is already in the graph!");
        vertices.push_back(newVertex);
        verticesIndex[newVertex] = vertices.size() - 1;
    }

    int getPosition(T vertex) const {
        if (std::count(vertices.begin(), vertices.end(), vertex) == 0)
            throw std::invalid_argument("The vertex is not in the graph!");
        return verticesIndex.at(vertex);
    }

    void addEdge(T initialVertex, T terminalVertex) {
        /*
         * This function adds an edge to the graph.
         * in: initialVertex-the initial vertex of the edge to be added
         *     terminalVertex-the terminal vertex of the edge to be added
         * out: -
         */
        if (std::count(vertices.begin(), vertices.end(), initialVertex) != 1)
            throw std::invalid_argument("The initial vertex is not in the graph!");
        if (std::count(vertices.begin(), vertices.end(), terminalVertex) != 1)
            throw std::invalid_argument("The terminal vertex is not in the graph!");

        adjacencyList[initialVertex].push_back(terminalVertex);
        adjacencyList[terminalVertex].push_back(initialVertex);
    }

    std::vector<T> getNeighbours(T vertex) {
        /*
         * This function returns the neighbours of a vertex.
         * in: vertex-the vertex whose neighbours are to be returned
         * out: neighboursOfVertex-the neighbours of the vertex
         */
        if (std::count(vertices.begin(), vertices.end(), vertex) == 0)
            throw std::invalid_argument("The vertex is not in the graph!");

        return adjacencyList.at(vertex);
    }

    bool checkVertex(const T& vertex) {
        if (std::find(vertices.begin(), vertices.end(), vertex) != vertices.end())
            return true;
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const Graph<T> &graph) {
        for (const auto &vertex: graph.vertices) {
            os << vertex << ": ";
            std::vector<T> neighboursOfVertex = graph.getNeighbours(vertex);
            for (const auto &neighbour: neighboursOfVertex) {
                os << neighbour << ' ';
            }
            os << '\n';
        }
        return os;
    }

    int getNumberOfVertices() {
        return vertices.size();
    }

    int getNumberOfEdges() {
        int edges = 0;
        for (const auto &vertex: vertices) {
            std::vector<T> neighboursOfVertex = getNeighbours(vertex);
            edges += neighboursOfVertex.size();
        }
        return edges / 2;
    }

    std::vector<T> BFS(T startNode, T finishNode) {
//        if (std::count(vertices.begin(), vertices.end(), startNode) == 0)
//            throw std::invalid_argument("The start vertex is not in the graph!");
//        if (std::count(vertices.begin(), vertices.end(), finishNode) == 0)
//            throw std::invalid_argument("The finish vertex is not in the graph!");
//        std::queue<T> queue;
//        std::set<T> visited;
//        std::map<T, T> previous;
//        queue.push(startNode);
//        previous[startNode] = startNode;
//        while (!queue.empty() and (visited.find(finishNode) == visited.end())) {
//            T current = queue.front();
//            queue.pop();
//            visited.insert(current);
//            std::vector<T> neighbours = getNeighbours(current);
//            for (auto node : neighbours)
//                if (visited.find(node) == visited.end()){
//                    queue.push(node);
//                    previous[node] = current;
//                }
//        }
//        std::vector<T> path;
//        T at = finishNode;
//        while (at != startNode) {
//            path.push_back(at);
//            at = previous[at];
//        }
//        path.push_back(startNode);
//        std::reverse(path.begin(), path.end());
//        return path;


        if (std::find(vertices.begin(), vertices.end(), startNode) == vertices.end())
            throw std::runtime_error("starting word doesn't exist!\n");
        if(std::find(vertices.begin(), vertices.end(), finishNode) == vertices.end())
            throw std::runtime_error("ending word doesn't exist!\n");

        std::vector<bool>visited(vertices.size(), false);
        std::vector<int>parent(vertices.size());
        std::queue<T>bfsQueue;

        visited[verticesIndex[startNode]] = true;
        parent[verticesIndex[startNode]] = -1;
        bfsQueue.push(startNode);

        bool found = false;
        while(!bfsQueue.empty() && !found) {
            T currentNode = bfsQueue.front();
            bfsQueue.pop();

            for (auto& neighbor: getNeighbours(currentNode))
                if (!visited[verticesIndex[neighbor]]) {
                    visited[verticesIndex[neighbor]] = true;
                    parent[verticesIndex[neighbor]] = verticesIndex[currentNode];
                    bfsQueue.push(neighbor);
                    if (neighbor == finishNode) {
                        found = true;
                    }
                }
        }
        std::vector<std::string> path;
        if (found == true) {
            int current = verticesIndex[finishNode];
            while(current != -1) {
                path.push_back(vertices[current]);
                current = parent[current];
            }
            std::reverse(path.begin(), path.end());
        }
        return path;
    }

};
#endif
