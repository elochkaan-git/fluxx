#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
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
    short int handLimit = -1;
    short int themeLimit = -1;
    short int play = -1;
    short int take = -1;

    bool blindGame = false;
    bool castling = false;
    bool dance = false;
    bool duplet = false;
    bool enough = false;
    bool inflation = false;
    bool poverty = false;
    bool random = false;
    bool rich = false;
    bool spinAndTurn = false;
    bool utilize = false;
    bool withoutHands = false;
};

/**
 * \brief Базовый класс карты
 *
 * Базовый класс карты, от которого наследуются все остальные типы карт
 */
class Card
{
protected:
    sf::Sprite sprite;
    std::string name = "Default";

public:
    Card(std::string name, sf::Texture& t);
    const sf::Sprite& getSprite() const;
    const std::string& getName() const;
    virtual void play(State* state) = 0;
};

/**
 * \brief Класс карты-темы
 */
class CardTheme
  : public Card
  , std::enable_shared_from_this<CardTheme>
{
public:
    CardTheme(std::string name, sf::Texture& t);
    bool operator==(const CardTheme& other) const;
    bool operator==(const std::shared_ptr<CardTheme> other) const;
    void play(State* state) override;
};

class CardGoal
  : public Card
  , std::enable_shared_from_this<CardGoal>
{
protected:
    std::vector<std::shared_ptr<CardTheme>> themes = {};
    bool isNumOfThemes = false, isNumOfCards = false;

public:
    CardGoal(std::string name,
             sf::Texture& t,
             std::vector<std::shared_ptr<CardTheme>>& themes,
             bool isNumOfThemes,
             bool isNumOfCards);
    void play(State* state) override;
    const std::vector<std::shared_ptr<CardTheme>> getThemes() const;
};

class CardAction
  : public Card
  , std::enable_shared_from_this<CardAction>
{
public:
    void (*action)(State* state);
    CardAction(std::string name, sf::Texture& t, std::string action);
    void play(State* state) override;
};

class CardRule
  : public Card
  , std::enable_shared_from_this<CardRule>
{
protected:
    RulesParams params;

public:
    CardRule(std::string name, sf::Texture& t, RulesParams& params);
    void play(State* state) override;
    const RulesParams getParams() const;
};

/** Использование слово Cards вместо объемного типа */
using Cards = std::variant<std::shared_ptr<CardAction>,
                           std::shared_ptr<CardGoal>,
                           std::shared_ptr<CardRule>,
                           std::shared_ptr<CardTheme>>;