#include "card.hpp"
#include "actions.hpp"
#include "player.hpp"
#include "state.hpp"
#include <string>

/*
 *  МЕТОДЫ РОДИТЕЛЬСКОГО КЛАССА
 */

/**
 * @brief Базовый конструктор, создающий карту с именем, id и текстурой
 * @warning Нужно переделать размеры и позицию в конструкторе спрайта
 *
 * @param id Id карты
 * @param name Название карты
 * @param t Ссылка на текстуру для карты
 */
Card::Card(unsigned short int id, std::string name, sf::Texture& t)
  : sprite(t, { { 10, 10 }, { 50, 60 } })
  , name(name)
  , id(id)
{
}

/**
 * @brief Возвращает спрайт карты для отрисовки
 *
 * @return Спрайт карты
 */
const sf::Sprite&
Card::getSprite() const
{
    return this->sprite;
}

/**
 * @brief Возвращает строку - название карты
 *
 * @return const std::string& Название карты
 */
const std::string&
Card::getName() const
{
    return this->name;
}

/**
 * @brief Возвращает Id карты
 *
 * @return const unsigned short& Id карты
 */
const unsigned short int&
Card::getId() const
{
    return id;
}

/**
 * @brief Перегрузка оператора сравнения
 *
 * Эта функция нужна для работы функций вроде std::find. Это значительно
 * упрощает сравнение карт, ведь теперь сраниваются не два объекта, а их Id
 *
 * @param id Id сравниваемой карты
 * @return true Если Id совпадают
 * @return false Если Id не совпадают
 */
bool
Card::operator==(unsigned short int id)
{
    return this->id == id;
}

/*
 *  МЕТОДЫ КЛАССА КАРТЫ-ТЕМЫ
 */

/**
 * @brief Конструктор карты-темы. Ничем не отличается от базового конструктора
 *
 * @param id Id карты
 * @param name Название карты
 * @param t Ссылка на текстуру для карты
 */
CardTheme::CardTheme(unsigned short int id, std::string name, sf::Texture& t)
  : Card(id, name, t)
{
}

/**
 * @brief Играет карту. Вызывать при использовании карты
 *
 * @param state Игровое состояние
 */
void
CardTheme::play(State* state)
{
    state->currentPlayer()->deleteCardById(getId());
    state->currentPlayer()->addTheme(getId());
}

/*
 *  МЕТОДЫ КЛАССА КАРТЫ-ЦЕЛИ
 */

/**
 * @brief Конструктор карты-цели
 *
 * @param id Id карты
 * @param name Название карты
 * @param t Ссылка на текстуру для карты
 * @param themes Набор Id карт-тем
 * @param isNumOfThemes Это цель на количество тем?
 * @param isNumOfCards Это цель на количество карт?
 */
CardGoal::CardGoal(unsigned short int id,
                   std::string name,
                   sf::Texture& t,
                   std::vector<unsigned short int>& themes,
                   bool isNumOfThemes,
                   bool isNumOfCards)
  : Card(id, name, t)
{
    this->themes = themes;
    this->isNumOfThemes = isNumOfThemes;
    this->isNumOfCards = isNumOfCards;
}

/**
 * @brief Возвращает Id карт-тем, которые входят в цель
 *
 * @return const std::vector<unsigned short int> Набор Id карт-тем
 */
const std::vector<unsigned short int>
CardGoal::getThemes() const
{
    return this->themes;
}

/**
 * @brief Играет карту. Вызывать при использовании карты
 *
 * @param state Игровое состояние
 */
void
CardGoal::play(State* state)
{
    state->setGoal(getId());
    state->currentPlayer()->deleteCardById(getId());
}

/*
 *  МЕТОДЫ КЛАССА КАРТЫ-ДЕЙСТВИЯ
 */

/**
 * @brief Конструктор карты-действия
 *
 * @param id Id карты
 * @param name Название карты
 * @param t Ссылка на текстуру для карты
 * @param action Указатель на функцию, которая будет вызвана при использовании
 * карты
 */
CardAction::CardAction(unsigned short int id,
                       std::string name,
                       sf::Texture& t,
                       std::string action)
  : Card(id, name, t)
{
    this->action = actions[action];
}

/**
 * @brief Играет карту. Вызывать при использовании карты
 *
 * @param state Игровое состояние
 */
void
CardAction::play(State* state)
{
    this->action(state);
    state->currentPlayer()->deleteCardById(getId());
}

/*
 *  МЕТОДЫ КЛАССА КАРТЫ-ПРАВИЛА
 */

/**
 * @brief Конструктор карты-правила
 *
 * @param id Id карты
 * @param name Название карты
 * @param t Ссылка на текстуру для карты
 * @param params Набор параметров карты-правила
 */
CardRule::CardRule(unsigned short int id,
                   std::string name,
                   sf::Texture& t,
                   RulesParams& params)
  : Card(id, name, t)
{
    this->params = params;
}

/**
 * @brief Возвращает параметры карты-правил
 *
 * @return const RulesParams Параметры карты-правил
 */
const RulesParams
CardRule::getParams() const
{
    return params;
}

/**
 * @brief Играет карту. Вызывать при использовании карты
 *
 * @param state Игровое состояние
 */
void
CardRule::play(State* state)
{
    state->addRule(getId());
    state->currentPlayer()->deleteCardById(getId());
}