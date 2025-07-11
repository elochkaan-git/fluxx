#pragma once

#include "card.hpp"
#include <vector>


class Player;

class State
{
private:
    std::vector<Cards> deck, dump;
    std::vector<Player*> players;
    RulesParams params;
    char currentPlayerID = 0, currentCardID = 0;

public:
    State(std::vector<Player*>& players);
    const Cards getCard();
    void addCardTheme(std::string name, std::string imgPath, std::string theme);
    void addCardAction(std::string name, std::string imgPath, std::string action);
    void addCardGoal(std::string name, std::string imgPath, std::vector<std::string>& themes, bool isNumOfThemes, bool isNumOfCards);
    void addCardRule(std::string name, std::string imgPath, RulesParams& params);
    const RulesParams* getRules() const;
};