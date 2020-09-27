#include <iostream>
#include <vector>
using namespace std;

bool is_cyclic(vector<vector<int>>& graph, int start, int u) {
    for (int i = 0; i < graph[u].size(); ++i) {
        if (graph[u][i] == start) return true;
        if (is_cyclic(graph,start,graph[u][i])) return true;
    }
    return false;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> graph(n);
        bool cyclic = false;
        for (int i = 0; i < m; ++i) {
            int u, v;   // u -> v
            cin >> u >> v;
            graph[u].push_back(v);
            if (not cyclic and is_cyclic(graph,u, u)) cyclic = true;
        }
        if (cyclic) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}