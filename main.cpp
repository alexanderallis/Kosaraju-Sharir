#include <iostream>
#include <vector>
#include "read_file.h"
#include "adjacency_list.h"
#include "AlgoKS.h"

int main() {

    std::vector<std::pair<int, int>> pairs;

    int numberOfVertices;
    int numberOfEdges;

    readFile("input.txt", pairs, numberOfVertices, numberOfEdges);

    std::vector<std::pair<int, int>> reversePairs = getPairsOfGReverse(pairs);

    std::vector<LinkedList> tree = makeAdjacencyList(pairs);
    std::vector<LinkedList> treeReverse = makeAdjacencyList(reversePairs);

    Stack * topologicalOrder = getReversePostorder(treeReverse, numberOfVertices);

    int * idList = dfsSearch(tree, topologicalOrder, numberOfVertices);

    return 0;
}
