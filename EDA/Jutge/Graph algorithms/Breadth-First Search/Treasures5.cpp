#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct cell {
    int x;
    int y;
    int distance;

    cell(int xx, int yy, int dd) : x(xx), y(yy), distance(dd) {}
};

int BFS(vector<vector<char>> map, int x, int y) {
    vector<int> treasures;
    int n = map.size();
    int m = map[0].size();

    vector<vector<bool>> visited (n, vector<bool>(m, false));
    queue<cell> cua;
    cua.push(cell(x,y,0));
    visited[x][y] = true;

    int d = -1;

    while (not cua.empty()) {
        cell c = cua.front();
        if (map[c.x][c.y] == 't') treasures.push_back(c.distance);


        if (c.x+1 < n and not visited[c.x+1][c.y]) {    //RIGHT
            visited[c.x+1][c.y] = true;
            char t = map[c.x+1][c.y];
            if (t != 'X') cua.push(cell(c.x+1,c.y,c.distance+1));
            }
        if (c.y+1 < m and not visited[c.x][c.y+1]) {    //DOWN
            visited[c.x][c.y+1] = true;
            char t = map[c.x][c.y+1];
            if (t != 'X') cua.push(cell(c.x,c.y+1,c.distance+1));
            }
        if (c.x-1 >= 0 and not visited[c.x-1][c.y]) {   //LEFT
            visited[c.x-1][c.y] = true;
            char t = map[c.x-1][c.y];
            if (t != 'X') cua.push(cell(c.x-1,c.y,c.distance+1));
            }
        if (c.y-1 >= 0 and not visited[c.x][c.y-1]) {   //UP
            visited[c.x][c.y-1] = true;
            char t = map[c.x][c.y-1];
            if (t != 'X') cua.push(cell(c.x,c.y-1,c.distance+1));
            }
        cua.pop();
    }
    if (treasures.size() < 2) return -1;
    return treasures[treasures.size()-2];
}

int main() {
    int n,m;
    cin >> n >> m;
    vector<vector<char>> map (n, vector<char>(m));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> map[i][j];

    int x, y;
    cin >> x >> y;
    --x; --y;
    int d = BFS(map,x,y);
    if (d == -1) cout << "we cannot reach two or more treasures" << endl;
    else cout << "second maximum distance: " << d << endl;
}