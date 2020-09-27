#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct edge {
    int v;
    int cost;
    vector<int> path;

    edge(): v(0), cost(0), path(vector<int>(0)) {}
    edge(int w, int c): v(w), cost(c), path(vector<int>(0)) {}
    edge(int w, int c, vector<int> v): v(w), cost(c), path(v) {}
    friend bool operator< (const edge& a, const edge& b) {return a.cost > b.cost;}
};

edge dijkstra(vector<vector<edge>>& graph, int x, int y) {
    priority_queue<edge> cua;
    vector<bool> visited(graph.size(),false);
    vector<int> costs(graph.size(),-1);
    cua.push(edge(x,0,vector<int>(1,x)));

    while (not cua.empty()) {
        edge e = cua.top();
        cua.pop();
        if (not visited[e.v]) {
            visited[e.v] = true;
            if (e.v == y) return e;
            for (int i = 0; i < graph[e.v].size(); ++i) {
                edge ne (graph[e.v][i].v,graph[e.v][i].cost);
                if (costs[ne.v] == -1 or costs[ne.v] > ne.cost + e.cost) {
                    costs[ne.v] = ne.cost + e.cost;

                    edge pe(graph[e.v][i].v,graph[e.v][i].cost + e.cost,e.path);
                    pe.path.push_back(pe.v);
                    cua.push(pe);
                }
            }
        }
    }
    return edge(x,-1,vector<int>(0));
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<edge>> graph(n);
        for (int i = 0; i < m; ++i) {
            int j;
            edge e;
            cin >> j >> e.v >> e.cost;
            graph[j].push_back(e);
        }

        int x, y;
        cin >> x >> y;
        edge d = dijkstra(graph,x,y);
        if (d.path.size() == 0) cout << "no path from " << x << " to " << y << endl;
        else {
            cout << d.path[0];
            for (int i = 1; i < d.path.size(); ++i) cout << " " << d.path[i];
            cout << endl;
        }
    }
}