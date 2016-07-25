// Rank: 278/1984

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Position
{
    int x;
    int y;
};

struct Buster
{
    int id;
    Position pos;
    int state;
    int ghostId;
};

struct Ghost
{
    int id;
    Position pos;
    int stamina;
    int busters;
};


int MAP_WIDTH = 16000;
int MAP_HEIGHT = 9000;
int CELL_WIDTH = 1000;
int CELL_HEIGHT = 1000;
std::vector<std::vector<bool>> grid(MAP_HEIGHT / CELL_HEIGHT, std::vector<bool>(MAP_WIDTH / CELL_WIDTH, false));

Position basePos;
vector<Buster> busters;
vector<Buster> enemies;
vector<Ghost> ghosts;
int iterations = 0;
bool campersDetected = false;
vector<int> bustersStunTimeout;
vector<pair<int, Position>> targetPositions;


bool operator==(Position left, Position right)
{
    return left.x == right.x && left.y == right.y;
}

bool operator!=(Position left, Position right)
{
    return !(left == right);
}

float dist(Position begin, Position end)
{
    return std::sqrt(std::pow(begin.x - end.x, 2) + std::pow(begin.y - end.y, 2));
}

void move(int i, Position pos)
{
    float alpha = atan2(pos.y - busters[i].pos.y, pos.x - busters[i].pos.x);
    float x = 800 * cos(alpha);
    float y = 800 * sin(alpha);
    Position nextTurnPos = {busters[i].pos.x - x, busters[i].pos.y - y};
    
    for (int y = 0; y < 9000 / CELL_HEIGHT; ++y) {
        for (int x = 0; x < 16000 / CELL_WIDTH; ++x) {
            if (!grid[y][x]) {
                if (dist(nextTurnPos, {(x+0.5f)*CELL_WIDTH, (y+0.5f)*CELL_HEIGHT}) < 1000) {
                    cerr << "(" << x << "," << y << ") explored" << endl;
                    grid[y][x] = true;
                }
            }
        }
    }
    
    cout << "MOVE " << pos.x << " " << pos.y << endl;
}

void carry(int i, vector<int>& stunned, Position busterPos, Position basePos)
{
    // If there is an enemy nearby when carrying a ghost then immediately try to stun it
    if (bustersStunTimeout[i] == 0) {
        if (dist(busterPos, basePos) <= 1600) {
            int targetEnemy = -1;
            for (int j = 0; j < enemies.size(); ++j) {
                if (enemies[j].state != 2) {
                    if (dist(busters[i].pos, enemies[j].pos) <= 1760)
                        targetEnemy = j;
                }
            }
            
            if (targetEnemy != -1) {
                cout << "STUN " << enemies[targetEnemy].id << endl;
                stunned.push_back(targetEnemy);
                bustersStunTimeout[i] = 20;
                return;
            }
        }
        else if (dist(busterPos, basePos) < 9000) {
            int closestEnemy = -1;
            int closestEnemyDist = 1600;
            for (int j = 0; j < enemies.size(); ++j) {
                if (enemies[j].state != 2) { // Don't stun an already stunned enemy
                    int enemyDist = dist(busters[i].pos, enemies[j].pos);
                    if (enemyDist <= closestEnemyDist) {
                        closestEnemy = j;
                        closestEnemyDist = enemyDist;
                    }
                }
            }

            if (closestEnemy != -1) {
                cout << "STUN " << enemies[closestEnemy].id << endl;
                stunned.push_back(closestEnemy);
                bustersStunTimeout[i] = 20;
                return;
            }
        }
    }

    if (!campersDetected) {
        if (dist(busterPos, basePos) <= 1600) {
            cout << "RELEASE" << endl;
        }
        else { // Return to base when too far away
            if (basePos.x == 0)
                move(i, {1390,782});
            else
                move(i, {MAP_WIDTH-1390, MAP_HEIGHT-782});
        }
    }
    else { // Hide away in a corner with the ghost
        if (dist(busters[i].pos, {1900,9000-1100}) < dist(busters[i].pos, {16000-1900,1100})) {
            move(i, {1900,9000});
        }
        else {
            move(i, {16000,1100});
        }
    }
}

