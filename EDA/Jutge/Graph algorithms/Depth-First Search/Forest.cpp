#include <iostream>
#include <vector>
using namespace std;

bool forest_rec(vector<vector<int>>& graph, vector<bool>& visited, int i, int li) {
    visited[i] = true;

    for (int j = 0; j < graph[i].size(); ++j) {
            if (graph[i][j] != li) {
            if (visited[graph[i][j]] or not forest_rec(graph,visited,graph[i][j],i)) return false;
        }
    }
    return true;
}

int forest(vector<vector<int>>& graph) {
    vector<bool> visited (graph.size(), false);
    int counter = 0;
    for (int i = 0; i < graph.size(); ++i) {
        if (not visited[i]) {
            ++counter;
            if (not forest_rec(graph,visited,i,-1)) return -1;
        }
    }
    return counter;
}

int main() {
    int n, m, x, y;
    while (cin >> n >> m) {
        vector<vector<int>> graph (n);
        for (int i = 0; i < m; ++i) {
            cin >> x >> y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        int f = forest(graph);
        if (f == -1) cout << "no" << endl;
        else cout << f << endl;
    }
}