#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int W; // width of the building.
int H; // height of the building.
vector<vector<bool>> windows;

int minX = 0;
int minY = 0;
int maxX;
int maxY;

double dist(pair<int, int> point1, pair<int, int> point2)
{
    return sqrt(pow(point1.first - point2.first, 2) + pow(point1.second - point2.second, 2));
}

// Centroid of set of points is calculated by:
// ((x1,y1) + (x2,y2) + ... + (xk,yk)) / k
// k is the amount of windows where the bomb might still be here
pair<int, int> calculateCentroid()
{
    int k = 0;
    int totalX = 0;
    int totalY = 0;
    for (int h = minY; h < maxY; ++h)
    {
        for (int w = minX; w < maxX; ++w)
        {
            if (windows[h][w])
            {
                k++;
                totalX += w;
                totalY += h;
            }
        }
    }

    return {int(round(totalX / (double)k)), int(round(totalY / (double)k))};
}

int main()
{
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore();
    
    windows = vector<vector<bool>>(H, vector<bool>(W, true));
    maxX = W;
    maxY = H;
    
    pair<int, int> prevOldPosition{X0, Y0};
    pair<int, int> oldPosition{X0, Y0};
    pair<int, int> newPosition{X0, Y0};

    // game loop
    bool centroid = false;
    while (1) {
        string BOMB_DIST; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> BOMB_DIST; cin.ignore();
        
        // The normal calculations are only done up to 1000x1000 unexplored windows
        if ((maxX - minX) * (maxY - minY) <= 1000000)
        {
            // Mark windows where the bomb can no longer be
            if (BOMB_DIST == "WARMER")
            {
                for (int h = minY; h < maxY; ++h)
                {
                    for (int w = minX; w < maxX; ++w)
                    {
                        if (windows[h][w] && dist(oldPosition, {w,h}) <= dist(newPosition, {w,h}))
                            windows[h][w] = false;
                    }
                }
            }
            else if (BOMB_DIST == "COLDER")
            {
                for (int h = minY; h < maxY; ++h)
                {
                    for (int w = minX; w < maxX; ++w)
                    {
                        if (windows[h][w] && dist(oldPosition, {w,h}) >= dist(newPosition, {w,h}))
                            windows[h][w] = false;
                    }
                }
            }
            else if (BOMB_DIST == "SAME")
            {
                for (int h = minY; h < maxY; ++h)
                {
                    for (int w = minX; w < maxX; ++w)
                    {
                        if (windows[h][w] && dist(oldPosition, {w,h}) != dist(newPosition, {w,h}))
                            windows[h][w] = false;
                    }
                }
            }
    
            // Jump to the centroid of the part where the bomb can still be
            prevOldPosition = oldPosition;
            oldPosition = newPosition;
            newPosition = calculateCentroid();
            
            // Don't jump back or stand still, instead move one square in some direction
            if (newPosition == oldPosition || newPosition == prevOldPosition)
            {
                if (newPosition.first > 0 && windows[newPosition.second][newPosition.first-1])
                    newPosition.first--;
                else if (newPosition.second > 0 && windows[newPosition.second-1][newPosition.first])
                    newPosition.second--;
                else if (newPosition.second < H-1 && windows[newPosition.second+1][newPosition.first])
                    newPosition.second++;
                else if (newPosition.first < W-1 && windows[newPosition.second][newPosition.first+1])
                    newPosition.first++;
                else if (newPosition.first > 0 && newPosition.second > 0 && windows[newPosition.second-1][newPosition.first-1])
                {
                    newPosition.first--;
                    newPosition.second--;
                }
                else if (newPosition.first > 0 && newPosition.second < H-1 && windows[newPosition.second+1][newPosition.first-1])
                {
                    newPosition.first--;
                    newPosition.second++;
                }
                else if (newPosition.first < W-1 && newPosition.second > 0 && windows[newPosition.second-1][newPosition.first+1])
                {
                    newPosition.first++;
                    newPosition.second--;
                }
                else if (newPosition.first < W-1 && newPosition.second < H-1 && windows[newPosition.second+1][newPosition.first+1])
                {
                    newPosition.first++;
                    newPosition.second++;
                }
            }
        }
        else // There are too many windows for normal calculation
        {
            if (BOMB_DIST == "WARMER")
            {
                if (newPosition.first > oldPosition.first)
                    minX = oldPosition.first + (newPosition.first - oldPosition.first);
                else if (newPosition.first < oldPosition.first)
                    maxX = oldPosition.first - (oldPosition.first - newPosition.first);
                
                if (newPosition.second > oldPosition.second)
                    minY = oldPosition.second + (newPosition.second - oldPosition.second);
                else if (newPosition.second < oldPosition.second)
                    maxY = oldPosition.second - (oldPosition.second - newPosition.second);
            }
            else if (BOMB_DIST == "COLDER")
            {
                if (newPosition.first > oldPosition.first)
                    maxX = newPosition.first - (newPosition.first - oldPosition.first);
                else if (newPosition.first < oldPosition.first)
                    minX = newPosition.first + (oldPosition.first - newPosition.first);
                
                if (newPosition.second > oldPosition.second)
                    maxY = newPosition.second - (newPosition.second - oldPosition.second);
                else if (newPosition.second < oldPosition.second)
                    minY = newPosition.second + (oldPosition.second - newPosition.second);
            }

            prevOldPosition = oldPosition;
            oldPosition = newPosition;
            newPosition = {(maxX - minX) / 2, (maxY - minY) / 2};
        }
        
        cout << newPosition.first << " " << newPosition.second << endl;
    }
}
