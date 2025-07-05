#include "state.hpp"


// std::vector<std::variant<CardAction*, CardGoal*, CardRule*, CardTheme*>> loadImages();

State::State(std::vector<Player*>& players) {
    this->players = players;
    // this->deck = loadImages();
}

std::variant<CardAction*, CardGoal*, CardRule*, CardTheme*> State::getCard() {
    return this->deck[this->currentCardID++];
}