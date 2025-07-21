#include "player.hpp"
#include "card.hpp"
#include "state.hpp"
#include <vector>

Player::Player()
  : hand()
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

const std::vector<unsigned short int>
Player::getThemes() const
{
    return this->tableThemes;
}

const bool
Player::isFirstTurn() const
{
    return firstTurn;
}

const void
Player::addTheme(unsigned short int theme)
{
    tableThemes.push_back(theme);
}