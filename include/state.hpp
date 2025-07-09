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
    void addCardTheme(std::string name, std::string imgPath);
    const RulesParams* getRules() const;
};