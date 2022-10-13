//
// Created by Alexander Allis on 10/10/22.
//

#include "adjacency_list.h"
#include "LinkedList.h"

std::vector<LinkedList> makeAdjacencyList(const std::vector<std::pair<int, int>>& pairs) {


    unsigned int listSize = pairs.size();
    int index;

    //Get max value in pairs
    int max = 0;
    for(int i = 0; i < listSize; i++) {
        if(pairs.at(i).first > max) max = pairs.at(i).first;
        if(pairs.at(i).second > max) max = pairs.at(i).second;
    }

    std::vector<LinkedList> adjList(max + 1);

    for(int i = 0; i < listSize; i++) {
        index = pairs.at(i).first;
        adjList.at(index).add(pairs.at(i).second);
    }

    return adjList;

}