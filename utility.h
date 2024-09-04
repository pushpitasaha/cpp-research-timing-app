#ifndef UTILITY_H
#define UTILITY_H

#include "raylib.h"
#include "geometry.h"
#include <cmath>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

enum AlgorithmType {
    MST,
    CUSTOM1,
    CUSTOM2,
    ORIGINAL
};

// Utility functions declarations
float distance(Vector2 a, Vector2 b);
float angleBetween(Vector2 a, Vector2 b);
bool isPerpendicular(Vector2 circlePos, Vector2 squarePos, float squareSize);
string to_string_double2(double value);
string algorithmTypeToString(AlgorithmType algorithm);
void printResultEdgeset(const vector<std::pair<Vector2, Vector2>>& edges);
void printResultEdgesetID(const vector<pair<int, int>>& idEdges);
void drawDottedLine(Vector2 start, Vector2 end, float radius, float gap, Color color);

// Set operations
vector<pair<int, int>> setUnion(const vector<pair<int, int>>& set1, const vector<pair<int, int>>& set2);
vector<pair<int, int>> setIntersection(const vector<pair<int, int>>& set1, const vector<pair<int, int>>& set2);
float calculateJaccardIndex(const vector<pair<int, int>>& set1, const vector<pair<int, int>>& set2);
void printTestSummary(AlgorithmType algorithm, const vector<pair<int, int>>& resultEdges, const vector<pair<int, int>>& expectedEdges);


// Weight functors
struct EuclideanWeight {
    float operator()(Vector2 a, Vector2 b) const;
};

struct CustomWeight {
    const vector<Circle>& circles;
    const vector<Square>& squares;

    CustomWeight(const vector<Circle>& c, const vector<Square>& s);

    float operator()(Vector2 a, Vector2 b) const;
    bool isCircle(Vector2 pos) const;
};

struct CustomWeight2 {
    const vector<Circle>& circles;
    const vector<Square>& squares;

    CustomWeight2(const vector<Circle>& c, const vector<Square>& s);

    float operator()(Vector2 a, Vector2 b) const;
    bool isCircle(Vector2 pos) const;
};

#endif // UTILITY_H
