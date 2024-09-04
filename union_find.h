#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>

using namespace std;

// Union-Find (disjoint set) data structure
struct UnionFind {
    vector<int> parent, rank;

    // Constructor
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    
    // Find the root of the set containing u with path compression
    int find(int u) {
        if (u != parent[u]) parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union two sets containing u and v
    void unite(int u, int v) {
        int root_u = find(u), root_v = find(v); // Finding roots
        if (root_u != root_v) { // If they're in different sets
            // Union by rank
            if (rank[root_u] > rank[root_v]) parent[root_v] = root_u;
            else if (rank[root_u] < rank[root_v]) parent[root_u] = root_v;
            else { parent[root_v] = root_u; rank[root_u]++; }
        }
    }
};

#endif // UNION_FIND_H
