//
// Created by Alexander Allis on 10/11/22.
//
#include <string>
#include "AlgoKS.h"
#include "LinkedList.h"
#include "Stack.h"

Stack * getReversePostorder(std::vector<LinkedList> tree, const int numberOfVertices) {

    auto * topologicalOrder = new Stack(numberOfVertices);
    bool explored[numberOfVertices];
    for(int i = 0; i < numberOfVertices; i++) {
        explored[i] = false;
    }
    for(int i = 0; i < numberOfVertices; i++) {
        if(!explored[i]) {
            dfsPostorder(tree, topologicalOrder, explored, i);
        }
    }

    return topologicalOrder;
}

int dfsPostorder(std::vector<LinkedList> & tree, Stack * topologicalOrder, bool * explored, int root) {

    //mark u as explored and add u to r
    explored[root] = true;
    int root2;
    // for each edge (u,v) incident to u
    while(!tree.at(root).isEnd()) {
        // If v is not marked "explored" then
        root2 = tree.at(root).pop();
        if(!explored[root2]) {
            // recursively invoke getReversePostorder(v)
//            topologicalOrder -> push(dfsPostorder(tree, topologicalOrder, explored, root2));
            dfsPostorder(tree, topologicalOrder, explored, root2);
//            explored[root] = true;
        }
    }
    topologicalOrder -> push(root);
    return root;

}

int dfsSearch(std::vector<LinkedList> & tree, Stack * topologicalOrder, std::vector<LinkedList> * connectedCmptsList, int * idList, int numberOfVertices, std::vector<std::pair<int, int>> & kernelPairs) {

    int parent;
    int idCounter = 0;
//    auto * idList = new int[numberOfVertices];
//    auto * connectedCmptsList = new std::vector<LinkedList>;
    bool* explored = new bool[numberOfVertices]();
    for(int i = 0; i < numberOfVertices; i++) {
        explored[i] = false;
    }

    while(!topologicalOrder -> isEmpty()) {
        parent = topologicalOrder -> pop();
        if(!explored[parent]) {
            auto * connectionList = new LinkedList;
            connectedCmptsList -> push_back(*dfsConnections(tree, topologicalOrder, connectionList, idList, explored, parent, idCounter, kernelPairs));
            idCounter++;
        }
    }

    return 0;

}

LinkedList * dfsConnections(std::vector<LinkedList> & tree, Stack * topologicalOrder, LinkedList * connectionList, int * idList, bool * explored, int root, int idCounter, std::vector<std::pair<int, int>> & kernelPairs) {

    //mark u as explored and add u to r
    connectionList -> add(root);
    idList[root] = idCounter;
    explored[root] = true;
    int root2;
    // for each edge (u,v) incident to u
    while(!tree.at(root).isEnd()) {
        // If v is not marked "explored" then
        root2 = tree.at(root).pop();
        if(!explored[root2]) {
            // recursively invoke
            dfsConnections(tree, topologicalOrder, connectionList, idList, explored, root2, idCounter, kernelPairs);
        }
        else {  // add to kernel
            if(idList[root2] != idCounter) {
                kernelPairs.emplace_back(idCounter, idList[root2]);
            }

        }
    }
    tree.at(root).reset();  // clean up for future use
    return connectionList;

}

std::vector<std::pair<int, int>> getPairsOfGReverse(std::vector<std::pair<int, int>> & g) {

    std::vector<std::pair<int, int>> gR;
    gR.reserve(g.size());

    for(auto & i : g) {
        gR.emplace_back(i.second, i.first);
    }

    return gR;

}
