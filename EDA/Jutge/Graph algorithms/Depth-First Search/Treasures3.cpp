#include <iostream>
#include <vector>
using namespace std;


int counter = 0;
void search_treasure(int x, int y, vector<vector<char>>& map, vector<vector<bool>>& been_here) {
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