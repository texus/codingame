#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    
    vector<vector<bool>> grid(height, vector<bool>(width, false));
    
    for (int i = 0; i < height; i++) {
        string line; // width characters, each either 0 or .
        getline(cin, line);
        
        for (unsigned int j = 0; j < line.size(); ++j) {
            if (line[j] == '0') {
                grid[i][j] = true;
            }
        }
    }

    for (unsigned int h = 0; h < height; ++h) {
        for (unsigned int w = 0; w < width; ++w) {
            if (grid[h][w]) {
                cout << w << " " << h << " ";
                bool found = false;
                for (unsigned int i = w+1; i < width; ++i) {
                    if (grid[h][i]) {
                        cout << i << " " << h << " ";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "-1 -1 ";
                }
                
                found = false;
                for (unsigned int j = h+1; j < height; ++j) {
                    if (grid[j][w]) {
                        cout << w << " " << j << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "-1 -1" << endl;
                }
            }
        }
    }
}
