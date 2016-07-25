// Rank: 89/2616

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const unsigned int ZONES = 30;
const unsigned int MIN_PATTERN_SIZE = 9;

string magicPhrase;

char rune[ZONES];
string output;
int currentZone = 0;

string detectedPattern;
int detectedPatternCount = 0;
unsigned int currentPatternPosition = 0;

// We don't have to look at empty stones behind other empty ones
int leftBorderUnsearched = 1;
int rightBorderUnsearched = ZONES - 1;

string repeat(const std::string& word, unsigned int times) {
    string result;
    result.reserve(times * word.length());
    for (unsigned int i = 0; i < times; ++i)
        result += word;

    return result ;
}

int bound(int zone)
{
    // Handle negative numbers
    if (zone < 0)
        zone += ZONES;

    return zone % ZONES;
}

int distance(int current, int goal)
{
    if ((current == ' ') || (goal == ' ')) {
        if (current == goal)
            return 0;
        else if ((current == ' ') && (goal <= 'M'))
            return goal - 'A' + 1;
        else if ((current == ' ') && (goal >= 'N'))
            return -('Z' - goal + 1);
        else if ((current <= 'M') && (goal <= ' '))
            return -(current - 'A' + 1);
        else if ((current >= 'N') && (goal >= ' '))
            return 'Z' - current + 1;
    }

    if (current > goal) {
        if (current - goal < 14)
            return -(current - goal);
        else
            return 'Z' - current + 1 + goal - 'A' + 1;
    }
    else if (current < goal) {
        if (goal - current < 14)
            return goal - current;
        else
            return 'A' - current - 1 - ('Z' - goal + 1);
    }
    else {
        return 0;
    }
}

int findPattern()
{
    detectedPattern = "";
    detectedPatternCount = 0;

    string pattern;
    int moveDirection = 0;

    // Try to find patterns
    for (unsigned int i = output.size() / MIN_PATTERN_SIZE; i > 0; --i) {
        pattern = output.substr(output.size() - i);

        bool invalid = false;
        int patternMoveDistance = 0;
        int patternMoveDirection = 0;
        for (unsigned int j = 0; j < pattern.size(); ++j) {
            if (pattern[j] == '<') {
                patternMoveDistance--;
                if (patternMoveDirection > 0 && patternMoveDistance < 0) {
                    invalid = true;
                    break;
                }
                else if (patternMoveDirection == 0)
                    patternMoveDirection = -1;
            }
            else if (pattern[j] == '>') {
                patternMoveDistance++;
                if (patternMoveDirection < 0 && patternMoveDistance > 0) {
                    invalid = true;
                    break;
                }
                else if (patternMoveDirection == 0)
                    patternMoveDirection = 1;
            }
        }

        if (rune[currentZone] == ' ')
            invalid = true;
        if (patternMoveDistance != 0)
            invalid = true;

        if (invalid)
            continue;

        // Count the occurence of the pattern
        unsigned int opCount = 1;
        for (unsigned int j = output.size() - i; j >= i; j -= i) {
            if (output.substr(j-i, i) == pattern)
                opCount++;
            else
                break;
        }

        if ((opCount > MIN_PATTERN_SIZE) && (detectedPatternCount == 0 || abs(opCount - 26) < abs(detectedPatternCount - 26))) {
            detectedPattern = pattern;
            detectedPatternCount = opCount;
            currentPatternPosition = 0;
            moveDirection = patternMoveDirection;
        }
    }

    return moveDirection;
}

