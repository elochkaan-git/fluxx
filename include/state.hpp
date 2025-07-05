#pragma once

#include "card.hpp"
#include <vector>
#include <variant>


class Player;

class State
{
private:
    std::vector<std::variant<CardAction*, CardGoal*, CardRule*, CardTheme*>> deck, dump;
    std::vector<Player*> players;
    RulesParams params;
    char currentPlayerID = 0, currentCardID = 0;

public:
    State(std::vector<Player*>& players);
    std::variant<CardAction*, CardGoal*, CardRule*, CardTheme*> getCard();
    // FIXME: ДОБАВИТЬ ДЕСТРУКТОР
};