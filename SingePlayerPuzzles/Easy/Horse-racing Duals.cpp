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
    vector<int> P;
    int minDist = 10000000;
    
    int maxNr = 0;
    int minNr = 10000000;
    
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi; cin.ignore();
        
        if (Pi > maxNr)
        {
            int dist = Pi - maxNr;
            if (dist < minDist)
                minDist = dist;
            
            maxNr = Pi;
        }
        else if (Pi < minNr)
        {
            int dist = minNr - Pi;
            if (dist < minDist)
                minDist = dist;
            
            minNr = Pi;
        }
        else
        {
            for (int j = 0; j < i; ++j)
            {
                int dist = abs(P[j] - Pi);
                if (dist < minDist)
                    minDist = dist;
            }
        }
        
        P.push_back(Pi);
    }
    
    cout << minDist << endl;
}
