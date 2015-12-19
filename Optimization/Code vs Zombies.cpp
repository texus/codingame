#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Human
{
    Human(int id_, int x_, int y_) : id(id_), x(x_), y(y_) {}

    int id;
    int x;
    int y;
};

struct Zombie
{
    Zombie(int id_, int x_, int y_, int nextX_, int nextY_) : id(id_), x(x_), y(y_), nextX(nextX_), nextY(nextY_) {}

    int id;
    int x;
    int y;
    int nextX;
    int nextY;
};

int dist(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

int main()
{
    // game loop
    while (1) {
        vector<Human> humans;
        vector<Zombie> zombies;

        int playerX;
        int playerY;
        cin >> playerX >> playerY; cin.ignore();
        int humanCount;
        cin >> humanCount; cin.ignore();
        for (int i = 0; i < humanCount; i++) {
            int humanId;
            int humanX;
            int humanY;
            cin >> humanId >> humanX >> humanY; cin.ignore();
            humans.emplace_back(humanId, humanX, humanY);
        }
        int zombieCount;
        cin >> zombieCount; cin.ignore();
        for (int i = 0; i < zombieCount; i++) {
            int zombieId;
            int zombieX;
            int zombieY;
            int zombieXNext;
            int zombieYNext;
            cin >> zombieId >> zombieX >> zombieY >> zombieXNext >> zombieYNext; cin.ignore();
            zombies.emplace_back(zombieId, zombieX, zombieY, zombieXNext, zombieYNext);
        }

        // Find the human in greatest danger
        pair<int,int> target;
        int minDist = numeric_limits<int>::max();
        for (auto& human : humans)
        {
            Zombie* closingZombie;
            int closestZombieDist = numeric_limits<int>::max();
            for (auto& zombie : zombies)
            {
                int zombieDist = dist(human.x, human.y, zombie.x, zombie.y);
                if (closestZombieDist > zombieDist)
                {
                    closestZombieDist = zombieDist;
                    closingZombie = &zombie;
                }
            }

            if (closestZombieDist < minDist)
            {
                int distance = dist(playerX, playerY, human.x, human.y);
                if (closestZombieDist / 400.0 >= (max(distance - 2000, 0)) / 1000.0)
                {
                    target = {closingZombie->x, closingZombie->y};
                    minDist = closestZombieDist;
                }
            }
        }

        // Check if player is the closest to ALL zombies
        bool playerClosestToAllZombies = true;
        for (auto& zombie : zombies)
        {
            for (auto& human : humans)
            {
                if (dist(human.x, human.y, zombie.x, zombie.y) < dist(playerX, playerY, zombie.x, zombie.y))
                {
                    playerClosestToAllZombies = false;
                    break;
                }
            }

            if (!playerClosestToAllZombies)
                break;
        }

        // When we are closest to all zombies, move to their center
        if (playerClosestToAllZombies)
        {
            double centerX = 0;
            double centerY = 0;
            for (auto& zombie : zombies)
            {
                centerX += zombie.x;
                centerY += zombie.y;
            }
            centerX /= zombies.size();
            centerY /= zombies.size();

            target = {centerX, centerY};
        }

        cout << target.first << " " << target.second << endl;
    }
}
