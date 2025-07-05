#include "player.hpp"
#include "state.hpp"

Player::Player() : hand(0), tableThemes(0) {}

void Player::takeCards(State& state) {
    for(unsigned short int i = 0; i < 3; ++i) {
        this->hand.push_back(state.getCard());
    }
}