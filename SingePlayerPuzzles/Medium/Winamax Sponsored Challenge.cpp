#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int getCardValue(string card)
{
    int val = atoi(card.substr(0, card.length()-1).c_str());
    if (val > 0)
        return val;
    else
    {
        if (card[0] == 'J')
            return 11;
        else if (card[0] == 'Q')
            return 12;
        else if (card[0] == 'K')
            return 13;
        else if (card[0] == 'A')
            return 14;
    }
}

int getWinner(string card1, string card2)
{
    if (getCardValue(card1) > getCardValue(card2))
        return 1;
    else if (getCardValue(card1) < getCardValue(card2))
        return 2;
    else
        return 0;
}

int main()
{
    deque<string> cardsP1;
    deque<string> cardsP2;
    deque<string> cardsOnTableP1;
    deque<string> cardsOnTableP2;
    
    int n; // the number of cards for player 1
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string cardp1; // the n cards of player 1
        cin >> cardp1; cin.ignore();
        
        cardsP1.push_back(cardp1);
    }
    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
    for (int i = 0; i < m; i++) {
        string cardp2; // the m cards of player 2
        cin >> cardp2; cin.ignore();
        
        cardsP2.push_back(cardp2);
    }

    int rounds = 0;
    while (true)
    {
        // The game ends when one player no longer has cards
        if (cardsP1.empty())
        {
            cout << 2 << " " << rounds << endl;
            return 0;
        }
        else if (cardsP2.empty())
        {
            cout << 1 << " " << rounds << endl;
            return 0;
        }
        
        bool playingWar;
        do
        {
            playingWar = false;
            
            // Each player draws a card
            cardsOnTableP1.push_back(cardsP1.front());
            cardsOnTableP2.push_back(cardsP2.front());
            cardsP1.pop_front();
            cardsP2.pop_front();
            
            // Play the round
            int roundWinner = getWinner(cardsOnTableP1.back(), cardsOnTableP2.back());
            cerr << cardsOnTableP1.back() << " " << cardsOnTableP2.back() << " " << roundWinner << endl;
            if (roundWinner == 1)
            {
                for (auto& card : cardsOnTableP1)
                    cardsP1.push_back(card);
    
                for (auto& card : cardsOnTableP2)
                    cardsP1.push_back(card);
                
                cardsOnTableP1.clear();
                cardsOnTableP2.clear();
            }
            else if (roundWinner == 2)
            {
                for (auto& card : cardsOnTableP1)
                    cardsP2.push_back(card);
    
                for (auto& card : cardsOnTableP2)
                    cardsP2.push_back(card);
                
                cardsOnTableP1.clear();
                cardsOnTableP2.clear();
            }
            else // war!
            {
                // If we don't have enough cards => draw
                if ((cardsP1.size() < 4) || (cardsP2.size() < 4))
                {
                    cout << "PAT" << endl;
                    return 0;
                }
                
                // Place 3 cards face down
                for (int i = 0; i < 3; ++i)
                {
                    cardsOnTableP1.push_back(cardsP1.front());
                    cardsOnTableP2.push_back(cardsP2.front());
                    cardsP1.pop_front();
                    cardsP2.pop_front();
                }
                
                // Draw the next cards
                playingWar = true;
            }
        } while (playingWar);
        
        rounds++;
    }
}
