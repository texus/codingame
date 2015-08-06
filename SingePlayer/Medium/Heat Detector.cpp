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
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore();
    
    int left = X0;
    int top = Y0;
    int width;
    int height;
    bool firstTime = true;

    // game loop
    while (1) {
        string BOMB_DIR; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> BOMB_DIR; cin.ignore();
        
        if (firstTime)
        {
            if (BOMB_DIR == "U")
            {
                width = 0;
                height = Y0;
            }
            else if (BOMB_DIR == "D")
            {
                width = 0;
                height = H - Y0;
            }
            else if (BOMB_DIR == "L")
            {
                width = X0;
                height = 0;
            }
            else if (BOMB_DIR == "R")
            {
                width = W - X0;
                height = 0;
            }
            if (BOMB_DIR == "UL")
            {
                width = X0;
                height = Y0;
            }
            else if (BOMB_DIR == "UR")
            {
                width = W - X0;
                height = Y0;
            }
            else if (BOMB_DIR == "DL")
            {
                width = X0;
                height = H - Y0;
            }
            else if (BOMB_DIR == "DR")
            {
                width = W - X0;
                height = H - Y0;
            }
            
            firstTime = false;
        }

        if (BOMB_DIR == "D")
        {
            Y0 = top + (int)ceil(height/2.0);
        }
        else if (BOMB_DIR == "U")
        {
            Y0 = top - (int)ceil(height/2.0);
        }
        else if (BOMB_DIR == "L")
        {
            X0 = left - (int)ceil(width/2.0);
        }
        else if (BOMB_DIR == "R")
        {
            X0 = left + (int)ceil(width/2.0);
        }
        else if (BOMB_DIR == "UL")
        {
            X0 = left - (int)ceil(width/2.0);
            Y0 = top - (int)ceil(height/2.0);
        }
        else if (BOMB_DIR == "UR")
        {
            X0 = left + (int)ceil(width/2.0);
            Y0 = top - (int)ceil(height/2.0);
        }
        else if (BOMB_DIR == "DL")
        {
            X0 = left - (int)ceil(width/2.0);
            Y0 = top + (int)ceil(height/2.0);
        }
        else if (BOMB_DIR == "DR")
        {
            X0 = left + (int)ceil(width/2.0);
            Y0 = top + (int)ceil(height/2.0);
        }
        
        if (BOMB_DIR == "UL" || BOMB_DIR == "UR" || BOMB_DIR == "DL" || BOMB_DIR == "DR")
        {
            left = X0;
            top = Y0;
            width = width/2;
            height = height/2;
        }
        else if (BOMB_DIR == "U" || BOMB_DIR == "D")
        {
            top = Y0;
            width = 1;
            height = height/2;
        }
        else if (BOMB_DIR == "L" || BOMB_DIR == "R")
        {
            left = X0;
            width = width/2;
            height = 1;
        }
        
        cout << X0 << " " << Y0 << endl;
    }
}
