#pragma once

#include "card.hpp"
#include <memory>
#include <vector>

class Player;

class State
{
private:
    std::vector<Cards> deck, dump;
    std::vector<Player*> players;
    std::vector<std::shared_ptr<CardGoal>> goals;
    RulesParams params;
    unsigned char currentPlayerID = 0, currentCardID = 0;
    bool isNumOfThemes = false, isNumOfCards = false;

public:
    State(std::vector<Player*>& players);
    Cards getCard();
    const std::vector<Cards>& getDeck() const;
    void addCardTheme(std::string name, std::string imgPath);
    void addCardAction(std::string name,
                       std::string imgPath,
                       std::string action);
    void addCardGoal(std::string name,
                     std::string imgPath,
                     std::vector<std::shared_ptr<CardTheme>>& themes,
                     bool isNumOfThemes,
                     bool isNumOfCards);
    void addCardRule(std::string name,
                     std::string imgPath,
                     RulesParams& params);
    void setGoal(std::shared_ptr<CardGoal> goal);
    bool checkWinner();
    Player* currentPlayer();
    Player* nextPlayer();
    Player* nextPlayer(unsigned short int n);
    void nextMove();
    const unsigned short int howManyTake() const;
    const unsigned short int howManyPlay() const;
    const RulesParams* getRules() const;
};