void testPattern(char nextChar)
{
    if (output.size() <= MIN_PATTERN_SIZE)
        return;

    if (!detectedPattern.empty()) {
        // Check if we are still following the pattern
        if (detectedPattern[currentPatternPosition] == nextChar) {
            currentPatternPosition++;
            if (currentPatternPosition == detectedPattern.size()) {
                currentPatternPosition = 0;
                detectedPatternCount++;
            }
        }
        else { // The pattern sequence ends here, try to replace it with a loop
            // Try to find a larger pattern first
            string oldOutput = output;
            string oldPattern = detectedPattern;
            int oldPatternCount = detectedPatternCount;
            int oldPatternPosition = currentPatternPosition;
            output = output.substr(0, output.size() - currentPatternPosition);
            int dir = findPattern();
            output = oldOutput;
            currentPatternPosition = oldPatternPosition;
            if (detectedPattern.size() * detectedPatternCount < oldPattern.size() * oldPatternCount) {
                detectedPattern = oldPattern;
                detectedPatternCount = oldPatternCount;
            }

            string attemptChoice;
            string choice = output.substr(output.size() - currentPatternPosition - detectedPatternCount * detectedPattern.size(), detectedPatternCount * detectedPattern.size());

            // Check if we can create a loop to the right
            if (dir != 1) {
                char rightRune = rune[bound(currentZone+1)];
                int rightDist = distance(rightRune, ' ');
                if (rightDist <= detectedPatternCount) {
                    if (rightRune >= 'N') {
                        attemptChoice = ">[<" + detectedPattern + ">+]<" + repeat(detectedPattern, detectedPatternCount - rightDist);
                        if (attemptChoice.size() < choice.size())
                            choice = attemptChoice;
                    }
                    else if (rightRune != ' ') {
                        attemptChoice = ">[<" + detectedPattern + ">-]<" + repeat(detectedPattern, detectedPatternCount - rightDist);
                        if (attemptChoice.size() < choice.size())
                            choice = attemptChoice;
                    }
                    else if (26 <= detectedPatternCount) { // rightRune == ' ' => rightDist == 0
                        attemptChoice = ">-[<" + detectedPattern + ">-]<" + repeat(detectedPattern, detectedPatternCount - 26);
                        if (attemptChoice.size() < choice.size())
                            choice = attemptChoice;
                    }
                    else { // Try to change space into a letter that we can use
                        attemptChoice = ">" + string(26 - detectedPatternCount + 1, '-') + "[<" + detectedPattern + ">-]<";
                        if (attemptChoice.size() < choice.size())
                            choice = attemptChoice;

                        attemptChoice = ">" + string(detectedPatternCount, '-') + "[<" + detectedPattern + ">+]<";
                        if (attemptChoice.size() < choice.size())
                            choice = attemptChoice;
                    }
                }
            }

            // Check if we can create a loop to the left
            if (dir != -1) {
                char leftRune = rune[bound(currentZone-1)];
                int leftDist = distance(leftRune, ' ');
                if (leftDist <= detectedPatternCount) {
                    if (leftRune >= 'N') {
                        attemptChoice = "<[>" + detectedPattern + "<+]>" + repeat(detectedPattern, detectedPatternCount - leftDist);
                        if (attemptChoice.size() < choice.size())
                            choice = attemptChoice;
                    }
                    else if (leftRune != ' ') {
                        attemptChoice = "<[>" + detectedPattern + "<-]>" + repeat(detectedPattern, detectedPatternCount - leftDist);
                        if (attemptChoice.size() < choice.size())
                            choice = attemptChoice;
                    }
                    else if (26 <= detectedPatternCount) { // leftRune == ' ' => leftDist == 0
                        attemptChoice = "<-[>" + detectedPattern + "<-]>" + repeat(detectedPattern, detectedPatternCount - 26);
                        if (attemptChoice.size() < choice.size())
                            choice = attemptChoice;
                    }
                    else { // Try to change space into a letter that we can use
                        attemptChoice = "<" + string(26 - detectedPatternCount + 1, '-') + "[>" + detectedPattern + "<-]>";
                        if (attemptChoice.size() < choice.size())
                            choice = attemptChoice;

                        attemptChoice = "<" + string(detectedPatternCount, '-') + "[>" + detectedPattern + "<+]>";
                        if (attemptChoice.size() < choice.size())
                            choice = attemptChoice;
                    }
                }
            }

            // If we profit by looping then do so (and try again in case we opened other posibilities)
            if (choice.size() < detectedPattern.size() * detectedPatternCount) {
                if (choice[0] == '<')
                    rune[bound(currentZone-1)] = ' ';
                else if (choice[0] == '>')
                    rune[bound(currentZone+1)] = ' ';

                output = output.substr(0, output.size() - currentPatternPosition - detectedPatternCount * detectedPattern.size()) + choice + output.substr(output.size() - currentPatternPosition);

                detectedPatternCount = 0;
                detectedPattern = "";

                testPattern(' ');
                currentPatternPosition = 0;
                if (!detectedPattern.empty())
                    testPattern(' ');
            }

            currentPatternPosition = 0;
            detectedPatternCount = 0;
            detectedPattern = "";
        }
    }
    else { // There is no pattern yet
        findPattern();
        if (detectedPattern.size() > 1)
            currentPatternPosition = 1;
    }
}

