#include "card.hpp"
#include "TGUI/Texture.hpp"
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
 * @param imgPath Путь до изображения карты
 */
Card::Card(unsigned short int id, std::string name, std::string imgPath)
  : texture(imgPath)
  , name(name)
  , id(id)
{
}

/**
 * @brief Возвращает спрайт карты для отрисовки
 *
 * @return Спрайт карты
 */
const tgui::Texture&
Card::getTexture() const
{
    return this->texture;
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

/*
 *  МЕТОДЫ КЛАССА КАРТЫ-ТЕМЫ
 */

/**
 * @brief Конструктор карты-темы. Ничем не отличается от базового конструктора
 *
 * @param id Id карты
 * @param name Название карты
 * @param imgPath Путь до изображения карты
 */
CardTheme::CardTheme(unsigned short int id,
                     std::string name,
                     std::string imgPath)
  : Card(id, name, imgPath)
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
 * @param imgPath Путь до изображения карты
 * @param themes Набор Id карт-тем
 * @param isNumOfThemes Это цель на количество тем?
 * @param isNumOfCards Это цель на количество карт?
 */
CardGoal::CardGoal(unsigned short int id,
                   std::string name,
                   std::string imgPath,
                   std::vector<unsigned short int>& themes,
                   bool isNumOfThemes,
                   bool isNumOfCards)
  : Card(id, name, imgPath)
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
 * @param imgPath Путь до изображения карты
 * @param action Указатель на функцию, которая будет вызвана при использовании
 * карты
 */
CardAction::CardAction(unsigned short int id,
                       std::string name,
                       std::string imgPath,
                       std::string action)
  : Card(id, name, imgPath)
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
 * @param imgPath Путь до изображения карты
 * @param params Набор параметров карты-правила
 */
CardRule::CardRule(unsigned short int id,
                   std::string name,
                   std::string imgPath,
                   RulesParams& params)
  : Card(id, name, imgPath)
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

/**
 * @brief Конструктор для карты-темы
 * 
 * @param card Карта-тема
 */
Cards::Cards(CardTheme card)
  : data{ card }
{
}

/**
 * @brief Конструктор для карты-цели
 * 
 * @param card Карта-цель
 */
Cards::Cards(CardGoal card)
  : data{ card }
{
}

/**
 * @brief Конструктор для карты-действия
 * 
 * @param card Карта-действие
 */
Cards::Cards(CardAction card)
  : data{ card }
{
}

/**
 * @brief Конструктор для карты-правила
 * 
 * @param card Карта-правило
 */
Cards::Cards(CardRule card)
  : data{ card }
{
}

/**
 * @brief Возвращает Id карты
 * 
 * @return const unsigned short int Id карты
 */
const unsigned short int
Cards::getId() const
{
    if (std::holds_alternative<CardTheme>(data)) {
        return std::get<CardTheme>(data).getId();
    } else if (std::holds_alternative<CardGoal>(data)) {
        return std::get<CardGoal>(data).getId();
    } else if (std::holds_alternative<CardAction>(data)) {
        return std::get<CardAction>(data).getId();
    } else {
        return std::get<CardRule>(data).getId();
    }
}

/**
 * @brief Играет данную карту
 * 
 * @param state Игровое состояние
 */
void
Cards::play(State* state)
{
    if (std::holds_alternative<CardTheme>(data)) {
        std::get<CardTheme>(data).play(state);
    } else if (std::holds_alternative<CardGoal>(data)) {
        std::get<CardGoal>(data).play(state);
    } else if (std::holds_alternative<CardAction>(data)) {
        std::get<CardAction>(data).play(state);
    } else {
        std::get<CardRule>(data).play(state);
    }
}

/**
 * @brief Возвращает название карты
 * 
 * @return const std::string название карты
 */
const std::string
Cards::getName() const
{
    if (std::holds_alternative<CardTheme>(data)) {
        return std::get<CardTheme>(data).getName();
    } else if (std::holds_alternative<CardGoal>(data)) {
        return std::get<CardGoal>(data).getName();
    } else if (std::holds_alternative<CardAction>(data)) {
        return std::get<CardAction>(data).getName();
    } else {
        return std::get<CardRule>(data).getName();
    }
}

/**
 * @brief Возвращает вектор Id карт-тем, которые содержатся в цели.
 * Если карта - не цель, то вернется пустой вектор
 * 
 * @return const std::vector<unsigned short int> Вектор Id карт-тем
 * @retval {} Если это не карта-цель
 */
const std::vector<unsigned short int>
Cards::getThemes() const
{
    if (std::holds_alternative<CardGoal>(data))
        return std::get<CardGoal>(data).getThemes();
    return {};
}

/**
 * @brief Возвращает параметры правил, если это карта-правило.
 * Иначе возвращается структура по умолчанию
 * 
 * @return const RulesParams Параметры правила
 * @retval {} Если это не карта-правило
 */
const RulesParams
Cards::getParams() const
{
    if (std::holds_alternative<CardRule>(data))
        return std::get<CardRule>(data).getParams();
    return {};
}

/**
 * @brief Возвращает текстуру данной карты
 * 
 * @return const tgui::Texture& Текстура карты
 */
const tgui::Texture&
Cards::getTexture() const
{
    if (std::holds_alternative<CardTheme>(data)) {
        return std::get<CardTheme>(data).getTexture();
    } else if (std::holds_alternative<CardGoal>(data)) {
        return std::get<CardGoal>(data).getTexture();
    } else if (std::holds_alternative<CardAction>(data)) {
        return std::get<CardAction>(data).getTexture();
    } else {
        return std::get<CardRule>(data).getTexture();
    }
}

/**
 * @brief Перегрузка оператора сравнения карты с указанным id.
 * Необходимо для работы std::find и т.д.
 * 
 * @param id Id для сравнения
 * @return true Если Id совпадают
 * @return false Если Id не совпадают
 */
bool
Cards::operator==(unsigned short int id)
{
    return this->getId() == id;
}

/**
 * @brief Перегрузка оператора сравнения карты с указанным именем.
 * Необходимо для работы std::find и т.д.
 * 
 * @param name Имя для сравнения
 * @return true Если имена совпадают
 * @return false Если имена не совпадают
 */
bool
Cards::operator==(std::string name)
{
    return this->getName() == name;
}