#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{

    // game loop
    while (1) {
        int biggestMH = 0;
        int biggestMHPos = 0;
        
        int SX;
        int SY;
        cin >> SX >> SY; cin.ignore();
        for (int i = 0; i < 8; i++) {
            int MH; // represents the height of one mountain, from 9 to 0. Mountain heights are provided from left to right.
            cin >> MH; cin.ignore();
            
            if (biggestMH < MH)
            {
                biggestMH = MH;
                biggestMHPos = i;
            }
        }

        // either:  FIRE (ship is firing its phase cannons) or HOLD (ship is not firing).
        if (biggestMH != 0 && biggestMHPos == SX)
            cout << "FIRE" << endl;
        else
            cout << "HOLD" << endl;
    }
}