void optimizeOutput()
{
    // Don't move in one direction and then immediately move to the other
    for (unsigned int i = 0; i < output.size()-1; ++i) {
        if (output[i] == '<' && output[i+1] == '>') {
            output = output.substr(0, i) + output.substr(i+2);
        }
        else if (output[i] == '>' && output[i+1] == '<') {
            output = output.substr(0, i) + output.substr(i+2);
        }
    }

    // Don't keep movements at the end
    while (!output.empty() && (output[output.size()-1] == '<' || output[output.size()-1] == '>')) {
        output = output.substr(0, output.size()-1);
    }
}

void prevChar()
{
    testPattern('-');

    if (rune[currentZone] == ' ')
        rune[currentZone] = 'Z';
    else if (rune[currentZone] == 'A')
        rune[currentZone] = ' ';
    else
        rune[currentZone] -= 1;

    output += "-";
}

void nextChar()
{
    testPattern('+');

    if (rune[currentZone] == ' ')
        rune[currentZone] = 'A';
    else if (rune[currentZone] == 'Z')
        rune[currentZone] = ' ';
    else
        rune[currentZone] += 1;

    output += "+";
}

void goLeft()
{
    testPattern('<');

    output += "<";
    currentZone = bound(currentZone - 1);
    if (currentZone == leftBorderUnsearched)
        rightBorderUnsearched -= 1;
}

void goRight()
{
    testPattern('>');

    output += ">";
    currentZone = bound(currentZone + 1);
    if (currentZone == leftBorderUnsearched)
        leftBorderUnsearched += 1;
}

void print()
{
    testPattern('.');

    output += ".";
}

