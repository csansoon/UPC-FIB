#include <iostream>
#include <utility>
#include <vector>
using namespace std;

void expand(int x, int y, vector<vector<char>>& map) {
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
        
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                cout << map[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
}