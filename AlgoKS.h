//
// Created by Alexander Allis on 10/11/22.
//
#ifndef KOSARAJU_SHARIR_ALGOKS_H
#define KOSARAJU_SHARIR_ALGOKS_H

#include "LinkedList.h"
#include "Stack.h"

Stack * getReversePostorder(std::vector<LinkedList>, int);

int dfsPostorder(std::vector<LinkedList> &graph, Stack *reversePostorder, bool *isExplored, int root);

int dfsSearchByRevPostorder(std::vector<LinkedList> &graph, Stack *reversePostorder, std::vector<LinkedList> *connectedCmptsList, int *idList, int numberOfVertices, std::vector<std::pair<int, int>> &kernelEdges);

LinkedList * dfsConnections(std::vector<LinkedList> &, Stack *, LinkedList *, int *, bool *, int, int, std::vector<std::pair<int, int>> &, bool *);

std::vector<std::pair<int, int>> getPairsOfGReverse(std::vector<std::pair<int, int>> &);

#endif //KOSARAJU_SHARIR_ALGOKS_H
