// Jonah Ebent, ShortestPath.cpp
// Contains implementations of elementary graph algorithms
// longestCircuit employs a modification of depth-first search
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
private:
    int size;
    vector<vector<int>> matrix;

    bool contains(vector<int> path, int node) const {
        return find(path.begin(), path.end(), node) != path.end();
    }

    void longestCircuit(int current, vector<int> &path, int start, vector<int> &longest) const {
        // for each neighbor
        for (int n : neighbors(current)) {
            // if neighbor is not already visited
            if (!contains(path, n)) {
                path.push_back(n);
                longestCircuit(n, path, start, longest);
                path.erase(path.end() - 1);
            }
            else {
                if (n == start && path.size() > 2 && path.size() >= longest.size()) {
                    path.push_back(n);
                    longest = path;
                    if (path.size() == size) return;
                    path.erase(path.end() - 1);
                }
            }
        }
    }

public:
    Graph(int size, const vector<pair<int, int>>& edges, bool directed = true) :
        size(size),
        matrix(size, vector<int>(size, 0))
    {
        for (const auto& edge : edges) {
            matrix[edge.first][edge.second] = 1;
            if (!directed) matrix[edge.second][edge.first] = 1;
        }
    }

    void displayMatrix() {
        cout << "  ";
        for (int i = 0; i < size; i++) {
            cout << i << " ";
        }
        cout << endl;
        for (int i = 0; i < size; i++) {
            cout << i << " ";
            for (int j = 0; j < size; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    vector<int> neighbors(int n) const {
        vector<int> neighbors = {};
        for (int i = 0; i < size; i++) {
            if (matrix[n][i] == 1) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }

    vector<int> shortestPath(const int start, const int finish) const {
        vector<int> parents(size, -1);  // keeps track of the parent of each node
        queue<int> queue;               // keeps track of which node to visit next
        int current = start;
        while (current != finish) {
            for (int n : neighbors(current)) {  // for each neighbor n
                if (parents.at(n) == -1) {          // if n hasn't been visited yet
                    parents.at(n) = current;            // log n's parent as current
                    queue.push(n);                      // add to queue
                }
            }
            if (queue.empty()) return {};   // exhausted nodes before reaching finish
            current = queue.front();        // get next in queue
            queue.pop();
        }
        vector<int> path = {};          // recover path by following parents backwards
        while (current != start) {
            path.insert(path.begin(), current);
            current = parents.at(current);
        }
        path.insert(path.begin(), current);
        return path;
    }

    vector<int> longestCircuit(int a) {
        vector<int> path = { a };
        vector<int> longest = {};
        longestCircuit(a, path, a, longest);
        return longest;
    }
};

int main()
{
    vector<pair<int, int>> edges = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 1},
        {1, 4},
        {4, 5},
        {5, 6},
        {6, 4},
        {0, 5},
        {2, 5}
    };
    Graph g(7, edges);
    g.displayMatrix();
    for (int i : g.shortestPath(3, 6)) cout << i << " ";
    cout << endl;

    vector<pair<int, int>> moreEdges = {
        {0, 1},
        {1, 2},
        {2, 0},
        {2, 3},
    };
    Graph h(7, edges, false);
    for (int i : h.longestCircuit(3)) cout << i << " ";
    cout << endl;
}
