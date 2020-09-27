#include <iostream>
#include <vector>
using namespace std;

/* +=================== DEBUG ===================+ */
#include <chrono>
#include <thread>
const string    reset       = "\033[1;0m";
const string    magenta     = "\033[1;35m";
const string    red_b       = "\033[1;41m";
const string    green_b     = "\033[1;42m";
const string    yellow_b    = "\033[1;43m";
const string    blue_b      = "\033[1;44m";
void debug_print(int x, int y, vector<vector<char>>& map, vector<vector<bool>>& been_here, bool found) {
system("clear");
cout << magenta;
cout << "+";
for (int i = 0; i < map[0].size(); ++i) cout << "=";
cout << "+";
cout << reset << endl;
for (int i = 0; i < map.size(); ++i) {
    cout << magenta << "|" << reset;
    for (int j = 0; j < map[0].size(); ++j) {
        if (x == i and y == j and not found) cout << yellow_b;
        else if (x == i and y == j and found) cout << green_b;
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

bool search_treasure(int x, int y, vector<vector<char>>& map, vector<vector<bool>>& been_here) {

/* +=================== DEBUG ===================+ */
this_thread::sleep_for(chrono::milliseconds(100)); //
debug_print(x,y,map,been_here,false);              //
/* +=============================================+ */

    if (x >= map.size() or y >= map[0].size() or x < 0 or y < 0) return false;
    if (been_here[x][y]) return false;
    been_here[x][y] = true;
    if (map[x][y] == 't') {

/* +============ DEBUG ============+ */
debug_print(x,y,map,been_here,true); //
/* +===============================+ */

        return true;}
    if (map[x][y] == '.') {
        if (search_treasure(x+1,y,map,been_here)) return true;
        if (search_treasure(x,y+1,map,been_here)) return true;
        if (search_treasure(x-1,y,map,been_here)) return true;
        if (search_treasure(x,y-1,map,been_here)) return true;
    }
    return false;
}

int main() {
    int x,y;
    cin >> x >> y;
    vector<vector<char>> map (x,vector<char>(y));
    vector<vector<bool>> been_here (x,vector<bool>(y,false));
    for (int i = 0; i < x; ++i) for (int j = 0; j < y; ++j) cin >> map[i][j];

    cin >> x >> y;
    if (search_treasure(x-1,y-1,map,been_here)) cout << "yes" << endl;
    else cout << "no" << endl;
}