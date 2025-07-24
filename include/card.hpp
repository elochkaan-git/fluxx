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
    // Конструктор
    Card(unsigned short int id, std::string name, std::string imgPath);

    // Геттеры
    const tgui::Texture& getTexture() const;
    const std::string& getName() const;
    const unsigned short int getId() const;

    // Операторы сравнения
    bool operator==(unsigned short int id) const;
    bool operator==(std::string name) const;

    // Виртуальная функция для наследников
    virtual void play(State* state) = 0;
};

/**
 * \brief Класс карты-темы
 */
class CardTheme : public Card
{
public:
    // Конструктор
    CardTheme(unsigned short int id, std::string name, std::string imgPath);

    // Реализация виртуальной функции
    void play(State* state) override;
};

/**
 * \brief Класс карты-цели
 */
class CardGoal : public Card
{
protected:
    std::vector<unsigned short int> themes = {}; // Id карт-тем
    bool isNumOfThemes = false, isNumOfCards = false;

public:
    CardGoal(unsigned short int id,
             std::string name,
             std::string imgPath,
             std::vector<unsigned short int>& themes,
             bool isNumOfThemes,
             bool isNumOfCards);
    void play(State* state) override;
    const std::vector<unsigned short int>& getThemes() const;
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
    const RulesParams& getParams() const;
};

/**
 * @brief Структура для унифицирования интерфейса взаимодействия с картами.
 * Собирает в себе все необходимые функции для связки классов карт с ядром и
 * фронтом
 *
 */
struct Cards
{
    std::variant<CardTheme, CardGoal, CardAction, CardRule> data;

    Cards(CardTheme card);
    Cards(CardGoal card);
    Cards(CardAction card);
    Cards(CardRule card);

    const unsigned short int getId() const;
    const std::string& getName() const;
    const RulesParams getParams() const;
    const tgui::Texture& getTexture() const;
    const std::vector<unsigned short int> getThemes() const;

    bool operator==(unsigned short int id);
    bool operator==(std::string name);

    void play(State* state);
};