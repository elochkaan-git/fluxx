#include "player.hpp"
#include "card.hpp"
#include "state.hpp"
#include <vector>

/**
 * @brief Конструктор класса Player
 *
 * Создает новый объект класса Player с пустыми рукой и темами на столе
 */
Player::Player()
  : hand()
  , tableThemes(0)
{
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
const std::vector<unsigned short int>
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
const void
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