int main()
{
    // Bases should not be explored
    for (int y = 0; y < 4000 / CELL_HEIGHT; ++y) {
        for (int x = 0; x < 4000 / CELL_WIDTH; ++x) {
            grid[y][x] = true;
            grid[grid.size()-1-y][grid.back().size()-1-x] = true;
        }
    }
    
    // Sides are automatically explored when at the row one away from them
    for (int y = 0; y < 9000 / CELL_HEIGHT; ++y) {
        grid[y][0] = true;
        grid[y][9000/CELL_HEIGHT-1] = true;
    }
    for (int x = 0; x < 16000 / CELL_WIDTH; ++x) {
        grid[0][x] = true;
        grid[9000/CELL_HEIGHT-1][x] = true;
    }
    
    int bustersPerPlayer; // the amount of busters you control
    cin >> bustersPerPlayer; cin.ignore();
    int ghostCount; // the amount of ghosts on the map
    cin >> ghostCount; cin.ignore();
    int myTeamId; // if this is 0, your base is on the top left of the map, if it is one, on the bottom right
    cin >> myTeamId; cin.ignore();

    if (myTeamId == 0)
        basePos = {0, 0};
    else
        basePos = {MAP_WIDTH, MAP_HEIGHT};

    bustersStunTimeout.resize(bustersPerPlayer, 0);

    // game loop
    bool cornersSearchedAgain = false;
    while (1) {
        iterations++;
        busters.clear();
        enemies.clear();
        ghosts.clear();

        if (iterations == 175)
            campersDetected = true;
        
        int entities; // the number of busters and ghosts visible to you
        cin >> entities; cin.ignore();
        for (int i = 0; i < entities; i++) {
            int entityId; // buster id or ghost id
            int x;
            int y; // position of this buster / ghost
            int entityType; // the team id if it is a buster, -1 if it is a ghost.
            int state; // For busters: 0=idle, 1=carrying a ghost.
            int value; // For busters: Ghost id being carried. For ghosts: number of busters attempting to trap this ghost.
            cin >> entityId >> x >> y >> entityType >> state >> value; cin.ignore();
        
            if (entityType == myTeamId) {
                busters.push_back({entityId, {x, y}, state, value});
            }
            else if (entityType == -1)
                ghosts.push_back({entityId, {x, y}, state, value});
            else {
                enemies.push_back({entityId, {x, y}, state, value});
            }
        }

        vector<int> stunned;
        for (int i = 0; i < bustersPerPlayer; i++) {            
            if (bustersStunTimeout[i] > 0) {
                bustersStunTimeout[i]--;
            }
            
            // Just give some instruction when stunned
            if (busters[i].state == 2) {
                if (dist(busters[i].pos, basePos) < 6000)
                    campersDetected = true;
                
                move(i, {0,0});
                continue;
            }
/*
            // Check if this buster is going somewhere specific with his ghost
            auto it = find_if(targetPositions.begin(), targetPositions.end(), [=](pair<int, Position> p){ return i == p.first; });
            if (it != targetPositions.end()) {
                // Move towards the location as long as we still have the ghost
                if (busters[i].state == 1) {
                    //if (busters[i].pos != it->second) {
                        move(i, it->second);
                    //}
                    continue;
                }
                else { // We released the ghost (we became stunned)
                    targetPositions.erase(it);
                }
            }
            */
            if (busters[i].state == 1) { // Check if carrying ghost
                carry(i, stunned, busters[i].pos, basePos);
            }
            else
            {
                // Try to stun if there are enemies nearby
                if (!enemies.empty()) {
                    int targetEnemy = -1;
                    
                    // Prioritize stunning an enemy that is carrying a ghost
                    for (int j = 0; j < enemies.size(); ++j) {
                        if (enemies[j].state == 1) {
                            if (dist(busters[i].pos, enemies[j].pos) <= 6000)
                                targetEnemy = j;
                        }
                    }

                    if (bustersStunTimeout[i] == 0 && targetEnemy == -1) {
                        // Try stunning an attacking enemy when the ghost's stamina is low
                        for (int j = 0; j < enemies.size(); ++j) {
                            if (enemies[j].state == 3) {
                                if (dist(busters[i].pos, enemies[j].pos) <= 1760+2*800) {
                                    targetEnemy = j;
                                    
                                    auto it = find_if(ghosts.begin(), ghosts.end(), [&](const Ghost& g){ return g.id == enemies[j].ghostId; });
                                    if (it != ghosts.end() && it->stamina / it->busters > 3) {
                                        targetEnemy = -1;
                                    }
                                }
                            }
                        }

                        if (targetEnemy == -1) {
                            // Just attack the closest enemy when there are weak ghosts nearby
                            for (int j = 0; j < ghosts.size(); ++j) {
                                if (ghosts[j].stamina < 4) {
                                    if (dist(busters[i].pos, ghosts[j].pos) < 2200) {
                                        int closestEnemyDist = numeric_limits<int>::max();
                                        for (int k = 0; k < enemies.size(); ++k) {
                                            if (enemies[k].state != 2) { // Don't stun an already stunned enemy
                                                int enemyDist = dist(busters[i].pos, enemies[k].pos);
                                                if (enemyDist <= closestEnemyDist && dist(enemies[k].pos, ghosts[j].pos) < 2200) {
                                                    targetEnemy = k;
                                                    closestEnemyDist = enemyDist;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    
                    if ((targetEnemy != -1) && (std::find(stunned.begin(), stunned.end(), targetEnemy) == stunned.end())) {
                        if (bustersStunTimeout[i] == 0) {
                            if (dist(busters[i].pos, enemies[targetEnemy].pos) < 1760) {
                                cout << "STUN " << enemies[targetEnemy].id << endl;
                                stunned.push_back(targetEnemy);
                                bustersStunTimeout[i] = 20;
                                continue;
                            }
                            //else {
                            //    move(i, enemies[targetEnemy].pos);
                            //}
                            //continue;
                        }
                        /*else*/ { // We can't stun him yet, but maybe we can take him down before he reaches the exit?
                            Position goalPos;
                            if (basePos.x == 0)
                                goalPos =  {16000-1390,9000-782};
                            else
                                goalPos =  {1390,782};

                            if (dist(enemies[targetEnemy].pos, goalPos) / 800 > bustersStunTimeout[i]) {
                                if (dist(busters[i].pos, enemies[targetEnemy].pos) < 1760) {
                                    move(i, enemies[targetEnemy].pos);
                                    continue;
                                }
                                else { // We are not close to him, try to intercept him
                                    if (dist(enemies[targetEnemy].pos, goalPos) / 800 <= dist(busters[i].pos, goalPos) / 800) {
                                        move(i, goalPos);
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                }

                // Find the closest ghost (if not too far away)
                int closestGhost = -1;
                int closestGhostDist = numeric_limits<int>::max();
                int closestGhostStamina = numeric_limits<int>::max();
                int closestGhostScore = numeric_limits<int>::max();
                //if (dist(busters[i].pos, basePos) < 10000)
                //    closestGhostDist = numeric_limits<int>::max(); // Stay together in the beginning
                
                for (int j = 0; j < ghosts.size(); ++j) {
                    // Ignore strong ghosts
                    if (ghosts[j].stamina <= 15 + iterations/5) {
                        int ghostDist = dist(busters[i].pos, ghosts[j].pos);
                        int ghostScore = ghostDist + 200 * ghosts[j].stamina;
                        if (ghostDist < 8000 && ghostScore < closestGhostScore) {
                            closestGhost = j;
                            closestGhostDist = ghostDist;
                            closestGhostStamina = ghosts[j].stamina;
                            closestGhostScore = ghostScore;
                        }
                    }
                }

                // Nobody can see a ghost
                if (closestGhost == -1) {
                    
                    // Check if we need to play the stealer role
                    int closestBuster = -1;
                    int closestBusterDistance = 0;
                    int secondClosestBuster = -1;
                    int secondClosestBusterDistance = 0;
                    for (int j = 0; j < bustersPerPlayer; ++j) {
                        if (bustersStunTimeout[i] <= 4) {
                            if (dist(busters[i].pos, basePos) > closestBusterDistance) {
                                closestBusterDistance = dist(busters[i].pos, basePos);
                                closestBuster = j;
                            }
                            else if (dist(busters[i].pos, basePos) > secondClosestBusterDistance) {
                                secondClosestBusterDistance = dist(busters[i].pos, basePos);
                                secondClosestBuster = j;
                            }
                        }
                    }
                    
                    bool stealer = false;
                    if (iterations >= 40) {
                        if ((i == closestBuster) || (i == secondClosestBuster/* && bustersPerPlayer > 3*/)) {
                            stealer = true;
                        }
                    }
                    
                    if (!stealer) {
                        // Move to the closest unexplored cell
                        Position closestUnexploredCell = {0,0};
                        float closestUnexploredCellDist = numeric_limits<int>::max();
                        for (int y = 0; y < grid.size(); ++y) {
                            for (int x = 0; x < grid.back().size(); ++x) {
                                if (!grid[y][x]) {
                                    int cellDist = dist(busters[i].pos, {(x+0.5f) * CELL_WIDTH, (y+0.5f) * CELL_HEIGHT});
                                    if (cellDist < closestUnexploredCellDist) {
                                        closestUnexploredCell = {x, y};
                                        closestUnexploredCellDist = cellDist;
                                    }
                                }
                            }
                        }
                    
                        if (closestUnexploredCell.x != 0 || closestUnexploredCell.y != 0) {
                            move(i, {(closestUnexploredCell.x+0.5)*CELL_WIDTH, (closestUnexploredCell.y+0.5)*CELL_HEIGHT});
                        }
                        else {
                            stealer = true;
                            
                            // Move towards the closest corner (in the last 40 moves)
                            if (iterations >= 160 && !cornersSearchedAgain) {
                                grid[0][16000/CELL_WIDTH-1] = false;
                                grid[9000/CELL_HEIGHT-1][0] = false;
                                cornersSearchedAgain = true;
                            }
                            
                            /*
                            if (iterations >= 160) {
                                if (dist(busters[i].pos, {1900,9000-1100}) < dist(busters[i].pos, {16000-1900,1100})) {
                                    move(i, {1900,9000-1100});
                                }
                                else {
                                    move(i, {16000-1900,1100});
                                }
                            }
                            */
                        }
                    }

                    if (stealer) {
                        // Go attack the enemy
                        if (myTeamId == 0)
                            move(i, {16000-1700, 9000-1700});
                        else
                            move(i, {1700, 1700});
                    }
                }
                else {
                    if (closestGhostDist < 900) { // Walk away if the ghost is too close
                        float diff = 1760-400-closestGhostDist;
                        float alpha = atan2(busters[i].pos.y, busters[i].pos.x);
                        float x = diff * cos(alpha);
                        float y = diff * sin(alpha);
                        move(i, {busters[i].pos.x - x, busters[i].pos.y - y});
                    }
                    else if (closestGhostDist >= 1760) { // Move towards the ghost if it is too far away
                        move(i, ghosts[closestGhost].pos);
                    }
                    else { // Bust the ghost when in range
                    
                        // Check if enemy busters are busting the ghost when its stamina is low
                        if (bustersStunTimeout[i] == 0 && ghosts[closestGhost].busters > 0 && ghosts[closestGhost].stamina / ghosts[closestGhost].busters <= 3) {
                            int busterCount = count_if(busters.begin(), busters.end(), [&](Buster b){ return b.state == 3 && b.ghostId == ghosts[closestGhost].id; });
                            if (ghosts[closestGhost].busters >= 2* busterCount) {
                                move(i, ghosts[closestGhost].pos);
                                continue;
                            }
                        }
                    
                        cout << "BUST " << ghosts[closestGhost].id << endl;
                    }
                }
            }
        }
    }
}
