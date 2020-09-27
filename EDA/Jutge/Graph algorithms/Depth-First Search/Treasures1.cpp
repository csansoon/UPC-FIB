#include <iostream>
#include <vector>
using namespace std;


bool search_treasure(int x, int y, vector<vector<char>>& map, vector<vector<bool>>& been_here) {
    if (x >= map.size() or y >= map[0].size() or x < 0 or y < 0) return false;
    if (been_here[x][y]) return false;
    been_here[x][y] = true;
    if (map[x][y] == 't') {
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