#include <iostream>
#include <vector>
using namespace std;

bool valid(int i, int j, int x, int y) {
    if (x == i or y == j) return false;
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> map(n,vector<bool>(m,false));
    for (int i = 0; i < n/2; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int x = 0; x < n; ++x) {
                for (int y = 0; y < m; ++y) {
                   if (valid(i,j,x,y)) {


                       for (int ii = 0; ii < n; ++ii) {
                           for (int jj = 0; jj < m; ++jj) {
                               if (ii == i and jj == j) cout << "R";
                               else if (ii == x and jj == y) cout << "R";
                               else cout << ".";
                           }
                           cout << endl;
                       }    
                       cout << endl;
                   } 
                }
            }
        }
    }
}