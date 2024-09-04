#ifndef MST_H
#define MST_H

#include "raylib.h"
#include "union_find.h"
#include "geometry.h"
#include "utility.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cfloat>

using namespace std;

struct Edge {
    size_t i, j;
    float weight;
    Edge(size_t i = 0, size_t j = 0, float weight = 0) : i(i), j(j), weight(weight) {}
};

//hand-engineered connect algo that checks if a square is perpendicular 
vector<std::pair<Vector2, Vector2>> connectAlgorithm(
    const vector<Circle> &circles,
    const vector<Square> &squares)
{
    vector<std::pair<Vector2, Vector2>> pointPairs;
    for (size_t i = 0; i < circles.size(); i++)
    {
        if ((circles[i].position.x < circles[i + 1].position.x) || (circles[i].position.x > circles[i - 1].position.x))
        {
            // Find the best-fit square on top of the circle
            float bestDistance = FLT_MAX;
            int bestIndex = -1;
            for (size_t j = 0; j < squares.size(); j++)
            {
                float dist = distance(circles[i].position, squares[j].position);
                if (dist < bestDistance && isPerpendicular(circles[i].position, squares[j].position, squares[j].size))
                {
                    bestDistance = dist;
                    bestIndex = j;
                }
            }

            // separate draw from calculation
            if (bestIndex != -1)
            {
                pointPairs.push_back(
                    std::pair<Vector2, Vector2>(
                        circles[i].position,
                        squares[bestIndex].position));
            }
            // Connect with the next circle
            if (i != circles.size() - 1)
            {
                pointPairs.push_back(
                    std::pair<Vector2, Vector2>(
                        circles[i].position,
                        circles[i + 1].position));
            }
        }
    }
    return pointPairs;
}

//MST that takes in different functors
template<typename WeightFunc>
vector<std::pair<Vector2, Vector2>> connectAlgorithmMST(
    const vector<Circle>& circles,
    const vector<Square>& squares,
    const string& filename,
    WeightFunc weightFunc
) {
    vector<Edge> edges;
    size_t n = circles.size() + squares.size();
    vector<Vector2> positions;
    positions.reserve(n);

    for (const auto& circle : circles) positions.push_back(circle.position);
    for (const auto& square : squares) positions.push_back(square.position);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            float weight = weightFunc(positions[i], positions[j]);
            if (weight < FLT_MAX) {
                edges.emplace_back(i, j, weight);
            }
        }
    }
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    UnionFind uf(n);
    vector<std::pair<Vector2, Vector2>> mstEdges;

    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return {};
    }

    for (const auto& edge : edges) {
        if (uf.find(edge.i) != uf.find(edge.j)) {
            uf.unite(edge.i, edge.j);
            mstEdges.push_back({ positions[edge.i], positions[edge.j] });
            outputFile << "(" << edge.i + 1 << ", " << edge.j + 1 << ")" << endl;
        }
    }
    outputFile.close();

    return mstEdges;
}

#endif // MST_H
