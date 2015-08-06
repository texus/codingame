#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <memory>
#include <queue>
#include <set>

using namespace std;

int W; // number of columns.
int H; // number of rows.
int EX; // the coordinate along the X axis of the exit.

struct State
{
    int x;
    int y;
    string entry;
    int roomType;
    vector<vector<int>> rooms;
};

string findExit(int room, const string& entry)
{
    switch (abs(room))
    {
        case 0:
            return "";
        case 1:
            return "TOP";
        case 2:
            if (entry == "LEFT")
                return "LEFT";
            else if (entry == "RIGHT")
                return "RIGHT";
            else
                return "";
        case 3:
            if (entry == "TOP")
                return "TOP";
            else
                return "";
        case 4:
            if (entry == "TOP")
                return "RIGHT";
            else if (entry == "RIGHT")
                return "TOP";
            else
                return "";
        case 5:
            if (entry == "TOP")
                return "LEFT";
            else if (entry == "LEFT")
                return "TOP";
            else
                return "";
        case 6:
            if (entry == "LEFT")
                return "LEFT";
            else if (entry == "RIGHT")
                return "RIGHT";
            else
                return "";
        case 7:
            if (entry == "TOP")
                return "TOP";
            else if (entry == "RIGHT")
                return "TOP";
            else
                return "";
        case 8:
            if (entry == "LEFT")
                return "TOP";
            else if (entry == "RIGHT")
                return "TOP";
            else
                return "";
        case 9:
            if (entry == "TOP")
                return "TOP";
            else if (entry == "LEFT")
                return "TOP";
            else
                return "";
        case 10:
            if (entry == "TOP")
                return "RIGHT";
            else
                return "";
        case 11:
            if (entry == "TOP")
                return "LEFT";
            else
                return "";
        case 12:
            if (entry == "RIGHT")
                return "TOP";
            else
                return "";
        case 13:
            if (entry == "LEFT")
                return "TOP";
            else
                return "";
    }
}

int rotateClockwise(int roomType)
{
    switch (roomType)
    {
        case 2:
            return 3;
        case 3:
            return 2;
        case 4:
            return 5;
        case 5:
            return 4;
        case 6:
            return 7;
        case 7:
            return 8;
        case 8:
            return 9;
        case 9:
            return 6;
        case 10:
            return 11;
        case 11:
            return 12;
        case 12:
            return 13;
        case 13:
            return 10;
    }
}

int rotateCounterClockwise(int roomType)
{
    switch (roomType)
    {
        case 2:
            return 3;
        case 3:
            return 2;
        case 4:
            return 5;
        case 5:
            return 4;
        case 6:
            return 9;
        case 7:
            return 6;
        case 8:
            return 7;
        case 9:
            return 8;
        case 10:
            return 13;
        case 11:
            return 10;
        case 12:
            return 11;
        case 13:
            return 12;
    }
}

