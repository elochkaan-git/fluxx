#pragma once

#include "card.hpp"
#include "state.hpp"
#include <memory>

class State;

class Player
{
private:
    std::vector<Cards> hand;
    std::vector<std::shared_ptr<CardTheme>> tableThemes;
    bool isFirstTurn = true;

public:
    Player();
    void takeCards(State& state);
    // void setThemes(const std::shared_ptr<CardTheme>& theme);
    const std::vector<std::shared_ptr<CardTheme>> getThemes() const;
    // const std::shared_ptr<CardGoal> getCard(int id) const;
    // const std::shared_ptr<CardTheme> getCardT(int id) const;
};