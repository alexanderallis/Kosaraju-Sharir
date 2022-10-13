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

    std::vector<LinkedList> * idList = dfsSearch(tree, topologicalOrder, numberOfVertices);

    // OUTPUT - BASIC
    unsigned int numStronglyConnCmpts = idList -> size();
    std::cout << "The graph has " << numStronglyConnCmpts << " Strongly Connected Components." << std::endl;
    for(int i = 0; i < numStronglyConnCmpts; i++) {
        std::cout << "Strongly Connected Component #" << i << ": ";
        while(!idList -> at(i).isEnd()) {
            std::cout << idList -> at(i).pop();
            if(idList -> at(i).isEnd()) {
                std::cout << ". " << std::endl;
            }
            else {
                std::cout << ", ";
            }
        }
    }

    // OUTPUT - KERNEL


    return 0;
}
