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
    vector<pair<int, int>> positions;
    
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int X;
        int Y;
        cin >> X >> Y; cin.ignore();
        
        positions.push_back({X, Y});
    }

    // Calculate the median y position
    sort(positions.begin(), positions.end(), [](pair<int, int> p1, pair<int, int> p2){ return p1.second < p2.second; });
    int mainCableY;
    if (positions.size() % 2)
        mainCableY = positions[positions.size() / 2].second;
    else
        mainCableY = (positions[(positions.size() / 2)-1].second + positions[positions.size() / 2].second) / 2;
    
    // Calculate the length of the main cable
    int minPosX = numeric_limits<int>::max();
    int maxPosX = numeric_limits<int>::min();
    for (auto& pos : positions)
    {
        if (pos.first < minPosX)
            minPosX = pos.first;
        if (pos.first > maxPosX)
            maxPosX = pos.first;
    }
    
    int mainCableLength = maxPosX - minPosX;

    // Calculate the total length of the cables
    long long totalLength = mainCableLength;
    for (auto& pos : positions)
        totalLength += abs(mainCableY - pos.second);
    
    cout << totalLength << endl;
}
