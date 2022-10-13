//
// Created by Alexander Allis on 10/11/22.
//
#include <string>
#include "AlgoKS.h"
#include "LinkedList.h"
#include "Stack.h"

Stack * getReversePostorder(std::vector<LinkedList> tree, const int numberOfVertices) {

    auto * topologicalOrder = new Stack;
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

std::vector<LinkedList> * dfsSearch(std::vector<LinkedList> & tree, Stack * topologicalOrder, int numberOfVertices) {

    auto * connectedCmptsList = new std::vector<LinkedList>;
//    int idList[numberOfVertices];
    bool* explored = new bool[numberOfVertices]();
    for(int i = 0; i < numberOfVertices; i++) {
        explored[i] = false;
    }

    int root, parent;

    while(!topologicalOrder -> isEmpty()) {
        parent = topologicalOrder -> pop();
        if(!explored[parent]) {
            auto * idList = new LinkedList;
            connectedCmptsList -> push_back(*dfsConnections(tree, topologicalOrder, idList, explored, parent));
//            dfsConnections(tree, topologicalOrder, idList, parent, numOfConnectedCompts);  // modifies idList in place
        }
    }

    return connectedCmptsList;

}

LinkedList * dfsConnections(std::vector<LinkedList> & tree, Stack * topologicalOrder, LinkedList * idList, bool * explored, int root) {

    //mark u as explored and add u to r
    idList -> add(root);
    explored[root] = true;
//    idList[root] = parent;
    int root2;
    // for each edge (u,v) incident to u
    while(!tree.at(root).isEnd()) {
        // If v is not marked "explored" then
        root2 = tree.at(root).pop();
        if(!explored[root2]) {
            // recursively invoke getReversePostorder(v)
            dfsConnections(tree, topologicalOrder, idList, explored, root2);
//            explored[root2] = true;
        }
    }

    return idList;

}

std::vector<std::pair<int, int>> getPairsOfGReverse(std::vector<std::pair<int, int>> & g) {

    std::vector<std::pair<int, int>> gR;

    for(int i = 0; i < g.size(); i++) {
        gR.emplace_back(g.at(i).second, g.at(i).first);
    }

    return gR;

}
