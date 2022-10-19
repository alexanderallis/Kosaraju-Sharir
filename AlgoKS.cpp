//
// Created by Alexander Allis on 10/11/22.
//
#include "AlgoKS.h"
#include "LinkedList.h"
#include "Stack.h"

/*
 * Returns a stack that will pop vertices in reverse postorder.
 * Pushes vertices on stack in order of dfs return.
 * Args:
 *  graph: an adjacency list of the graph
 *  numberOfVertices: number of vertices in the graph
 * Returns:
 *  reversePostorder: a stack which will pop values in reverse postorder
 */
Stack * getReversePostorder(std::vector<LinkedList> graph, const int numberOfVertices) {

    auto * reversePostorder = new Stack(numberOfVertices);
    bool isExplored[numberOfVertices];
    for(int i = 0; i < numberOfVertices; i++) { isExplored[i] = false; }

    for(int i = 0; i < numberOfVertices; i++) {
        if(!isExplored[i]) {
            dfsPostorder(graph, reversePostorder, isExplored, i);
        }
    }

    return reversePostorder;
}

/*
 * Runs a recursive dfs search on a graph and pushes vertices onto a stack on dfs return.
 * args:
 *  graph: an adjacency list of the graph
 *  reversePostorder: a stack that will pop values in reverse postorder
 *  isExplored: a list of boolean values that track which vertices have been isExplored.
 *  root: the value of the vertex which called the function.
 * returns: the value of the vertex which called the dfs search.
 */
int dfsPostorder(std::vector<LinkedList> & graph, Stack * reversePostorder, bool * isExplored, int root) {

    isExplored[root] = true;
    int root2;
    // For each edge connected to root...
    while(!graph.at(root).isEnd()) {
        root2 = graph.at(root).pop();
        if(!isExplored[root2]) {  // ...if not explored...
            dfsPostorder(graph, reversePostorder, isExplored, root2);  // ...recursively invoke dfs.
        }
    }

    reversePostorder -> push(root);
    return root;

}

/*
 * Runs a dfs search on vertices according to the reverse postorder. Modifies a connected components list inplace and
 * a kernel graph inplace.
 * Args:
 *  graph: an adjacency list of the graph
 *  reversePostorder: a stack that pops the vertices in reverse postorder
 *  connectedCmptsList: a list of linked lists of connected components
 *  idList: an array that logs which vertex goes with which connected component (index:value = vertex:ID)
 *  numberOfVertices: the number of vertices in the graph.
 *  kernelEdges: a list of edges in the kernel graph.
 * Returns:
 *  0 if executed correctly. Modifies connectedCmptsList, idList, kernelEdges inplace
 */
int dfsSearchByRevPostorder(std::vector<LinkedList> & graph, Stack * reversePostorder, std::vector<LinkedList> * connectedCmptsList, int * idList, int numberOfVertices, std::vector<std::pair<int, int>> & kernelEdges) {

    int parent;
    int idCounter = 0;

    bool* explored = new bool[numberOfVertices]();
    for(int i = 0; i < numberOfVertices; i++) { explored[i] = false; }
    bool* kernelExplored = new bool[numberOfVertices]();
    for(int i = 0; i < numberOfVertices; i++) { explored[i] = false; }

    while(!reversePostorder -> isEmpty()) {
        parent = reversePostorder -> pop();
        if(!explored[parent]) {
            auto * connectionList = new LinkedList;
            connectedCmptsList -> push_back(*dfsConnections(graph, reversePostorder, connectionList, idList, explored, parent, idCounter, kernelEdges, kernelExplored));
            idCounter++;
            *kernelExplored = {false};  // reset kernel explored for each idCounter
        }
    }

    return 0;
}

/*
 * Recursively invokes a dfs search to determine the strongly connected components.
 * Args:
 *  graph: an adjacency list of the graph
 *  reversePostoder: a stack that pops vertices in reverse postorder
 *  stronglyConnectedList: a singly-linked list that follows the path of the recursive dfs search
 *  idList: an array of vertices and their kernel IDs (index:value = vertex:ID)
 *  isExplored: a boolean array to keep track of which vertices have been isExplored by the dfs search
 *  root: the vertex from which the dfs search was invoked
 *  idCounter: iterates for each separate kernel, used for calculating kernel pairs and kernel ID
 *  kernelPairs: a list of kernel edges. modified inplace.
 *  kernelIsExplored: a boolean array to keep track of whether a kernel has been isExplored (used to identify parallel edges in the kernel graph). Modified inplace.
 * Returns:
 *  stronglyConnectedList: a linked list of strongly connected components.
 */
LinkedList * dfsConnections(std::vector<LinkedList> & graph, Stack * reversePostorder, LinkedList * stronglyConnectedList, int * idList, bool * isExplored, int root, int idCounter, std::vector<std::pair<int, int>> & kernelPairs, bool * kernelIsExplored) {

    //mark u as isExplored and add u to r
    stronglyConnectedList -> add(root);
    idList[root] = idCounter;
    isExplored[root] = true;
    int root2;
    // For each edge connected to root...
    while(!graph.at(root).isEnd()) {
        // ...if not explored...
        root2 = graph.at(root).pop();
        if(!isExplored[root2]) {
            // ...recursively invoke dfs.
            dfsConnections(graph, reversePostorder, stronglyConnectedList, idList, isExplored, root2, idCounter, kernelPairs, kernelIsExplored);
        }
        else {  // add to kernel graph
            if(idList[root2] != idCounter && !kernelIsExplored[idList[root2]]) {
                kernelPairs.emplace_back(idCounter, idList[root2]);
                kernelIsExplored[idList[root2]] = true;
            }

        }
    }
    graph.at(root).reset();  // clean up for future use
    return stronglyConnectedList;

}

/*
 * Returns the reverse graph
 * Args:
 *  g: the graph to reverse
 * returns:
 *  gR: the reversed graph
 */
std::vector<std::pair<int, int>> getPairsOfGReverse(std::vector<std::pair<int, int>> & g) {

    std::vector<std::pair<int, int>> gR;
    gR.reserve(g.size());

    for(auto & i : g) {
        gR.emplace_back(i.second, i.first);
    }

    return gR;

}
