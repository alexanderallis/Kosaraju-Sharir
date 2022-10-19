//
// Created by Alexander Allis on 10/17/22.
//
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <random>

#include "gtest/gtest.h"
#include "../LinkedList.h"


class BlackBox : public ::testing::Test {
public:

    virtual void SetUp() {
        // initialization or some code to run before each test
    }

    virtual void TearDown() {
        // code to run after each test;
        // can be used instead of a destructor,
        // but exceptions can be handled in this function only
    }

};

TEST_F(BlackBox, CheckPairsWithListOne) {



}

// generates random pairs to simulate a tree
std::vector<std::pair<int, int>> generateEdges(int numberOfNodes) {
    std::vector<std::pair<int, int>> pairs;
    std::vector<int> vectorA;
    vectorA.reserve(numberOfNodes);
    for(int i = 0; i < numberOfNodes; i++) { vectorA.emplace_back(i); }
    std::vector<int> vectorB;
    vectorB.reserve(numberOfNodes);
    for(int i = 0; i < numberOfNodes; i++) { vectorB.emplace_back(i); }

    std::random_device randomDevice;
    std::default_random_engine randEngine(randomDevice());
    shuffle(vectorA.begin(), vectorA.end(), randEngine);

    pairs.reserve(numberOfNodes);
    for(int i = 0; i < numberOfNodes; i++) {  // all nodes in vectorA point to one node in vectorB
        pairs.emplace_back(vectorA.at(i), vectorB.at(i));
    }

    int k = 2;
    while(vectorA.size() / k) {
        shuffle(vectorA.begin(), vectorA.end(), randEngine);  // shuffle vectorA again
        shuffle(vectorB.begin(), vectorB.end(), randEngine);  // shuffle vectorB again
        for(int i = 0; i < vectorA.size() / k; i++) {  // make n/2 new edges
            pairs.emplace_back(vectorA.at(i), vectorB.at(i));
        }
        k *= 2;
    }

    std::cout << pairs.size() << std::endl;
    return pairs;
}