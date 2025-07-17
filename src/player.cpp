#include "player.hpp"
#include "card.hpp"
#include "state.hpp"
#include <memory>
#include <vector>

Player::Player()
  : hand(0)
  , tableThemes(0)
{
}

void
Player::takeCards(State& state)
{
    if (firstTurn) {
        for (unsigned short int i = 0; i < 3; ++i) {
            this->hand.push_back(state.getCard());
        }
        firstTurn = false;
    } else {
        for (unsigned short int i = 0; i < state.getRules()->take; ++i) {
            this->hand.push_back(state.getCard());
        }
    }
}

const std::vector<std::shared_ptr<CardTheme>>
Player::getThemes() const
{
    return this->tableThemes;
}

const bool
Player::isFirstTurn() const
{
    return firstTurn;
}

// const std::shared_ptr<CardGoal>
// Player::getCard(int id) const
// {
//     return std::get<std::shared_ptr<CardGoal>>(hand[id]);
// }

// void
// Player::setThemes(const std::shared_ptr<CardTheme>& theme)
// {
//     tableThemes.push_back(theme);
// }

// const std::shared_ptr<CardTheme>
// Player::getCardT(int id) const
// {
//     return std::get<std::shared_ptr<CardTheme>>(hand[id]);
// }