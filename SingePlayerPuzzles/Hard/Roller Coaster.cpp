#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int L;
    int C;
    int N;
    cin >> L >> C >> N; cin.ignore();
    
    vector<int> queue(N);
    
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi; cin.ignore();

        queue[i] = Pi;
    }

    long long earnings = 0;
    if (C < N)
    {
        int index = 0;
        for (int c = 0; c < C; ++c)
        {
            int beginIndex = index;
            int remainingSpace = L;
            while (queue[index] <= remainingSpace)
            {
                remainingSpace -= queue[index];
    
                if (index < queue.size()-1)
                    ++index;
                else
                    index = 0;
                
                // Don't let the same people board twice
                if (index == beginIndex)
                    break;
            }
            
            earnings += L - remainingSpace;
        }
    }
    else // Less groups than rides
    {
        // Calculate the earning for each group standing in the front
        vector<pair<int, int>> earningsQueue(N);
        for (int i = 0; i < N; ++i)
        {
            int index = i;
            int beginIndex = index;
            int remainingSpace = L;
            while (queue[index] <= remainingSpace)
            {
                remainingSpace -= queue[index];
    
                if (index < queue.size()-1)
                    ++index;
                else
                    index = 0;
                
                // Don't let the same people board twice
                if (index == beginIndex)
                    break;
            }
            
            earningsQueue[i] = {L - remainingSpace, index};
        }
        
        // Run the algorithm on the cached values
        int index = 0;
        for (int c = 0; c < C; ++c)
        {
            earnings += earningsQueue[index].first;
            index = earningsQueue[index].second;
        }
    }
    
    cout << earnings << endl;
}
