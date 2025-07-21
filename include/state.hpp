#pragma once

#include "card.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class Player;

class State
{
private:
    std::vector<Cards> deck, dump;
    std::vector<Player*> players;
    std::vector<unsigned short int> goals, rules;
    RulesParams params;
    unsigned char currentPlayerID = 0, currentCardID = 0;
    bool isNumOfThemes = false, isNumOfCards = false;
    void clearRules();

public:
    State(std::vector<Player*>& players);
    Cards getCard();
    Cards* getCardById(unsigned short int id);
    const std::vector<Cards>& getDeck() const;
    void addCardTheme(unsigned short int id,
                      std::string name,
                      std::string imgPath);
    void addCardAction(unsigned short int id,
                       std::string name,
                       std::string imgPath,
                       std::string action);
    void addCardGoal(unsigned short int id,
                     std::string name,
                     std::string imgPath,
                     std::vector<unsigned short int>& themes,
                     bool isNumOfThemes,
                     bool isNumOfCards);
    void addCardRule(unsigned short int id,
                     std::string name,
                     std::string imgPath,
                     RulesParams& params);
    void setGoal(unsigned short int goalId);
    void addRule(unsigned short int ruleId);
    bool checkWinner();
    Player* currentPlayer();
    Player* nextPlayer();
    Player* nextPlayer(unsigned short int n);
    void nextMove();
    const unsigned short int howManyTake() const;
    const unsigned short int howManyPlay() const;
    const RulesParams* getRules() const;
    void updateRules();
};