#include <iostream>
#include <utility>
#include <vector>
using namespace std;

/* +=================== DEBUG ===================+ */
#include <chrono>
#include <thread>
#include <map>
const string    reset       = "\033[1;0m";
const string    magenta     = "\033[1;35m";
const string    red_b       = "\033[1;41m";
const string    green_b     = "\033[1;42m";
const string    yellow_b    = "\033[1;43m";
const string    blue_b      = "\033[1;44m";
const string    magenta_b   = "\033[1;45m";
const string    cyan_b      = "\033[1;46m";
const string    white_b     = "\033[1;47m";
const string    inverse     = "\033[1;7m";
const string    underline   = "\033[1;4m";
map<char,string> color;
int counter;

string set_color(char c) {
if (color.find(c) == color.end()) {
    if (counter == 0) color[c] = red_b;
    else if (counter == 1) color[c] = yellow_b;
    else if (counter == 2) color[c] = cyan_b;
    else if (counter == 3) color[c] = green_b;
    else if (counter == 4) color[c] = blue_b;
    else if (counter == 5) color[c] = magenta_b;
    ++counter;
    if (counter > 5) counter = 0;
}
return color[c];
}


void debug_print(int x, int y, vector<vector<char>>& map) {
system("clear");
cout << magenta;
cout << "+";
for (int i = 0; i < map[0].size(); ++i) cout << "=";
cout << "+";
cout << reset << endl;
for (int i = 0; i < map.size(); ++i) {
    cout << magenta << "|" << reset;
    for (int j = 0; j < map[0].size(); ++j) {
        if (map[i][j] == '#') cout << inverse;
        else if (map[i][j] != '.') {
            cout << set_color(map[i][j]);
        }
        if (i == x and j == y) cout << underline;
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


void expand(int x, int y, vector<vector<char>>& map) {

/* +=================== DEBUG ===================+ */
this_thread::sleep_for(chrono::milliseconds(100)); //
debug_print(x,y,map);                              //
/* +=============================================+ */


    if (x+1 < map.size() and map[x+1][y] == '.') {
        map[x+1][y] = map[x][y];
        expand(x+1,y,map);
    }
    if (y+1 < map[0].size() and map[x][y+1] == '.') {
        map[x][y+1] = map[x][y];
        expand(x,y+1,map);
    }
    if (x-1 >= 0 and map[x-1][y] == '.') {
        map[x-1][y] = map[x][y];
        expand(x-1,y,map);
    }
    if (y-1 >= 0 and map[x][y-1] == '.') {
        map[x][y-1] = map[x][y];
        expand(x,y-1,map);
    }
}

int main() {
    int x,y;
    while(cin >> x >> y) {
        vector<pair<int,int>> letters;
        vector<vector<char>> map (x,vector<char>(y));
        for (int i = 0; i < x; ++i) for (int j = 0; j < y; ++j) {
            cin >> map[i][j];
            if (map[i][j] != '.' and map[i][j] != '#') letters.push_back(make_pair(i,j));
        }

        for (int i = 0; i < letters.size(); ++i) expand(letters[i].first,letters[i].second,map);
        /*
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                cout << map[i][j];
            }
            cout << endl;
        }
        cout << endl;
        */
    }
}