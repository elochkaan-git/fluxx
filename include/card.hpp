#pragma once

#include <TGUI/Texture.hpp>
#include <string>
#include <variant>
#include <vector>

// Объявление класса State для избежания цикличного включения
class State;

/**
 * \brief Структура, содержащая параметры карт-правил
 */
struct RulesParams
{
    // Значения действительны, только если > 0
    short int handLimit = -1;  // Предел руки
    short int themeLimit = -1; // Предел тем
    short int play = -1;       // Сколько сыграть
    short int take = -1;       // Сколько взять

    // Состояния для особых карт
    bool blindGame = false;    // Игра вслепую
    bool castling = false;     // Рокировка
    bool dance = false;        // Танцуют все!
    bool duplet = false;       // Дуплет
    bool enough = false;       // С меня хватит!
    bool inflation = false;    // Инфляция
    bool poverty = false;      // Бедность не порок
    bool random = false;       // Наугад
    bool rich = false;         // Богато жить не запретишь
    bool spinAndTurn = false;  // Кручу-верчу
    bool utilize = false;      // Переработка
    bool withoutHands = false; // Как без рук
};

/**
 * \brief Базовый класс карты
 *
 * Базовый класс карты, от которого наследуются все остальные типы карт
 */
class Card
{
protected:
    unsigned short int id;
    tgui::Texture texture;
    std::string name = "Default";

public:
    Card(unsigned short int id, std::string name, std::string imgPath);
    const tgui::Texture& getTexture() const;
    const std::string& getName() const;
    const unsigned short int& getId() const;
    bool operator==(unsigned short int id);
    virtual void play(State* state) = 0;
};

/**
 * \brief Класс карты-темы
 */
class CardTheme : public Card
{
public:
    CardTheme(unsigned short int id, std::string name, std::string imgPath);
    void play(State* state) override;
};

/**
 * \brief Класс карты-цели
 */
class CardGoal : public Card
{
protected:
    std::vector<unsigned short int> themes = {};
    bool isNumOfThemes = false, isNumOfCards = false;

public:
    CardGoal(unsigned short int id,
             std::string name,
             std::string imgPath,
             std::vector<unsigned short int>& themes,
             bool isNumOfThemes,
             bool isNumOfCards);
    void play(State* state) override;
    const std::vector<unsigned short int> getThemes() const;
};

/**
 * \brief Класс карты-действия
 */
class CardAction : public Card
{
public:
    void (*action)(State* state);
    CardAction(unsigned short int id,
               std::string name,
               std::string imgPath,
               std::string action);
    void play(State* state) override;
};

/**
 * \brief Класс карты-правиляа
 */
class CardRule : public Card
{
protected:
    RulesParams params;

public:
    CardRule(unsigned short int id,
             std::string name,
             std::string imgPath,
             RulesParams& params);
    void play(State* state) override;
    const RulesParams getParams() const;
};

/** Использование слово Cards вместо объемного типа */
using Cards = std::variant<CardAction, CardGoal, CardRule, CardTheme>;

struct CardPlay
{
    State* state;
    CardPlay(State* state) { this->state = state; }
    void operator()(CardTheme& card) { card.play(state); }
    void operator()(CardGoal& card) { card.play(state); }
    void operator()(CardAction& card) { card.play(state); }
    void operator()(CardRule& card) { card.play(state); }
};

struct CardTexture
{
    tgui::Texture operator()(CardTheme& card) { return card.getTexture(); }
    tgui::Texture operator()(CardGoal& card) { return card.getTexture(); }
    tgui::Texture operator()(CardAction& card) { return card.getTexture(); }
    tgui::Texture operator()(CardRule& card) { return card.getTexture(); }
    tgui::Texture operator()(const CardTheme& card) { return card.getTexture(); }
    tgui::Texture operator()(const CardGoal& card) { return card.getTexture(); }
    tgui::Texture operator()(const CardAction& card) { return card.getTexture(); }
    tgui::Texture operator()(const CardRule& card) { return card.getTexture(); }
};

struct CardId
{
    unsigned short int operator()(CardTheme& card) { return card.getId(); }
    unsigned short int operator()(CardGoal& card) { return card.getId(); }
    unsigned short int operator()(CardAction& card) { return card.getId(); }
    unsigned short int operator()(CardRule& card) { return card.getId(); }
    unsigned short int operator()(const CardTheme& card) { return card.getId(); }
    unsigned short int operator()(const CardGoal& card) { return card.getId(); }
    unsigned short int operator()(const CardAction& card) { return card.getId(); }
    unsigned short int operator()(const CardRule& card) { return card.getId(); }
};