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
    bool firstTurn = true;

public:
    Player();
    void takeCards(State& state);
    const std::vector<std::shared_ptr<CardTheme>> getThemes() const;
    const void addTheme(std::shared_ptr<CardTheme> theme);
    const bool isFirstTurn() const;
    // void setThemes(const std::shared_ptr<CardTheme>& theme);
    // const std::shared_ptr<CardGoal> getCard(int id) const;
    // const std::shared_ptr<CardTheme> getCardT(int id) const;
};