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
    int LX; // the X position of the light of power
    int LY; // the Y position of the light of power
    int TX; // Thor's starting X position
    int TY; // Thor's starting Y position
    cin >> LX >> LY >> TX >> TY; cin.ignore();

    // game loop
    while (1) {
        int E; // The level of Thor's remaining energy, representing the number of moves he can still make.
        cin >> E; cin.ignore();

        if (LX > TX)
        {
            if (LY > TY)
            {
                TX += 1;
                TY += 1;
                cout << "SE" << endl;
            }
            else if (LY < TY)
            {
                TX += 1;
                TY -= 1;
                cout << "NE" << endl;
            }
            else
            {
                TX += 1;
                cout << "E" << endl;
            }
        }
        else if (LX < TX)
        {
            if (LY > TY)
            {
                TX -= 1;
                TY += 1;
                cout << "SW" << endl;
            }
            else if (LY < TY)
            {
                TX -= 1;
                TY -= 1;
                cout << "NW" << endl;
            }
            else
            {
                TX -= 1;
                cout << "W" << endl;
            }
        }
        else
        {
            if (LY > TY)
            {
                TY += 1;
                cout << "S" << endl;
            }
            else if (LY < TY)
            {
                TY -= 1;
                cout << "N" << endl;
            }
        }
    }
}
