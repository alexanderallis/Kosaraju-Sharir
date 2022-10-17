//
// Created by Alexander Allis on 10/10/22.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>

#include "read_file.h"

using std::ifstream;

int readFile(const std::string & fileName, std::vector<std::pair<int, int>> & treePairs, int & numberOfVertices, int & numberOfEdges) {

    // Check if file exists
    ifstream inFile(fileName.c_str());  // Check to make sure file exists
    if (!inFile) {
        std::cerr << "File not found." << std::endl;
        return -1;
        // Or throw error
    }

// Open file
    ifstream fileStream(fileName);
    if (!fileStream.is_open()) {
        std::cout << "Can't read file." << std::endl;
        return -1;
        // Or throw error
    }

    std::stringstream sStream;  // stream to parse each line
    std::string line;  // each line (string)
    std::vector<int> row;  // each line (int)
    std::string vectorA;  // each vertex
    std::string vectorB;

    getline(fileStream, line);  // Consume first line
    numberOfVertices = stoi(line);

    getline(fileStream, line);  // Consume second line
    numberOfEdges = stoi(line);

    while(!fileStream.eof()) {  // Loop through lines

        getline(fileStream, line);

        if (!fileStream.fail()) {
            sStream << line;
            while(!sStream.eof()) {  // Loop through numbers
                if(!sStream.fail()) {
                    sStream >> vectorA;
                    sStream >> vectorB;
                    treePairs.emplace_back(std::stoi(vectorA), std::stoi(vectorB));
                }
            }

            // Clean up
            sStream.str(std::string());  // Clear string
            sStream.clear();  // Clear the state flags for eof()
            for (int &k: row) {    // Clear contents of the vector
                row.clear();
            }
        }
    }

    fileStream.close();
    return 0;
}
