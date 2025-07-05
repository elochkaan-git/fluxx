#include "card.hpp"
#include "state.hpp"
#include <variant>


class State;

class Player
{
private:
    std::vector<std::variant<CardAction*, CardGoal*, CardRule*, CardTheme*>> hand;
    std::vector<CardTheme*> tableThemes;
    bool isFirstTurn = true;

public:
    Player();
    void takeCards(State& state);
    // FIXME: ДОБАВИТЬ ДЕСТРУКТОР
};