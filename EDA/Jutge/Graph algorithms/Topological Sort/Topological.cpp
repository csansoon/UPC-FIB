#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> topological_sort(vector<vector<int>>& graph, vector<int> apuntadors) {
    priority_queue<int, vector<int>, greater<int>> cua;
    vector<int> sorted;
    for (int i = 0; i < apuntadors.size(); ++i) if (apuntadors[i] == 0) cua.push(i);
    while (not cua.empty()) {
        int n = cua.top();
        sorted.push_back(n);
        cua.pop();
        for(int i = 0; i < graph[n].size(); ++i) if (--apuntadors[graph[n][i]] == 0) cua.push(graph[n][i]);
    }
    return sorted;
}


int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> graph(n);
        vector<int> apuntadors(n,0);
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            graph[x].push_back(y);
            ++apuntadors[y];
        }
        vector<int> sorted = topological_sort(graph,apuntadors);
        if (sorted.size() > 0) cout << sorted[0];
        for (int i = 1; i < sorted.size(); ++i) cout << " " << sorted[i];
        cout << endl;
    }
}