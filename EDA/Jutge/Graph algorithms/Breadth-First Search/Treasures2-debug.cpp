#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/* +=================== DEBUG ===================+ */
#define FPS 5

#include <chrono>
#include <thread>
const string    reset       = "\033[1;0m";
const string    magenta     = "\033[1;35m";
const string    red_b       = "\033[1;41m";
const string    green_b     = "\033[1;42m";
const string    yellow_b    = "\033[1;43m";
const string    blue_b      = "\033[1;44m";
void debug_print(int x, int y, vector<vector<char>>& map, vector<vector<bool>>& been_here) {
system("clear");
cout << magenta;
cout << "+";
for (int i = 0; i < map[0].size(); ++i) cout << "=";
cout << "+";
cout << reset << endl;
for (int i = 0; i < map.size(); ++i) {
    cout << magenta << "|" << reset;
    for (int j = 0; j < map[0].size(); ++j) {
        if (x == i and y == j) cout << green_b;
        else if (been_here[i][j] and map[i][j] == 't') cout << yellow_b;
        else if (been_here[i][j] and map[i][j] == '.') cout << blue_b;
        else if (been_here[i][j]) cout << red_b;
        cout << map[i][j] << reset;
    }
    cout << magenta << "|" << reset;
    cout << endl;
}
cout << magenta;
cout << "+";
for (int i = 0; i < map[0].size(); ++i) cout << "=";
cout << "+";
cout << reset << endl;
}
/* +=============================================+ */



struct cell {
    int x;
    int y;
    int distance;

    cell(int xx, int yy, int dd) : x(xx), y(yy), distance(dd) {}
};

int BFS(vector<vector<char>> map, int x, int y) {
    int n = map.size();
    int m = map[0].size();

    vector<vector<bool>> visited (n, vector<bool>(m, false));
    queue<cell> cua;
    cua.push(cell(x,y,0));
    visited[x][y] = true;
/* +=================== DEBUG ===================+ */
this_thread::sleep_for(chrono::milliseconds(1000/FPS)); //
debug_print(x,y,map,visited);              //
/* +=============================================+ */

    while (not cua.empty()) {

        cell c = cua.front();
        if (map[c.x][c.y] == 't') return c.distance;


        if (c.x+1 < n and not visited[c.x+1][c.y]) {    //RIGHT
            visited[c.x+1][c.y] = true;
/* +=================== DEBUG ===================+ */
this_thread::sleep_for(chrono::milliseconds(1000/FPS)); //
debug_print(x,y,map,visited);              //
/* +=============================================+ */
            char t = map[c.x+1][c.y];
            if (t == 't') return c.distance+1;
            else if (t != 'X') cua.push(cell(c.x+1,c.y,c.distance+1));
            }
        if (c.y+1 < m and not visited[c.x][c.y+1]) {    //DOWN
            visited[c.x][c.y+1] = true;
/* +=================== DEBUG ===================+ */
this_thread::sleep_for(chrono::milliseconds(1000/FPS)); //
debug_print(x,y,map,visited);              //
/* +=============================================+ */
            char t = map[c.x][c.y+1];
            if (t == 't') return c.distance+1;
            else if (t != 'X') cua.push(cell(c.x,c.y+1,c.distance+1));
            }
        if (c.x-1 >= 0 and not visited[c.x-1][c.y]) {   //LEFT
            visited[c.x-1][c.y] = true;
/* +=================== DEBUG ===================+ */
this_thread::sleep_for(chrono::milliseconds(1000/FPS)); //
debug_print(x,y,map,visited);              //
/* +=============================================+ */
            char t = map[c.x-1][c.y];
            if (t == 't') return c.distance+1;
            else if (t != 'X') cua.push(cell(c.x-1,c.y,c.distance+1));
            }
        if (c.y-1 >= 0 and not visited[c.x][c.y-1]) {   //UP
            visited[c.x][c.y-1] = true;
/* +=================== DEBUG ===================+ */
this_thread::sleep_for(chrono::milliseconds(1000/FPS)); //
debug_print(x,y,map,visited);              //
/* +=============================================+ */
            char t = map[c.x][c.y-1];
            if (t == 't') return c.distance+1;
            else if (t != 'X') cua.push(cell(c.x,c.y-1,c.distance+1));
            }
        cua.pop();
    }
    return -1;
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
    if (d == -1) cout << "no treasure can be reached" << endl;
    else cout << "minimum distance: " << d << endl;
}