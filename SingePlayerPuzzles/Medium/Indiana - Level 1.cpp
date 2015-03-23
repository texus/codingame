#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    map<pair<int, int>, int> grid;
    
    int W; // number of columns.
    int H; // number of rows.
    cin >> W >> H; cin.ignore();
    for (int i = 0; i < H; i++) {
        string LINE; // represents a line in the grid and contains W integers. Each integer represents one room of a given type.
        getline(cin, LINE);
        
        stringstream ss(LINE);
        for (int j = 0; j < W; ++j)
        {
            string temp;
            ss >> temp;
            grid[{j, i}] = stoi(temp);
        }
    }
    int EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
    cin >> EX; cin.ignore();

    // game loop
    while (1) {
        int XI;
        int YI;
        string POS;
        cin >> XI >> YI >> POS; cin.ignore();
        
        switch(grid[{XI, YI}])
        {
        case 1:
        case 3:
        case 7:
        case 8:
        case 9:
        case 12:
        case 13:
            cout << XI << " " << (YI+1) << endl;
            break;
            
        case 2:
        case 6:
        {
            if (POS == "LEFT")
                cout << (XI+1) << " " << YI << endl;
            else if (POS == "RIGHT")
                cout << (XI-1) << " " << YI << endl;
            break;
        }
        
        case 4:
        {
            if (POS == "TOP")
                cout << (XI-1) << " " << YI << endl;
            else if (POS == "RIGHT")
                cout << XI << " " << (YI+1) << endl;
            break;
        }
        
        case 5:
        {
            if (POS == "TOP")
                cout << (XI+1) << " " << YI << endl;
            else if (POS == "LEFT")
                cout << XI << " " << (YI+1) << endl;
            break;
        }
        
        case 10:
            cout << (XI-1) << " " << YI << endl;
            break;
        
        case 11:
            cout << (XI+1) << " " << YI << endl;
            break;
            
        default:
            cerr << "Unknown type" << endl;
        };
    }
}
