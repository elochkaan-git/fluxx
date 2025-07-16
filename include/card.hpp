#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include <vector>
#include <variant>


class State;

class Card
{
protected:
    sf::Sprite sprite;
    std::string name = "Default";

public:
    Card(std::string name, sf::Texture& t);
    const sf::Sprite& getSprite() const;
    const std::string& getName() const;
    // virtual void play(State* state) = 0;
};


class CardTheme : public Card
{
public:
    CardTheme(std::string name, sf::Texture& t, std::string theme);
    bool operator ==(const CardTheme& other) const;
    bool operator ==(const std::shared_ptr<CardTheme> other) const;
    // void play(State* state) override;
};


class CardAction : public Card
{
public:
    void (*action)(State* state);
    CardAction(std::string name, sf::Texture& t, std::string action);
    // void play(State* state) override;
};


class CardGoal : public Card
{
protected:
    std::vector<std::shared_ptr<CardTheme>> themes = {};
    bool isNumOfThemes = false, isNumOfCards = false;

public:
    CardGoal(std::string name, sf::Texture& t, std::vector<std::shared_ptr<CardTheme>>& themes,
             bool isNumOfThemes, bool isNumOfCards);
    // void play(State* state) override;
    const std::vector<std::shared_ptr<CardTheme>> getThemes() const;
};


struct RulesParams
{
    short int handLimit = -1, 
        themeLimit = -1, play = -1, take = -1;
    bool castling = false, blindGame = false, 
        duplet = false, withoutHands = false, enough = false,
        rich = false, random = false, poverty = false,
        utilize = false, dance = false, spinAndTurn = false,
        inflation = false;
};

class CardRule : public Card
{
protected:
    RulesParams params;

public:
    CardRule(std::string name, sf::Texture& t, RulesParams& params);
    // void play(State* state) override;
};

using Cards = std::variant<std::shared_ptr<CardAction>, std::shared_ptr<CardGoal>, std::shared_ptr<CardRule>, std::shared_ptr<CardTheme>>;