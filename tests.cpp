#include "tests.h"
#include <fstream>
#include <iostream>
#include <unordered_set>
#include "utility.h"

void writeTestToFile(const std::string& filename, const std::vector<Circle>& circles, const std::vector<Square>& squares, const std::vector<std::pair<int, int>>& testEdgesID) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Write circles
    outFile << circles.size() << "\n";
    for (const auto& circle : circles) {
        outFile << circle.position.x << " " << circle.position.y << " " << circle.id << "\n";
    }
    // Write squares
    outFile << squares.size() << "\n";
    for (const auto& square : squares) {
        outFile << square.position.x << " " << square.position.y << " " << square.id << "\n";
    }

    // Write edges
    outFile << testEdgesID.size() << "\n";
    for (const auto& edge : testEdgesID) {
        outFile << edge.first << " " << edge.second << "\n";
    }

    outFile.close();

    if (!outFile) {
        std::cerr << "Failed to write to file: " << filename << std::endl;
    } else {
        std::cout << "Test saved to file: " << filename << std::endl;
    }
}

void loadTest(const std::string& filename, std::vector<Circle>& circles, std::vector<Square>& squares, std::vector<std::pair<int, int>>& testEdgesID) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    int numCircles, numSquares, numEdges;

    // Read circles
    inFile >> numCircles;
    circles.clear();
    for (int i = 0; i < numCircles; ++i) {
        float x, y;
        int id;
        inFile >> x >> y >> id;
        circles.push_back({{x, y}, 20.0f, RED, id});
    }

    // Read squares
    inFile >> numSquares;
    squares.clear();
    for (int i = 0; i < numSquares; ++i) {
        float x, y;
        int id;
        inFile >> x >> y >> id;
        squares.push_back({{x, y}, 40.0f, BLUE, id});
    }

    // Read edges
    inFile >> numEdges;
    testEdgesID.clear();
    for (int i = 0; i < numEdges; ++i) {
        int id1, id2;
        inFile >> id1 >> id2;
        testEdgesID.push_back({id1, id2});
    }

    inFile.close();

    if (!inFile) {
        std::cerr << "Failed to read from file: " << filename << std::endl;
    } else {
        std::cout << "Test loaded from file: " << filename << std::endl;
    }
}



