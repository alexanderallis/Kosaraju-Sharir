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

    // K-S Algorithm
    Stack * topologicalOrder = getReversePostorder(treeReverse, numberOfVertices);
    auto * connectedCmptsList = new std::vector<LinkedList>;
    auto * idList = new int[numberOfVertices];
    std::vector<std::pair<int, int>> kernelGraph;
    dfsSearch(tree, topologicalOrder, connectedCmptsList, idList, numberOfVertices, kernelGraph);
    // End K-S Algorithm

    // OUTPUT - BASIC
    unsigned int numStronglyConnCmpts = connectedCmptsList -> size();
    std::cout << "The graph has " << numStronglyConnCmpts << " Strongly Connected Components." << std::endl;
    for(int i = 0; i < numStronglyConnCmpts; i++) {
        std::cout << "Strongly Connected Component #" << i << ": ";
        while(!connectedCmptsList -> at(i).isEnd()) {
            std::cout << connectedCmptsList -> at(i).pop();
            if(connectedCmptsList -> at(i).isEnd()) {
                std::cout << ". " << std::endl;
            }
            else {
                std::cout << ", ";
            }
        }
        connectedCmptsList -> at(i).reset();  // reset Linked list pointer to head for further use.
    }

    // OUTPUT - KERNEL
    std::cout << std::endl << "Kernel Graph" << std::endl;
    std::cout << connectedCmptsList->size() << std::endl;
    std::cout << kernelGraph.size() << std::endl;
    for(auto & i : kernelGraph) {
        std::cout << i.first << ", " << i.second << std::endl;
    }

//    int v;
//    int u;
//    int id;
//    unsigned int numConnectedCmpts = connectedCmptsList -> size();
//    bool found = false;
//    std::vector<std::pair<int, int>> kernelPairs;
//
//    for(int i = 0; i < numConnectedCmpts; i++) {
//        while(!connectedCmptsList -> at(i).isEnd()) {
//            v = connectedCmptsList -> at(i).pop();
//            while(!tree.at(v).isEnd()) {
//                u = tree.at(v).pop();
//                id = idList[u];
//                if(i != id) {
//                    for(auto & kernelPair : kernelPairs) {
//                        if(kernelPair.first == i) {
//                            if(kernelPair.second == id) {
//                                found = true;
//                                break; // do nothing if found parallel edge
//                            }
//                        }
//                    }
//                    if(!found) kernelPairs.emplace_back(i, id);
//                }
//            }
//        }
//    }

//    std::cout << std::endl;
//    std::cout << "Kernel Graph" << std::endl;
//    std::cout << connectedCmptsList -> size() << std::endl;
//    std::cout << kernelPairs.size() << std::endl;
//    for(auto & kernelPair : kernelPairs) {
//        std::cout << kernelPair.first << " " << kernelPair.second << std::endl;
//    }

    return 0;
}
