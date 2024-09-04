#include "utility.h"
#include <sstream>
#include <iomanip>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <unordered_set>

using namespace std;

float distance(Vector2 a, Vector2 b) {
    return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
}

float angleBetween(Vector2 a, Vector2 b) {
    float deltaX = b.x - a.x;
    float deltaY = a.y - b.y; // Invert y-coordinates to match mathematical coordinate system
    float angleRadians = atan2f(deltaY, deltaX);
    float angleDegrees = angleRadians * (180.0f / PI);

    if (angleDegrees < 0) {
        angleDegrees += 360.0f;
    }

    return angleDegrees;
}

// Check if a square is perpendicular to a circle
bool isPerpendicular(Vector2 circlePos, Vector2 squarePos, float squareSize)
{
    float dx = squarePos.x - circlePos.x;
    // float dy = squarePos.y - circlePos.y;
    return abs(dx) <= squareSize && squarePos.y < circlePos.y;
}

//convert functions
string to_string_double2(double value) {
    stringstream stream;
    stream << fixed << setprecision(2) << value;
    return stream.str();
}

string algorithmTypeToString(AlgorithmType algorithm) {
    switch (algorithm) {
        case MST:
            return "MST";
        case CUSTOM1:
            return "CUSTOM1";
        case CUSTOM2:
            return "CUSTOM2";
        case ORIGINAL:
            return "ORIGINAL";
        default:
            return "UNKNOWN";
    }
}

void drawDottedLine(Vector2 start, Vector2 end, float radius, float gap, Color color) {
    // Calculate the total distance between the start and end points
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float distance = sqrt(dx * dx + dy * dy);

    // Calculate the direction vector of the line
    float dirX = dx / distance;
    float dirY = dy / distance;

    // Calculate the number of dots to draw
    int dotCount = distance / (2 * radius + gap);

    for (int i = 0; i <= dotCount; ++i) {
        // Calculate the position of each dot
        float x = start.x + i * (2 * radius + gap) * dirX;
        float y = start.y + i * (2 * radius + gap) * dirY;

        // Draw the dot
        DrawCircle(x, y, radius, color);
    }
}

void printResultEdgeset(const vector<std::pair<Vector2, Vector2>>& edges) {
    cout << "Edges:" << endl;
    for (const auto& edge : edges) {
        cout << "(" << edge.first.x << ", " << edge.first.y << ") - (" << edge.second.x << ", " << edge.second.y << ")" << endl;
    }
    cout << endl;
}

void printResultEdgesetID(const vector<pair<int, int>>& idEdges) {
    cout << "Edges:" << endl;
    for (const auto& edge : idEdges) {
        cout << edge.first << " " << edge.second << endl;
    }
    cout << endl;
}

//Set functions for eval
vector<pair<int, int>> setUnion(const vector<pair<int, int>>& set1, const vector<pair<int, int>>& set2) {
    unordered_set<string> edgeSet;
    vector<pair<int, int>> unionSet = set1;

    for (const auto& edge : set1) {
        string edgeStr = std::to_string(edge.first) + " " + std::to_string(edge.second);
        edgeSet.insert(edgeStr);
    }

    for (const auto& edge : set2) {
        string edgeStr = std::to_string(edge.first) + " " + std::to_string(edge.second);
        if (edgeSet.find(edgeStr) == edgeSet.end()) {
            unionSet.push_back(edge);
            edgeSet.insert(edgeStr);
        }
    }

    return unionSet;
}

vector<pair<int, int>> setIntersection(const vector<pair<int, int>>& set1, const vector<pair<int, int>>& set2) {
    unordered_set<string> edgeSet1, edgeSet2;
    vector<pair<int, int>> intersectionSet;

    for (const auto& edge : set1) {
        string edgeStr = std::to_string(edge.first) + " " + std::to_string(edge.second);
        edgeSet1.insert(edgeStr);
    }

    for (const auto& edge : set2) {
        string edgeStr = std::to_string(edge.first) + " " + std::to_string(edge.second);
        if (edgeSet1.find(edgeStr) != edgeSet1.end()) {
            intersectionSet.push_back(edge);
        }
    }

    return intersectionSet;
}

