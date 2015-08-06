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
    double g = -3.711;
    vector<pair<int, int>> land;
    
    int N; // the number of points used to draw the surface of Mars.
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int LAND_X; // X coordinate of a surface point. (0 to 6999)
        int LAND_Y; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> LAND_X >> LAND_Y; cin.ignore();
        
        land.push_back({LAND_X, LAND_Y});
    }
    
    // Search the landing spot
    pair<int, int> landingSpot;
    for (int i = 1; i < land.size(); ++i)
    {
        if (land[i-1].second == land[i].second)
        {
            landingSpot = {(land[i-1].first + land[i].first) / 2, land[i].second};
            break;
        }
    }
    
    // Find the maximum height
    int maxHeight = 0;
    for (int i = 0; i < land.size(); ++i)
        maxHeight = max(maxHeight, land[i].second);

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
        
        
        // VSpeed = VSpeed + (Power * sin(Angle)) + g
        // HSpeed = HSpeed + (Power * cos(Angle))
        // X = X + HSpeed
        // Y = Y + VSpeed
        // Fuel = Fuel - Power
        
        // Stay above max height when going to landing spot
        if (X < landingSpot.first - 400)
        {
            // Calculate the height of peaks between us and the landing zone
            maxHeight = landingSpot.second;
            for (int i = 0; i < land.size(); ++i)
            {
                if ((land[i].first < landingSpot.first - 400) && (land[i].first > X))
                    maxHeight = max(maxHeight, land[i].second);
            }
                
            if (HS < 20)
                R = -20;
            
            if (HS >= 20)
                R = 30;
            else if (HS <= -20)
                R = -30;
                
            if (Y + 10*VS < Y - landingSpot.second)
                P = 4;
            else
                P = min(max(-VS - 36, 0), 4);
            
            // Don't go below peaks
            if ((Y - VS*VS <= maxHeight) /*&& (maxHeight != landingSpot.second)*/
             && (X < landingSpot.first - 1000))
            {
                P = 4;
                R = min(max(R, -3), 3);
            }
        }
        else if (X > landingSpot.first + 400)
        {
            // Calculate the height of peaks between us and the landing zone
            maxHeight = landingSpot.second;
            for (int i = 0; i < land.size(); ++i)
            {
                if ((land[i].first > landingSpot.first + 400) && (land[i].first < X))
                    maxHeight = max(maxHeight, land[i].second);
            }
            
            if (HS > -20)
                R = 20;
            
            if (HS >= 20)
                R = 30;
            else if (HS <= -20)
                R = -30;

            if ((VS < 0) && (10*VS < Y - landingSpot.second))
                P = 4;
            else
                P = min(max(-VS - 36, 0), 4);

            // Don't go below peaks
            if ((Y - VS*VS <= maxHeight) /*&& (maxHeight != landingSpot.second)*/
             && (X > landingSpot.first + 1000))
            {
                P = 4;
                R = min(max(R, -3), 3);
            }
        }
        else
        {
            // HS =  50  => Angle =  45
            // HS =   0  => Angle =   0
            // HS = -50  => Angle = -45
            R = min(max((int)(HS / 30.0 * 45.0), -90), 90);
            
            // Angle = 45  =>  P = 4
            // Angle =  0  =>  P >= 0
            P = min(max(-VS - 30, max(abs((int)((R/45.0)*4)), 0)), 4);
        }
        
        // Angle == 0 when landing
        if (Y - landingSpot.second <= ((abs(2*R / 15) + 1) * -VS))
            R = 0;

        // Emergency landing
        if (((R / 15) + 1) * P >= F)
            R = 0;
        
        // Set the wanted rotation and power
        cout << R << " " << P << endl;
    }
}
