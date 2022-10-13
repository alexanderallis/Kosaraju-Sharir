//
// Created by Alexander Allis on 10/11/22.
//
#ifndef KOSARAJU_SHARIR_ALGOKS_H
#define KOSARAJU_SHARIR_ALGOKS_H

#include "LinkedList.h"
#include "Stack.h"

Stack * getReversePostorder(std::vector<LinkedList>, int);

int dfsPostorder(std::vector<LinkedList> &tree, Stack *topologicalOrder, bool *explored, int root);

std::vector<LinkedList> * dfsSearch(std::vector<LinkedList> &, Stack *, int);

LinkedList * dfsConnections(std::vector<LinkedList> &, Stack *, LinkedList *, bool *, int);

std::vector<std::pair<int, int>> getPairsOfGReverse(std::vector<std::pair<int, int>> &);

#endif //KOSARAJU_SHARIR_ALGOKS_H
