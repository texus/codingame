#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lanes(4);
std::string::size_type lastHole;
std::string::size_type trackLength;

struct State
{
    unsigned int speed;
    unsigned int x;
    vector<unsigned int> y;
};

// Returns casualties and best move
pair<unsigned int, std::string> decide(State state)
{
    // Just keep going once you pass all holes
    if (state.x >= lastHole)
        return {0, "WAIT"};

    // Don't just stand there, move!
    if (state.speed == 0)
        return {0, "SPEED"};

    pair<unsigned int, string> minCasualties = {state.y.size(), "WAIT"};

    // Faster, go faster! This must be the default move to make it in time.
    {
        State newState = state;
        newState.speed += 1;
        newState.x += newState.speed;

        for (auto y : state.y)
        {
            for (unsigned int x = state.x + 1; x <= newState.x; ++x)
            {
                if (lanes[y][x] == '0')
                {
                    newState.y.erase(std::find(newState.y.begin(), newState.y.end(), y));
                    break;
                }
            }
        }

        if (newState.y.size() > 0)
        {
            unsigned int casualties = (state.y.size() - newState.y.size()) + decide(newState).first;
            if (casualties == 0)
                return {0, "SPEED"};

            if (casualties < minCasualties.first)
                minCasualties = {casualties, "SPEED"};
        }
    }

    // Keep going
    {
        State newState = state;
        newState.x += newState.speed;

        for (auto y : state.y)
        {
            for (unsigned int x = state.x + 1; x <= newState.x; ++x)
            {
                if (lanes[y][x] == '0')
                {
                    newState.y.erase(std::find(newState.y.begin(), newState.y.end(), y));
                    break;
                }
            }
        }

        if (newState.y.size() > 0)
        {
            unsigned int casualties = (state.y.size() - newState.y.size()) + decide(newState).first;
            if (casualties == 0)
                return {0, "WAIT"};

            if (casualties < minCasualties.first)
                minCasualties = {casualties, "WAIT"};
        }
    }

    // We lose at least one machine by just moving forward, so what about jumping?
    {
        State newState = state;
        newState.x += newState.speed;

        for (auto y : state.y)
        {
            if (lanes[y][newState.x] == '0')
                newState.y.erase(std::find(newState.y.begin(), newState.y.end(), y));
        }

        if (newState.y.size() > 0)
        {
            unsigned int casualties = (state.y.size() - newState.y.size()) + decide(newState).first;
            if (casualties == 0)
                return {0, "JUMP"};

            if (casualties < minCasualties.first)
                minCasualties = {casualties, "JUMP"};
        }
    }

    // Try moving up
    if (std::find(state.y.begin(), state.y.end(), 0) == state.y.end())
    {
        State newState = state;
        newState.x += newState.speed;
        newState.y = {};

        for (auto y : state.y)
        {
            bool stillAlive = true;
            for (unsigned int x = state.x + 1; x <= newState.x - 1; ++x)
            {
                if (lanes[y][x] == '0')
                {
                    stillAlive = false;
                    break;
                }
            }
            for (unsigned int x = state.x + 1; x <= newState.x; ++x)
            {
                if (lanes[y-1][x] == '0')
                {
                    stillAlive = false;
                    break;
                }
            }

            if (stillAlive)
                newState.y.push_back(y - 1);
        }

        if (newState.y.size() > 0)
        {
            unsigned int casualties = (state.y.size() - newState.y.size()) + decide(newState).first;
            if (casualties == 0)
                return {0, "UP"};

            if (casualties < minCasualties.first)
                minCasualties = {casualties, "UP"};
        }
    }

    // Try moving down
    if (std::find(state.y.begin(), state.y.end(), lanes.size()-1) == state.y.end())
    {
        State newState = state;
        newState.x += newState.speed;
        newState.y = {};

        for (auto y : state.y)
        {
            bool stillAlive = true;
            for (unsigned int x = state.x + 1; x <= newState.x - 1; ++x)
            {
                if (lanes[y][x] == '0')
                {
                    stillAlive = false;
                    break;
                }
            }
            for (unsigned int x = state.x + 1; x <= newState.x; ++x)
            {
                if (lanes[y+1][x] == '0')
                {
                    stillAlive = false;
                    break;
                }
            }

            if (stillAlive)
                newState.y.push_back(y + 1);
        }

        if (newState.y.size() > 0)
        {
            unsigned int casualties = (state.y.size() - newState.y.size()) + decide(newState).first;
            if (casualties == 0)
                return {0, "DOWN"};

            if (casualties < minCasualties.first)
                minCasualties = {casualties, "DOWN"};
        }
    }

    // Slow down, will ya?
    if (state.speed > 1)
    {
        State newState = state;
        newState.speed -= 1;
        newState.x += newState.speed;

        for (auto y : state.y)
        {
            for (unsigned int x = state.x + 1; x <= newState.x; ++x)
            {
                if (lanes[y][x] == '0')
                {
                    newState.y.erase(std::find(newState.y.begin(), newState.y.end(), y));
                    break;
                }
            }
        }

        if (newState.y.size() > 0)
        {
            unsigned int casualties = (state.y.size() - newState.y.size()) + decide(newState).first;
            if (casualties == 0)
                return {0, "SLOW"};

            if (casualties < minCasualties.first)
                minCasualties = {casualties, "SLOW"};
        }
    }

    // We can't all make it, choose a move that minimizes casualties
    return minCasualties;
}

int main()
{
    int M; // the amount of motorbikes to control
    cin >> M; cin.ignore();
    int V; // the minimum amount of motorbikes that must survive
    cin >> V; cin.ignore();
    cin >> lanes[0]; cin.ignore();
    cin >> lanes[1]; cin.ignore();
    cin >> lanes[2]; cin.ignore();
    cin >> lanes[3]; cin.ignore();

    lastHole = 0;
    lastHole = max(lastHole, (lanes[0].rfind('0') != string::npos) ? lanes[0].rfind('0') : 0);
    lastHole = max(lastHole, (lanes[1].rfind('0') != string::npos) ? lanes[1].rfind('0') : 0);
    lastHole = max(lastHole, (lanes[2].rfind('0') != string::npos) ? lanes[2].rfind('0') : 0);
    lastHole = max(lastHole, (lanes[3].rfind('0') != string::npos) ? lanes[3].rfind('0') : 0);
    trackLength = lanes[0].length();

    // game loop
    while (1) {
        int S; // the motorbikes' speed
        cin >> S; cin.ignore();

        State currentState;
        currentState.speed = S;

        for (int i = 0; i < M; i++) {
            int X; // x coordinate of the motorbike
            int Y; // y coordinate of the motorbike
            int A; // indicates whether the motorbike is activated "1" or detroyed "0"
            cin >> X >> Y >> A; cin.ignore();

            if (A) {
                currentState.x = X;
                currentState.y.push_back(Y);
            }
        }

        cout << decide(currentState).second << endl;
    }
}
