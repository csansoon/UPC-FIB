#include <iostream>
#include <vector>
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
        if (x == i and y == j) cout << yellow_b;
        else if (been_here[i][j] and map[i][j] == 't') cout << green_b;
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



int counter = 0;
void search_treasure(int x, int y, vector<vector<char>>& map, vector<vector<bool>>& been_here) {

/* +=================== DEBUG ===================+ */
this_thread::sleep_for(chrono::milliseconds(1000/FPS)); //
debug_print(x,y,map,been_here);              //
/* +=============================================+ */

    been_here[x][y] = true;
    if (map[x][y] == 't')
        ++counter;
    if (map[x][y] == '.' or map[x][y] == 't') {
        if (x+1 < map.size() and not been_here[x+1][y])       search_treasure(x+1,y,map,been_here);
        if (y+1 < map[0].size() and not been_here[x][y+1])    search_treasure(x,y+1,map,been_here);
        if (x-1 >= 0 and not been_here[x-1][y])               search_treasure(x-1,y,map,been_here);
        if (y-1 >= 0 and not been_here[x][y-1])               search_treasure(x,y-1,map,been_here);
    }
    return;
}

int main() {
    int x,y;
    cin >> x >> y;
    vector<vector<char>> map (x,vector<char>(y));
    vector<vector<bool>> been_here (x,vector<bool>(y,false));
    for (int i = 0; i < x; ++i) for (int j = 0; j < y; ++j) cin >> map[i][j];

    cin >> x >> y;
    search_treasure(x-1,y-1,map,been_here);
    cout << counter << endl;
}