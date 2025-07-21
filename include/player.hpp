#pragma once

#include "card.hpp"
#include "state.hpp"

class State;

class Player
{
private:
    std::vector<Cards> hand;
    std::vector<unsigned short int> tableThemes;
    bool firstTurn = true;

public:
    Player();
    void takeCards(State& state);
    const std::vector<unsigned short int> getThemes() const;
    const void addTheme(unsigned short int theme);
    const bool isFirstTurn() const;
};