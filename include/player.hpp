#include "card.hpp"
#include "state.hpp"


class State;

class Player
{
private:
    std::vector<Cards> hand;
    std::vector<CardTheme*> tableThemes;
    bool isFirstTurn = true;

public:
    Player();
    void takeCards(State& state);
};