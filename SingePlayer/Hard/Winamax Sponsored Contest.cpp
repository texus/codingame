#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Pos
{
    unsigned int x;
    unsigned int y;

    bool operator==(const Pos& other) const
    {
        return (x == other.x) && (y == other.y);
    }
};

struct Ball
{
    Pos pos;
    unsigned int count;
};

using BallTrajectory = std::vector<Pos>;
using BallTrajectoryOptions = std::vector<BallTrajectory>;

std::vector<std::vector<char>> inputGrid;
std::vector<std::vector<char>> outputGrid;

// Checks if the ball flies over a hole, which is not allowed
bool ballCrossesHole(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    if (y1 == y2)
    {
        for (unsigned int x = x1 + 1; x < x2; ++x)
        {
            if (inputGrid[x][y1] == 'H')
                return true;
        }
    }
    else // if (x1 == x2)
    {
        for (unsigned int y = y1 + 1; y < y2; ++y)
        {
            if (inputGrid[x1][y] == 'H')
                return true;
        }
    }

    return false;
}

// For a given ball, this function calculates all possible next positions recursively.
// Each trajectory contains a list of positions where the ball stops before ending in
// a hole. The trajectory is stored backwards (hole location is first in list) so that
// the recursive code can push positions at the back of the vector instead of the front.
BallTrajectoryOptions calculatePossibleBallTrajectories(Ball ball)
{
    // There are up to 4 positions where the ball could land after hitting it
    std::vector<Ball> ballOptions;
    if ((ball.pos.x >= ball.count)
     && (inputGrid[ball.pos.x - ball.count][ball.pos.y] != 'X')
     && !ballCrossesHole(ball.pos.x - ball.count, ball.pos.y, ball.pos.x, ball.pos.y))
    {
        ballOptions.push_back({{ball.pos.x - ball.count, ball.pos.y}, ball.count-1});
    }
    if ((ball.pos.x + ball.count < inputGrid.size())
     && (inputGrid[ball.pos.x + ball.count][ball.pos.y] != 'X')
     && !ballCrossesHole(ball.pos.x, ball.pos.y, ball.pos.x + ball.count, ball.pos.y))
    {
        ballOptions.push_back({{ball.pos.x + ball.count, ball.pos.y}, ball.count-1});
    }
    if ((ball.pos.y >= ball.count)
     && (inputGrid[ball.pos.x][ball.pos.y - ball.count] != 'X')
     && !ballCrossesHole(ball.pos.x, ball.pos.y - ball.count, ball.pos.x, ball.pos.y))
    {
        ballOptions.push_back({{ball.pos.x, ball.pos.y - ball.count}, ball.count-1});
    }
    if ((ball.pos.y + ball.count < inputGrid[0].size())
     && (inputGrid[ball.pos.x][ball.pos.y + ball.count] != 'X')
     && !ballCrossesHole(ball.pos.x, ball.pos.y, ball.pos.x, ball.pos.y + ball.count))
    {
        ballOptions.push_back({{ball.pos.x, ball.pos.y + ball.count}, ball.count-1});
    }

    // For each of those 4 positions, recursively calculate the next positions
    BallTrajectoryOptions steps;
    for (Ball& nextBall : ballOptions)
    {
        if (inputGrid[nextBall.pos.x][nextBall.pos.y] == 'H')
            steps.push_back(BallTrajectory(1, nextBall.pos));
        else if (nextBall.count > 0)
        {
            auto nextSteps = calculatePossibleBallTrajectories(nextBall);
            for (auto& step : nextSteps)
                steps.push_back(std::move(step));
        }
    }

    // Add the current ball position to the trajectories
    for (auto& step : steps)
        step.push_back(ball.pos);

    return steps;
}

// Changes part of a row or column in the output grid.
// Unless the contents of the line is being removed, this function will first
// check that all cells on the line are still empty and return false otherwise.
bool changeLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, char value)
{
    bool erasing = (value == '.');

    if (y1 == y2)
    {
        for (unsigned int x = x1; x <= x2; ++x)
        {
            if (!erasing && (outputGrid[x][y1] != '.'))
                return false;
        }

        for (unsigned int x = x1; x <= x2; ++x)
            outputGrid[x][y1] = value;
    }
    else // if (x1 == x2)
    {
        for (unsigned int y = y1; y <= y2; ++y)
        {
            if (!erasing && (outputGrid[x1][y] != '.'))
                return false;
        }

        for (unsigned int y = y1; y <= y2; ++y)
            outputGrid[x1][y] = value;
    }

    return true;
}

