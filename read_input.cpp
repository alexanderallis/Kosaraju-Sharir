//
// Created by Alexander Allis on 10/10/22.
//

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include "read_input.h"

using std::ifstream;

/*
 * Gets the list of pairs from the standard input according to the format specified in main.cpp
 * Args:
 *  pairs: modifies list of pairs inplace
 *  numberOfVertices: modifies inplace
 *  numberOfEdges: modifies inplace
 * Returns:
 *  0 if executed
 */

int getPairsFromStdIn(std::vector<std::pair<int, int>> & pairs, int & numberOfVertices, int & numberOfEdges) {

    std::cout << "Please input tree, and press \"enter\"." << std::endl;

    // Get input from stdin
    std::string input;
    std::string line;
    getline(std::cin, line);  // get vertices
    numberOfVertices = stoi(line);
    getline(std::cin, line);  // get edges
    numberOfEdges = stoi(line);

    std::stringstream sStream;
    std::string vectorA;  // each vertex
    std::string vectorB;

    for(int i = 0; i < numberOfEdges; i++) {
        getline(std::cin, line);
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
    }

    return 0;
}
