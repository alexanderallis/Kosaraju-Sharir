//
// Created by Alexander Allis on 10/10/22.
//

#include "adjacency_list.h"
#include "LinkedList.h"

/*
 * Makes an adjacency list of the graph from a list of pairs.
 * Args:
 *  pairs: a list of edges
 *  numberOfVertices
 * Returns: an adjacency list of the graph
 */
std::vector<LinkedList> makeAdjacencyList(const std::vector<std::pair<int, int>>& pairs, int numberOfVertices) {


    unsigned int listSize = pairs.size();
    int index;

    //Get max value in pairs
    int max = 0;
    for(int i = 0; i < listSize; i++) {
        if(pairs.at(i).first > max) max = pairs.at(i).first;
        if(pairs.at(i).second > max) max = pairs.at(i).second;
    }

    std::vector<LinkedList> adjList(numberOfVertices);

    for(const auto & pair : pairs) {
        index = pair.first;
        adjList.at(index).add(pair.second);
    }

    return adjList;

}