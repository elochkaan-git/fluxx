#include "player.hpp"
#include "card.hpp"
#include "state.hpp"
#include <algorithm>
#include <vector>

/**
 * @brief Конструктор класса Player
 *
 * Создает новый объект класса Player с пустыми рукой и темами на столе
 */
Player::Player(unsigned short int id)
  : hand()
  , tableThemes(0)
{
    this->id = id;
}

/**
 * @brief Добавляет в руку игрока необходимое число карт
 *
 * @param state Игровое состояние
 */
void
Player::takeCards(State& state)
{
    if (firstTurn) {
        for (unsigned short int i = 0; i < 3; ++i) {
            this->hand.push_back(state.getCardFromTop());
        }
        firstTurn = false;
    } else {
        for (unsigned short int i = 0; i < state.getRules()->take; ++i) {
            this->hand.push_back(state.getCardFromTop());
        }
    }
}

/**
 * @brief Возвращает набор Id карт-тем, лежащих у игрока на столе
 *
 * @return const std::vector<unsigned short int> Набор Id карт-тем
 */
const std::vector<unsigned short int>&
Player::getThemes() const
{
    return this->tableThemes;
}

/**
 * @brief Проверяет, первый ли ход у игрока
 *
 * @return true Если первый
 * @return false Если не первый
 */
const bool
Player::isFirstTurn() const
{
    return firstTurn;
}

/**
 * @brief Добавляет Id карты-темы в вектор Id карт-тем, лежащих на столе
 *
 * @param themeId Id сыгранной карты-темы
 */
void
Player::addTheme(unsigned short int themeId)
{
    tableThemes.push_back(themeId);
}

/**
 * @brief Возвращает количество карт в руке
 *
 * @return const unsigned short int Количество карт в руке
 */
const unsigned short int
Player::numOfCardsInHands() const
{
    return this->hand.size();
}

const unsigned short int
Player::getId() const
{
    return this->id;
}

void
Player::deleteCardById(unsigned short int id)
{
    auto ptr = std::find(hand.begin(), hand.end(), id);
    if (ptr != hand.end()) {
        hand.erase(ptr);
        return;
    }
    ptr = std::find(tableThemes.begin(), tableThemes.end(), id);
    if (ptr != tableThemes.end()) {
        tableThemes.erase(ptr);
        return;
    }
}

const std::vector<unsigned short int>&
Player::getHand() const
{
    return hand;
}