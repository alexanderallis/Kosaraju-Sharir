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

int * dfsSearch(std::vector<LinkedList> & tree, Stack * topologicalOrder, int numberOfVertices) {

//    int idList[numberOfVertices];
    int* idList = new int[numberOfVertices]();
    for(int i = 0; i < numberOfVertices; i++) {
        idList[i] = -1;
    }

    int root, parent;

    while(!topologicalOrder -> isEmpty()) {
        parent = topologicalOrder -> pop();
        if(idList[parent] == -1) {
            dfsConnections(tree, topologicalOrder, idList, parent, parent);  // modifies idList in place
        }
    }

    return idList;

}

int * dfsConnections(std::vector<LinkedList> & tree, Stack * topologicalOrder, int * idList, int root, const int parent) {

    //mark u as explored and add u to r
    idList[root] = parent;
    int root2;
    // for each edge (u,v) incident to u
    while(!tree.at(root).isEnd()) {
        // If v is not marked "explored" then
        root2 = tree.at(root).pop();
        if(idList[root2] == -1) {
            // recursively invoke getReversePostorder(v)
            dfsConnections(tree, topologicalOrder, idList, root2, parent);
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
