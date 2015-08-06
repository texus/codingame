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
    int N; // the number of points used to draw the surface of Mars.
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int LAND_X; // X coordinate of a surface point. (0 to 6999)
        int LAND_Y; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> LAND_X >> LAND_Y; cin.ignore();
    }
    
    int VSold = 0;

    // game loop
    while (1) {
        int X;
        int Y;
        int HS; // the horizontal speed (in m/s), can be negative.
        int VS; // the vertical speed (in m/s), can be negative.
        int F; // the quantity of remaining fuel in liters.
        int R; // the rotation angle in degrees (-90 to 90).
        int P; // the thrust power (0 to 4).
        cin >> X >> Y >> HS >> VS >> F >> R >> P; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        if (VS < -39)
            cout << 0 << " " << 4 << endl;
        /*else if (VS < -24)
            cout << 0 << " " << 3 << endl;
        else if (VS < -18)
            cout << 0 << " " << 2 << endl;
        else if (VS < -12)
            cout << 0 << " " << 1 << endl;*/
        else
            cout << 0 << " " << 0 << endl;
        
        //cout << "-20 3" << endl; // R P. R is the desired rotation angle. P is the desired thrust power.
    }
}