vector<State> findPath(State& state)
{
    struct Node {
        int x;
        int y;
        int roomType;
        string entry;
        set<string> visited;
        Node* parent = nullptr;
    };
    
    vector<vector<shared_ptr<Node>>> nodes;
    for (unsigned int y = 0; y < state.rooms.size(); ++y) {
        nodes.push_back({});
        for (unsigned int x = 0; x < state.rooms[y].size(); ++x) {
            nodes.back().emplace_back(make_shared<Node>());
            nodes.back().back()->roomType = state.rooms[y][x];
            nodes.back().back()->x = x;
            nodes.back().back()->y = y;
        }
    }
    
    queue<shared_ptr<Node>> q;
    
    nodes[state.y][state.x]->visited.insert(state.entry);
    nodes[state.y][state.x]->entry = state.entry;
    
    string entry = findExit(nodes[state.y][state.x]->roomType, nodes[state.y][state.x]->entry);

    if (entry == "LEFT") {
        nodes[state.y][state.x+1]->visited.insert(entry);
        nodes[state.y][state.x+1]->entry = entry;
        q.push(nodes[state.y][state.x+1]);
    }
    else if (entry == "RIGHT") {
        nodes[state.y][state.x-1]->visited.insert(entry);
        nodes[state.y][state.x-1]->entry = entry;
        q.push(nodes[state.y][state.x-1]);
    }
    else if (entry == "TOP") {
        nodes[state.y+1][state.x]->visited.insert(entry);
        nodes[state.y+1][state.x]->entry = entry;
        q.push(nodes[state.y+1][state.x]);
    }
    else {
        throw runtime_error("INVALID ENTRY");
    }
    
    while (!q.empty()) {
        auto node = q.front();
        q.pop();

        if (node->y == H-1 && node->x == EX) {
            std::vector<State> path;
            Node* nextNode = node.get();
            do {
                State nextState;
                nextState.x = nextNode->x;
                nextState.y = nextNode->y;
                nextState.entry = nextNode->entry;
                path.insert(path.begin(), nextState);
                nextNode = nextNode->parent;
            } while (nextNode != nullptr);

            return path;
        }

        entry = findExit(node->roomType, node->entry);
        if (entry == "LEFT") {
            if (node->x < W-1 && nodes[node->y][node->x+1]->visited.count(entry) == 0) {
                nodes[node->y][node->x+1]->visited.insert(entry);
                nodes[node->y][node->x+1]->parent = node.get();
                nodes[node->y][node->x+1]->entry = entry;
                q.push(nodes[node->y][node->x+1]);
            }
        }
        else if (entry == "RIGHT") {
            if (node->x > 0 && nodes[node->y][node->x-1]->visited.count(entry) == 0) {
                nodes[node->y][node->x-1]->visited.insert(entry);
                nodes[node->y][node->x-1]->parent = node.get();
                nodes[node->y][node->x-1]->entry = entry;
                q.push(nodes[node->y][node->x-1]);
            }
        }
        else if (entry == "TOP") {
            if (node->y < H-1 && nodes[node->y+1][node->x]->visited.count(entry) == 0) {
                nodes[node->y+1][node->x]->visited.insert(entry);
                nodes[node->y+1][node->x]->parent = node.get();
                nodes[node->y+1][node->x]->entry = entry;
                q.push(nodes[node->y+1][node->x]);
            }
        }
        
        if (node->roomType >= 2) {
            entry = findExit(rotateClockwise(node->roomType), node->entry);
            if (entry == "LEFT") {
                if (node->x < W-1 && nodes[node->y][node->x+1]->visited.count(entry) == 0) {
                    nodes[node->y][node->x+1]->visited.insert(entry);
                    nodes[node->y][node->x+1]->entry = entry;
                    nodes[node->y][node->x+1]->parent = node.get();
                    q.push(nodes[node->y][node->x+1]);
                }
            }
            else if (entry == "RIGHT") {
                if (node->x > 0 && nodes[node->y][node->x-1]->visited.count(entry) == 0) {
                    nodes[node->y][node->x-1]->visited.insert(entry);
                    nodes[node->y][node->x-1]->entry = entry;
                    nodes[node->y][node->x-1]->parent = node.get();
                    q.push(nodes[node->y][node->x-1]);
                }
            }
            else if (entry == "TOP") {
                if (node->y < H-1 && nodes[node->y+1][node->x]->visited.count(entry) == 0) {
                    nodes[node->y+1][node->x]->visited.insert(entry);
                    nodes[node->y+1][node->x]->entry = entry;
                    nodes[node->y+1][node->x]->parent = node.get();
                    q.push(nodes[node->y+1][node->x]);
                }
            }
            
            if (node->roomType >= 6) {
                entry = findExit(rotateClockwise(rotateClockwise(node->roomType)), node->entry);
                if (entry == "LEFT") {
                    if (node->x < W-1 && nodes[node->y][node->x+1]->visited.count(entry) == 0) {
                        nodes[node->y][node->x+1]->visited.insert(entry);
                        nodes[node->y][node->x+1]->entry = entry;
                        nodes[node->y][node->x+1]->parent = node.get();
                        q.push(nodes[node->y][node->x+1]);
                    }
                }
                else if (entry == "RIGHT") {
                    if (node->x > 0 && nodes[node->y][node->x-1]->visited.count(entry) == 0) {
                        nodes[node->y][node->x-1]->visited.insert(entry);
                        nodes[node->y][node->x-1]->entry = entry;
                        nodes[node->y][node->x-1]->parent = node.get();
                        q.push(nodes[node->y][node->x-1]);
                    }
                }
                else if (entry == "TOP") {
                    if (node->y < H-1 && nodes[node->y+1][node->x]->visited.count(entry) == 0) {
                        nodes[node->y+1][node->x]->visited.insert(entry);
                        nodes[node->y+1][node->x]->entry = entry;
                        nodes[node->y+1][node->x]->parent = node.get();
                        q.push(nodes[node->y+1][node->x]);
                    }
                }
                
                entry = findExit(rotateCounterClockwise(node->roomType), node->entry);
                if (entry == "LEFT") {
                    if (node->x < W-1 && nodes[node->y][node->x+1]->visited.count(entry) == 0) {
                        nodes[node->y][node->x+1]->visited.insert(entry);
                        nodes[node->y][node->x+1]->entry = entry;
                        nodes[node->y][node->x+1]->parent = node.get();
                        q.push(nodes[node->y][node->x+1]);
                    }
                }
                else if (entry == "RIGHT") {
                    if (node->x > 0 && nodes[node->y][node->x-1]->visited.count(entry) == 0) {
                        nodes[node->y][node->x-1]->visited.insert(entry);
                        nodes[node->y][node->x-1]->entry = entry;
                        nodes[node->y][node->x-1]->parent = node.get();
                        q.push(nodes[node->y][node->x-1]);
                    }
                }
                else if (entry == "TOP") {
                    if (node->y < H-1 && nodes[node->y+1][node->x]->visited.count(entry) == 0) {
                        nodes[node->y+1][node->x]->visited.insert(entry);
                        nodes[node->y+1][node->x]->entry = entry;
                        nodes[node->y+1][node->x]->parent = node.get();
                        q.push(nodes[node->y+1][node->x]);
                    }
                }
            }
        }
    }
    
    throw runtime_error("NO PATH FOUND");
}

