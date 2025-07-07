#include "state.hpp"
#include <filesystem>
#include <iostream>

std::vector<std::variant<CardAction*, CardGoal*, CardRule*, CardTheme*>> loadImages()
{
    std::vector<std::variant<CardAction*, CardGoal*, CardRule*, CardTheme*>> result(99);
    for(const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator("./resources/img"))
    {
        if(entry.path().filename() == "default.png") std::cout << "WORL!!";
    }
}

State::State(std::vector<Player*>& players) {
    this->players = players;
    this->deck = loadImages();
}

std::variant<CardAction*, CardGoal*, CardRule*, CardTheme*> State::getCard() {
    return this->deck[this->currentCardID++];
}