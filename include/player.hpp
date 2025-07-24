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
protected:
    unsigned short int id;
    std::vector<unsigned short int> hand;        // Карты на руки
    std::vector<unsigned short int> tableThemes; // Темы на столе
    bool firstTurn = true;

public:
    unsigned short int moves = 0;
    unsigned short int takes = 0;

    Player(unsigned short int id);

    void takeCards(State& state);
    void addTheme(unsigned short int theme);
    void deleteCardById(unsigned short int id);

    const unsigned short int getId() const;
    const std::vector<unsigned short int>& getHand() const;
    const std::vector<unsigned short int>& getThemes() const;
    const unsigned short int numOfCardsInHands() const;
    const unsigned short int randomCard() const;

    const bool isFirstTurn() const;
};