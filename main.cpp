#include "raylib.h"
#include "geometry.h"
#include "mst.h"
#include "utility.h"
#include "tests.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <filesystem>
#include <iomanip>

using namespace std;
using namespace chrono;

void saveTimesToFile(const string &filename, const vector<double> &times) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }
    // Set the format to fixed with precision
    outFile << std::fixed << std::setprecision(7);

    for (const auto &time : times) {
        outFile << time << endl;
    }
    outFile.close();
}

//argc - # of cmd line args
//argv - char array representing those cmd line args
//main for timing
int main(int argc, char *argv[]) {
    if (argc != 5) {
        cerr << "cmd format: " << argv[0] << " <algorithm> <testcase> <repetitions> <output_file>" << endl;
        return 1;
    }

    int algorithm = stoi(argv[1]); // first argc converted to algo num 0-2
    string testcase = argv[2]; //base name of test file
    int repetitions = stoi(argv[3]);
    string outputFile = argv[4];

    vector<Circle> circles;
    vector<Square> squares;
    vector<pair<int, int>> testEdgesID;

    // Load the test case
    string testFileName = testcase + ".txt";
    loadTest(testFileName, circles, squares, testEdgesID);

    vector<double> times;

    for (int i = 0; i < repetitions; ++i) {
        auto start = high_resolution_clock::now();

        if (algorithm == 0) {
            // Run the hand-engineered connectAlgorithm
            connectAlgorithm(circles, squares);            
        } else if (algorithm == 1) {
            // Run connectAlgorithmMST with EuclideanWeight - Kruskal
            connectAlgorithmMST(circles, squares, "last-mst-rslt.txt", EuclideanWeight());
        } else if (algorithm == 2) {
            // Run connectAlgorithmMST with CustomWeight - tweaked the functor
            connectAlgorithmMST(circles, squares, "last-custom-rslt.txt", CustomWeight(circles, squares));
        } else {
            cerr << "Invalid algorithm choice. [0-2]" << endl;
            return 1;
        }

        auto end = high_resolution_clock::now();
        
        // Calculate the duration
        std::chrono::duration<double> elapsed = end - start;

        //print the elapsed vals
        std::cout << std::fixed << std::setprecision(7) << elapsed.count() << " seconds" << std::endl;

        // Store the duration in the times vector
        times.push_back(elapsed.count());
        
        // Delay outside timed section between runs
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Save the times to the output file
    saveTimesToFile(outputFile, times);

    return 0;
} 