int main()
{
    unsigned int turn = 0;
    vector<vector<int>> rooms;
    cin >> W >> H; cin.ignore();
    for (int i = 0; i < H; i++) {
        rooms.push_back({});
        string LINE; // each line represents a line in the grid and contains W integers T. The absolute value of T specifies the type of the room. If T is negative, the room cannot be rotated.
        getline(cin, LINE);
        
        istringstream iss(LINE);
        vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
        for (auto& num : tokens)
            rooms.back().push_back(stoi(num));
    }
    cin >> EX; cin.ignore();

    // game loop
    while (1) {
        
        struct Rock {
            int x;
            int y;
            string entry;
        };
        vector<Rock> rocks;
        
        int XI;
        int YI;
        string POSI;
        cin >> XI >> YI >> POSI; cin.ignore();
        int R; // the number of rocks currently in the grid.
        cin >> R; cin.ignore();
        for (int i = 0; i < R; i++) {
            int XR;
            int YR;
            string POSR;
            cin >> XR >> YR >> POSR; cin.ignore();
            rocks.push_back({XR, YR, POSR});
        }
        
        vector<Rock> rocksCopy = rocks;

        State state;
        state.x = XI;
        state.y = YI;
        state.entry = POSI;
        state.rooms = rooms;

        static vector<State> path = findPath(state);
        
        bool clockWise;
        int rotationX = -1;
        int rotationY = -1;
        unsigned int distanceToRotation = 1;
        
        for (unsigned int i = turn; i < path.size()-1; ++i) {
            string expectedEntry = findExit(rooms[path[i].y][path[i].x], path[i].entry);
            if (!(((expectedEntry == "RIGHT") && (path[i+1].x+1 == path[i].x)) || ((expectedEntry == "LEFT") && (path[i+1].x == path[i].x+1)) || ((expectedEntry == "TOP") && (path[i+1].y == path[i].y+1)))) {
                expectedEntry = findExit(rotateClockwise(rooms[path[i].y][path[i].x]), path[i].entry);
                if (((expectedEntry == "RIGHT") && (path[i+1].x+1 == path[i].x)) || ((expectedEntry == "LEFT") && (path[i+1].x == path[i].x+1)) || ((expectedEntry == "TOP") && (path[i+1].y == path[i].y+1)))
                    clockWise = true;
                else
                    clockWise = false;
                
                rotationX = path[i].x;
                rotationY = path[i].y;
                break;
            }
            
            distanceToRotation++;
        }

        if (distanceToRotation > 1) {
            for (unsigned int i = turn; i < path.size(); ++i) {
                bool collision = false;
                int newX = path[i].x;
                int newY = path[i].y;
                for (unsigned int j = 0; j < rocks.size(); ++j) {
                    string entry = findExit(rooms[rocks[j].y][rocks[j].x], rocks[j].entry);
                    if (entry == "LEFT")
                        rocks[j].x += 1;
                    else if (entry == "RIGHT")
                        rocks[j].x -= 1;
                    else if (entry == "TOP")
                        rocks[j].y += 1;
                    
                    if (rocks[j].x == newX && rocks[j].y == newY)
                    {
                        rocks[j] = rocksCopy[j];
                        while (rocks[j].x != newX || rocks[j].y != newY) {
                            string entry = findExit(rooms[rocks[j].y][rocks[j].x], rocks[j].entry);
                            if (entry == "LEFT")
                                rocks[j].x += 1;
                            else if (entry == "RIGHT")
                                rocks[j].x -= 1;
                            else if (entry == "TOP")
                                rocks[j].y += 1;
                            
                            if (rocks[j].x == newX && rocks[j].y == newY)
                                break;
                            
                            if (rooms[rocks[j].y][rocks[j].x] >= 2) {
                                rotationX = rocks[j].x;
                                rotationY = rocks[j].y;
                                clockWise = true;
                                collision = true;
                                break;
                            }
                        }
                        
                        rocks[j] = rocksCopy[j];
    
                        if (collision)
                            break;
                    }
                }
                
                if (collision)
                    break;
            }
        }
        
        string decision = "WAIT";
        if (rotationX != -1 && rotationY != -1) {
            if (clockWise) {
                decision = to_string(rotationX) + " " + to_string(rotationY) + " RIGHT";
                rooms[rotationY][rotationX] = rotateClockwise(rooms[rotationY][rotationX]);
            }
            else {
                decision = to_string(rotationX) + " " + to_string(rotationY) + " LEFT";
                rooms[rotationY][rotationX] = rotateCounterClockwise(rooms[rotationY][rotationX]);
            }
        }

        turn++;
        cout << decision << endl; // One line containing on of three commands: 'X Y LEFT', 'X Y RIGHT' or 'WAIT'
    }
}
