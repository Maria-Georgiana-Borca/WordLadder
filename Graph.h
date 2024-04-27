#ifndef WORDLADDER_GRAPH_H
#define WORDLADDER_GRAPH_H

#include <map>
#include <stdexcept>
#include <iostream>

template<typename T>
class Graph {
    /*
     * This class represents a graph using an adjacency list representation.
     */
private:
    std::vector<T> vertices;
    std::multimap<T, T> neighbours;

public:

    void addVertex(T name) {
        /*
         * This function adds a vertex to the graph.
         * in: name-the name of the vertex to be added
         * out: -
         */
        int counter = std::count(vertices.begin(), vertices.end(), name);
        if (counter == 0)
            vertices.push_back(name);
        else throw std::invalid_argument("The vertex is already in the graph!");
    }

    void addEdge(T initialVertex, T terminalVertex) {
        /*
         * This function adds an edge to the graph.
         * in: initialVertex-the initial vertex of the edge to be added
         *     terminalVertex-the terminal vertex of the edge to be added
         * out: -
         */

        int counterForInitial = std::count(vertices.begin(), vertices.end(), initialVertex);
        int counterForTerminal = std::count(vertices.begin(), vertices.end(), terminalVertex);
        if (counterForInitial != 1)
            throw std::invalid_argument("The initial vertex is not in the graph!");
        if (counterForTerminal != 1)
            throw std::invalid_argument("The terminal vertex is not in the graph!");

        neighbours.insert(std::pair<T, T>(initialVertex, terminalVertex));
        neighbours.insert(std::pair<T, T>(terminalVertex, initialVertex));
    }

     std::vector<T> getNeighbours(T vertex) const {
        /*
         * This function returns the neighbours of a vertex.
         * in: vertex-the vertex whose neighbours are to be returned
         * out: neighboursOfVertex-the neighbours of the vertex
         */
        std::vector<T> neighboursOfVertex;
        for (auto it = neighbours.begin(); it != neighbours.end(); it++)
            if (it->first == vertex)
                neighboursOfVertex.push_back(it->second);
        return neighboursOfVertex;
    }

    friend std::ostream &operator<<(std::ostream &os, const Graph<T> &graph) {
        for (int i = 0; i < graph.vertices.size(); i++) {
            std::cout << graph.vertices[i] << ": ";
            std::vector<T> neighboursOfVertex = graph.getNeighbours(graph.vertices[i]);
            for (int j = 0; j < neighboursOfVertex.size(); j++)
                std:: cout << neighboursOfVertex[j] << ' ';
            std::cout << '\n';
        }
        return os;
    }

};


#endif