void hardcodedStrategies(string optimalOutput)
{
    output = "";

    // Find the different letters in the runes
    vector<char> letters;
    for (unsigned int i = 0; i < magicPhrase.size(); ++i) {
        if (magicPhrase[i] != ' ' && std::find(letters.begin(), letters.end(), magicPhrase[i]) == letters.end())
            letters.push_back(magicPhrase[i]);
    }

    // Try with each used letter on a separate rune
    int pos = 0;
    if (letters[0] >= 'N')
        output = repeat("-", 'Z' - letters[0] + 1);
    else if (letters[0] >= 'A')
        output = repeat("+", letters[0] - 'A' + 1);
    else
        output = "";

    bool match = true;
    int start = 1;
    output += ".";
    for (unsigned int i = 1; i < letters.size(); ++i) {
        if (letters[0] <= 'M')
            output += ">" + repeat("+", letters[i] - 'A' + 1);
        else
            output += ">" + repeat("-", 'Z' - letters[i] + 1);
        pos++;

        if (match) {
            if (letters[i] == magicPhrase[i]) {
                output += ".";
                start++;
            }
            else
                match = false;
        }
    }
    for (unsigned int i = start; i < magicPhrase.size(); ++i) {
        if ((magicPhrase[i] == ' ') && (pos != -1)) {
            if (abs(pos - 0) < abs(pos - ((int)letters.size()-1))) {
                output += repeat("<", pos + 1);
                pos = -1;
            }
            else if (abs(pos - 0) > abs(pos - ((int)letters.size()-1))) {
                output += repeat(">", letters.size() - pos);
                pos = letters.size();
            }
            else {
                // Try to choose based on the next characters
                int j = i;
                bool rightDirBest = true;
                while (++j < magicPhrase.size()) {
                    if (magicPhrase[j] != ' ') {
                        int letterPos = std::find(letters.begin(), letters.end(), magicPhrase[j]) - letters.begin();
                        if (pos < letterPos) {
                            output += repeat(">", letters.size() - pos);
                            pos = letters.size();
                        }
                        else {
                            output += repeat("<", pos + 1);
                            pos = -1;
                        }
                        break;
                    }
                }
            }
        }
        else if (magicPhrase[i] != ' ') {
            int letterPos = std::find(letters.begin(), letters.end(), magicPhrase[i]) - letters.begin();
            if (pos > letterPos)
                output += repeat("<", pos - letterPos);
            else
                output += repeat(">", letterPos - pos);

            pos = letterPos;
        }
        output += ".";
    }
    if (output.size() < optimalOutput.size())
        optimalOutput = output;

    output = optimalOutput;
}

int main()
{
    // Initialize zones
    for (unsigned int i = 0; i < 30; ++i)
        rune[i] = ' ';

    getline(cin, magicPhrase);

    for (unsigned int i = 0; i < magicPhrase.size(); ++i) {
        int d = numeric_limits<int>::max();
        int currentPenalty = 0;
        int newZone = currentZone;

        // Find the best zone to move to for this letter
        for (int j = 0; j < ZONES; ++j) {
            // We don't have to look at empty stones behind other empty ones
            if (j > leftBorderUnsearched && j < rightBorderUnsearched)
                continue;

            int zoneDist = min<int>(abs(j - currentZone), ZONES - abs(j - currentZone));

            // Calculate amount of letter changes required
            int dist = distance(rune[j], magicPhrase[i]);

            // Add penalty when removing letter that we need next turn
            int penalty = 0;
            if (i > 0 && i != magicPhrase.size()-1) {
                if (magicPhrase[i+1] == magicPhrase[i-1]) {
                    penalty = max<int>(0, ceil(abs(dist) / 2.0) - zoneDist);
                }
            }

            // Check if this zone is better than what we currently have selected
            if (abs(dist) + penalty + zoneDist < abs(d) + currentPenalty) {
                d = dist;
                newZone = j;
                currentPenalty = penalty;
            }
        }

        // Move to the new zone
        int oldZone = currentZone;
        if (newZone > oldZone) {
            if (newZone - oldZone < ZONES / 2) {
                for (unsigned int k = 0; k < newZone - oldZone; ++k) {
                    goRight();
                }
            }
            else {
                for (unsigned int k = 0; k < ZONES - newZone + oldZone; ++k) {
                    goLeft();
                }
            }
        }
        else if (newZone < oldZone) {
            if (oldZone - newZone < ZONES / 2) {
                for (unsigned int k = 0; k < oldZone - newZone; ++k) {
                    goLeft();
                }
            }
            else {
                for (unsigned int k = 0; k < ZONES - oldZone + newZone; ++k) {
                    goRight();
                }
            }
        }

        // Change the letter on the rune to the one we want
        while (d > 0) {
            nextChar();
            d--;
        }
        while (d < 0) {
            prevChar();
            d++;
        }

        // Print the letter that we just put on the rune
        print();
    }

    testPattern(' ');
    optimizeOutput();

    hardcodedStrategies(output);

    cout << output << endl;
}
