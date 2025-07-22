#pragma once

#include "card.hpp"
#include "state.hpp"

// Объявление класса State для избежания цикличного включения
class State;

/**
 * @brief Класс для представления игрока
 *
 */
class Player
{
private:
    std::vector<unsigned short int> hand;        // Карты на руки
    std::vector<unsigned short int> tableThemes; // Темы на столе
    bool firstTurn = true;

public:
    Player();
    void takeCards(State& state);
    const std::vector<unsigned short int> getThemes() const;
    const unsigned short int numOfCardsInHands() const;
    const void addTheme(unsigned short int theme);
    const bool isFirstTurn() const;
};