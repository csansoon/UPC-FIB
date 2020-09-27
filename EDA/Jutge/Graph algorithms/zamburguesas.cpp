#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

struct rock {
    float x;
    float y;
    float r;
    //rock(): x(0), y(0), r(0) {}
    //rock(float X, float Y, float R): x(X), y(Y), r(R) {}
};

float distance(rock& a, rock& b) {
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)) - a.r - b.r;
}

int BFS(vector<vector<int>>& graph, int i) {
    queue<pair<int,int>> cua;
    vector<bool> visited(graph.size(),false);
    cua.push(make_pair(i,0));
    visited[i]= true;
    while (not cua.empty()) {
        for (int j = 0; j < graph[cua.front().first].size(); ++j) {
            int r = cua.front().first;
            if (graph[r][j] == graph.size()-1) return cua.front().second + 1;
            if (not visited[graph[r][j]]) {
                cua.push(make_pair(graph[r][j],cua.front().second+1));
            }
        }
        cua.pop();
    }
    return -1;
}


int main() {
    int n, d;
    while (cin >> n >> d) {
        vector<rock> rocks;
        vector<vector<int>> jumps(n);
        for (int i = 0; i < n; ++i) {
            rock R;
            cin >> R.x >> R.y >> R.r;
            rocks.push_back(R);
            for (int j = 0; j < rocks.size(); ++j) {
                if (i != j and distance(rocks[i],rocks[j]) <= d) {
                    jumps[i].push_back(j);
                    jumps[j].push_back(i);
                }
            }
        }

        int min_jumps = BFS(jumps,0);
        if (min_jumps == -1) cout << "Xof!" << endl;
        else cout << min_jumps << endl;
    }
}