float calculateJaccardIndex(const vector<pair<int, int>>& set1, const vector<pair<int, int>>& set2) {
    vector<pair<int, int>> unionSet = setUnion(set1, set2);
    vector<pair<int, int>> intersectionSet = setIntersection(set1, set2);

    if (unionSet.size() == 0) return 1.0f;
    return static_cast<float>(intersectionSet.size()) / unionSet.size();
}

void printTestSummary(AlgorithmType algorithm, const vector<pair<int, int>>& resultEdges, const vector<pair<int, int>>& expectedEdges) {
    vector<pair<int, int>> unionSet = setUnion(resultEdges, expectedEdges);
    vector<pair<int, int>> intersectionSet = setIntersection(resultEdges, expectedEdges);
    float jaccardIndex = calculateJaccardIndex(resultEdges, expectedEdges);

    cout << "Algorithm: " << algorithmTypeToString(algorithm) << endl;
    cout << "Compared to solution, intersection / union is: " << jaccardIndex << endl;

    unordered_set<string> resultEdgeSet, expectedEdgeSet, addedEdges, omittedEdges;

    for (const auto& edge : resultEdges) {
        string edgeStr = std::to_string(edge.first) + " " + std::to_string(edge.second);
        resultEdgeSet.insert(edgeStr);
    }

    for (const auto& edge : expectedEdges) {
        string edgeStr = std::to_string(edge.first) + " " + std::to_string(edge.second);
        expectedEdgeSet.insert(edgeStr);
    }

    for (const auto& edgeStr : resultEdgeSet) {
        if (expectedEdgeSet.find(edgeStr) == expectedEdgeSet.end()) {
            addedEdges.insert(edgeStr);
        }
    }

    for (const auto& edgeStr : expectedEdgeSet) {
        if (resultEdgeSet.find(edgeStr) == resultEdgeSet.end()) {
            omittedEdges.insert(edgeStr);
        }
    }

    if (!addedEdges.empty()) {
        cout << "The algorithm ADDED the following INCORRECT edges:" << endl;
        int edgeCount = 1;
        for (const auto& edgeStr : addedEdges) {
            cout << "Edge " << edgeCount << ": " << edgeStr << endl;
            edgeCount++;
        }
    } else {
        cout << "The algorithm did not add any incorrect edges." << endl;
    }

    if (!omittedEdges.empty()) {
        cout << "The algorithm OMITTED the following CORRECT edges:" << endl;
        int edgeCount = 1;
        for (const auto& edgeStr : omittedEdges) {
            cout << "Edge " << edgeCount << ": " << edgeStr << endl;
            edgeCount++;
        }
    } else {
        cout << "The algorithm did not omit any correct edges." << endl;
    }
}

// Functor definitions
float EuclideanWeight::operator()(Vector2 a, Vector2 b) const {
    return distance(a, b);
}

CustomWeight::CustomWeight(const vector<Circle>& c, const vector<Square>& s) : circles(c), squares(s) {}

float CustomWeight::operator()(Vector2 a, Vector2 b) const {
    bool isCircleA = isCircle(a);
    bool isCircleB = isCircle(b);

    if (isCircleA && isCircleB) {
        return distance(a, b);
    } else if (isCircleA || isCircleB) {
        return distance(a, b) * 0.77f;
    }
    return FLT_MAX; // No square-square connections
}

bool CustomWeight::isCircle(Vector2 pos) const {
    for (const auto& circle : circles) {
        if (circle.position.x == pos.x && circle.position.y == pos.y) {
            return true;
        }
    }
    return false;
}

//not using custom 2
CustomWeight2::CustomWeight2(const vector<Circle>& c, const vector<Square>& s) : circles(c), squares(s) {}

float CustomWeight2::operator()(Vector2 a, Vector2 b) const {
    bool isCircleA = isCircle(a);
    bool isCircleB = isCircle(b);

    if (isCircleA && isCircleB) {
        return distance(a, b);
    } else if (isCircleA || isCircleB) {
        float angle = angleBetween(a, b);
        return angle * distance(a, b) / 3.0f;
    }
    return FLT_MAX; // No square-square connections
}

bool CustomWeight2::isCircle(Vector2 pos) const {
    for (const auto& circle : circles) {
        if (circle.position.x == pos.x && circle.position.y == pos.y) {
            return true;
        }
    }
    return false;
}
