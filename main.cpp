#include <iostream>
#include <vector>
#include <sstream>
#include <utility>

#include "adjacency_list.h"
#include "AlgoKS.h"

int main() {

    std::vector<std::pair<int, int>> pairs;

//    int numberOfVertices;
//    int numberOfEdges;
//    readFile("input.txt", pairs, numberOfVertices, numberOfEdges);

    // Get input from stdin
    std::string input;
    std::string line;
    getline(std::cin, line);  // get vertices
    int numberOfVertices = stoi(line);
    getline(std::cin, line);  // get edges
    int numberOfEdges = stoi(line);

    std::stringstream sStream;
    std::string vectorA;  // each vertex
    std::string vectorB;

    getline(std::cin, line);

    while (line != "finish") {
        if (std::cin.fail()) break;
        sStream << line;
        while(!sStream.eof()) {  // Loop through numbers
            if(!sStream.fail()) {
                sStream >> vectorA;
                sStream >> vectorB;
                pairs.emplace_back(std::stoi(vectorA), std::stoi(vectorB));
            }
        }
        sStream.str(std::string());  // Clear string
        sStream.clear();  // Clear the state flags for eof()
        getline(std::cin, line);
    }

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

    // OUTPUT - KERNEL GRAPH
    std::cout << std::endl << "Kernel Graph" << std::endl;
    std::cout << connectedCmptsList->size() << std::endl;
    std::cout << kernelGraph.size() << std::endl;
    for(auto & i : kernelGraph) {
        std::cout << i.first << " " << i.second << std::endl;
    }


    return 0;
}
