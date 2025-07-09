#include "player.hpp"
#include "state.hpp"

Player::Player() : hand(0), tableThemes(0) {}

void Player::takeCards(State& state) {
    if(isFirstTurn)
    { 
        for(unsigned short int i = 0; i < 3; ++i) 
        {
            this->hand.push_back(state.getCard());
        }
        isFirstTurn = false;
    }
    else
    {
        for(unsigned short int i = 0; i < state.getRules()->take; ++i) 
        {
            this->hand.push_back(state.getCard());
        }
    }
}