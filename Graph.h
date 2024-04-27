#ifndef WORDLADDER_GRAPH_H
#define WORDLADDER_GRAPH_H

#include <map>
#include <stdexcept>
#include <iostream>
#include <list>

template<typename T>
class Graph {
    /*
     * This class represents a graph using an adjacency list representation.
     */
private:
    std::vector<T> vertices;
    std::vector<std::list<T>> adjacencyLists;
    std::map<T, int> vertexIndexMap;

public:

    void addVertex(T name) {
        /*
         * This function adds a vertex to the graph.
         * in: name-the name of the vertex to be added
         * out: -
         */
        if (std::count(vertices.begin(), vertices.end(), name) == 0) {
            vertices.push_back(name);
            adjacencyLists.push_back(std::list<T>());
            vertexIndexMap[name] = vertices.size() - 1;
        } else throw std::invalid_argument("The vertex is already in the graph!");
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

        adjacencyLists[vertexIndexMap[initialVertex]].push_back(terminalVertex);
        adjacencyLists[vertexIndexMap[terminalVertex]].push_back(initialVertex);
    }

    std::list<T> getNeighbours(T vertex) const {
        /*
         * This function returns the neighbours of a vertex.
         * in: vertex-the vertex whose neighbours are to be returned
         * out: neighboursOfVertex-the neighbours of the vertex
         */
        if (std::count(vertices.begin(), vertices.end(), vertex) != 1)
            throw std::invalid_argument("The vertex is not in the graph!");
        return adjacencyLists[vertexIndexMap.at(vertex)];
    }

    friend std::ostream &operator<<(std::ostream &os, const Graph<T> &graph) {
        for (const auto &vertex: graph.vertices) {
            os << vertex << ": ";
            std::list<T> neighboursOfVertex = graph.getNeighbours(vertex);
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
            std::list<T> neighboursOfVertex = getNeighbours(vertex);
            edges += neighboursOfVertex.size();
        }
        return edges / 2;
    }

};


#endif
