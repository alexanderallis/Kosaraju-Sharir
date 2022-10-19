#include <iostream>
#include <vector>
#include <utility>

#include "read_file.h"
#include "adjacency_list.h"
#include "AlgoKS.h"

/*
 *  Alexander Allis
 *  Kosaraju-Shrarir Algorithm
 *  This program determines the strongly connected components in a tree
 *  and returns a list of the strongly connected components with their kernel graph.
 *
 *  To Compile:
 *  Run "cmake ." in root directory
 *  Run "make"
 *  Run "./Gale_Shapely [Program Type] [Male Preferences] [Female Preferences] [Output File]"
 *
 *  To Run:
 *  [# of vertices]
 *  [# of edges]
 *  [a1 b1]
 *  ...
 *  [an bn]
 *
 *  The edges go from ax -> bx
 */

int main() {

    std::vector<std::pair<int, int>> pairs;
    int numberOfVertices = 0;
    int numberOfEdges = 0;

    // read file
    readFile("input.txt", pairs, numberOfVertices, numberOfEdges);
    getPairsFromStdIn(pairs, numberOfVertices, numberOfEdges);
    std::vector<std::pair<int, int>> reversePairs = getPairsOfGReverse(pairs);

    // construct tree
    std::vector<LinkedList> tree = makeAdjacencyList(pairs, numberOfVertices);
    std::vector<LinkedList> treeReverse = makeAdjacencyList(reversePairs, numberOfVertices);

    // K-S Algorithm
    Stack * reversePostorder = getReversePostorder(treeReverse, numberOfVertices);
    auto * connectedCmptsList = new std::vector<LinkedList>;
    auto * idList = new int[numberOfVertices] {0};
    std::vector<std::pair<int, int>> kernelGraph;
    dfsSearchByRevPostorder(tree, reversePostorder, connectedCmptsList, idList, numberOfVertices, kernelGraph);
    // End K-S Algorithm

    // OUTPUT - STRONGLY CONNECTED COMPONENTS
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

    // OUTPUT - KERNEL GRAPH
    std::cout << std::endl << "Kernel Graph" << std::endl;
    std::cout << connectedCmptsList->size() << std::endl;
    std::cout << kernelGraph.size() << std::endl;
    for(auto & i : kernelGraph) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    return 0;
}