// Try all combinations recursively and backtrack when stuck
bool findSolutionTrajectories(const std::vector<BallTrajectoryOptions>& combinations, std::vector<Pos>& usedHoles, unsigned int ballIndex)
{
    for (unsigned int index = 0; index < combinations[ballIndex].size(); ++index)
    {
        const auto& trajectory = combinations[ballIndex][index];

        // If the trajectory ends in a hole that is already filled by another ball then we can
        // skip it entirely without having to do further calculations
        if (std::find(usedHoles.begin(), usedHoles.end(), trajectory.back()) != usedHoles.end())
            continue;

        bool valid = true;
        unsigned int trajectoryIndex;
        for (trajectoryIndex = 1; trajectoryIndex < trajectory.size(); ++trajectoryIndex)
        {
            const Pos& currentPos = trajectory[trajectoryIndex - 1];
            const Pos& nextPos = trajectory[trajectoryIndex];
            if (currentPos.x < nextPos.x)
                valid = changeLine(currentPos.x, currentPos.y, nextPos.x - 1, nextPos.y, '>');
            else if (currentPos.x > nextPos.x)
                valid = changeLine(nextPos.x + 1, nextPos.y, currentPos.x, currentPos.y, '<');
            else if (currentPos.y < nextPos.y)
                valid = changeLine(currentPos.x, currentPos.y, nextPos.x, nextPos.y - 1, 'v');
            else if (currentPos.y > nextPos.y)
                valid = changeLine(nextPos.x, nextPos.y + 1, currentPos.x, currentPos.y, '^');

            if (!valid)
                break;
        }

        // If there is no overlap with previous balls then proceed with testing the other balls
        if (valid && (ballIndex + 1 < combinations.size()))
        {
            usedHoles.push_back(trajectory.back());
            if (!findSolutionTrajectories(combinations, usedHoles, ballIndex + 1))
            {
                // If there is valid trajectory for the other balls then we still need to change
                // the trajectory for this ball.
                usedHoles.pop_back();
                valid = false;
            }
        }

        if (valid)
        {
            // We found the solution
            return true;
        }
        else // The trajectory overlapped, so undo the markings on the grid
        {
            for (trajectoryIndex = trajectoryIndex - 1; trajectoryIndex > 0; --trajectoryIndex)
            {
                const Pos& prevPos = trajectory[trajectoryIndex - 1];
                const Pos& currentPos = trajectory[trajectoryIndex];
                if (prevPos.x < currentPos.x)
                    changeLine(prevPos.x, prevPos.y, currentPos.x - 1, currentPos.y, '.');
                else if (prevPos.x > currentPos.x)
                    changeLine(currentPos.x + 1, currentPos.y, prevPos.x, prevPos.y, '.');
                else if (prevPos.y < currentPos.y)
                    changeLine(prevPos.x, prevPos.y, currentPos.x, currentPos.y - 1, '.');
                else if (prevPos.y > currentPos.y)
                    changeLine(currentPos.x, currentPos.y + 1, prevPos.x, prevPos.y, '.');
            }
        }
    }

    // None of the trajectories is valid for this ball, another ball must change his trajectory
    return false;
}

int main()
{
    std::vector<Ball> balls;

    unsigned int width;
    unsigned int height;
    cin >> width >> height; cin.ignore();
    inputGrid.resize(width, std::vector<char>(height));
    for (unsigned int y = 0; y < height; y++) {
        string row;
        cin >> row; cin.ignore();
        for (unsigned int x = 0; x < width; ++x)
        {
            inputGrid[x][y] = row[x];
            if ((row[x] >= '1') && (row[x] <= '9'))
                balls.push_back({{x, y}, row[x]-'0'});
        }
    }

    // First we calculate all valid trajectories for all balls while ignoring
    // the existence of the other balls.
    std::vector<BallTrajectoryOptions> allBallTrajectories;
    for (const auto& ball : balls)
        allBallTrajectories.push_back(calculatePossibleBallTrajectories(ball));

    // The trajectories were created in reverse order, so reverse them here to have
    // the current step in front and the final step in the back.
    for (auto& trajectoryOptions : allBallTrajectories)
    {
        for (auto& trajectory : trajectoryOptions)
            std::reverse(trajectory.begin(), trajectory.end());
    }

    // For the found trajectories, we now have to find the one for each ball which 
    // doesn't overlap with any other ball trajectory
    outputGrid = std::vector<std::vector<char>>(inputGrid.size(), std::vector<char>(inputGrid[0].size(), '.'));
    std::vector<Pos> usedHoles;
    findSolutionTrajectories(allBallTrajectories, usedHoles, 0);

    // Finally print the result
    for (unsigned int y = 0; y < height; y++)
    {
        std::string row;
        for (unsigned int x = 0; x < width; ++x)
            row.push_back(outputGrid[x][y]);

        std::cout << row << std::endl;
    }
}
