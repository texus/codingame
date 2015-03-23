#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string LON;
    cin >> LON; cin.ignore();
    string LAT;
    cin >> LAT; cin.ignore();
    int N;
    cin >> N; cin.ignore();

    auto COMMA_POS_LON = LON.find(",");
    assert(COMMA_POS_LON != string::npos);
    
    auto COMMA_POS_LAT = LAT.find(",");
    assert(COMMA_POS_LAT != string::npos);
    
    LON.replace(COMMA_POS_LON, 1, 1, '.');
    LAT.replace(COMMA_POS_LAT, 1, 1, '.');
    
    double longitudeA = stod(LON) / 180.0 * M_PI;
    double latitudeA = stod(LAT) / 180.0 * M_PI;

    double minDist = numeric_limits<double>::infinity();
    string address;
    
    for (int i = 0; i < N; i++) {
        string DEFIB;
        getline(cin, DEFIB);
        
        auto FIRST_SEMICOLON = DEFIB.find(";");
        assert(FIRST_SEMICOLON != string::npos);
        
        auto SECOND_SEMICOLON = DEFIB.find(";", FIRST_SEMICOLON + 1);
        assert(SECOND_SEMICOLON != string::npos);
        
        auto THIRD_SEMICOLON = DEFIB.find(";", SECOND_SEMICOLON + 1);
        assert(THIRD_SEMICOLON != string::npos);
        
        auto FOURTH_SEMICOLON = DEFIB.find(";", THIRD_SEMICOLON + 1);
        assert(FOURTH_SEMICOLON != string::npos);
        
        auto FIFTH_SEMICOLON = DEFIB.find(";", FOURTH_SEMICOLON + 1);
        assert(FIFTH_SEMICOLON != string::npos);

        COMMA_POS_LON = DEFIB.find(",", FOURTH_SEMICOLON + 1);
        assert(COMMA_POS_LON != string::npos);
        
        COMMA_POS_LAT = DEFIB.find(",", FIFTH_SEMICOLON + 1);
        assert(COMMA_POS_LAT != string::npos);
        
        DEFIB.replace(COMMA_POS_LON, 1, 1, '.');
        DEFIB.replace(COMMA_POS_LAT, 1, 1, '.');
        
        double longitudeB = stod(DEFIB.substr(FOURTH_SEMICOLON + 1, FIFTH_SEMICOLON - FOURTH_SEMICOLON - 1)) / 180.0 * M_PI;
        double latitudeB = stod(DEFIB.substr(FIFTH_SEMICOLON + 1)) / 180.0 * M_PI;

        double x = (longitudeB - longitudeA) * cos((latitudeA + latitudeB) / 2.0);
        double y = (latitudeB - latitudeA);
        double d = sqrt(x*x + y*y) * 6371;

        if (d < minDist)
        {
            minDist = d;
            address = DEFIB.substr(FIRST_SEMICOLON + 1, SECOND_SEMICOLON - FIRST_SEMICOLON - 1);
        }
    }
    
    cout << address << endl;
}
