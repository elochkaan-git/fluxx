#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <utility>
#include <vector>


class State;

class Card
{
protected:
    sf::Sprite sprite;
    std::string description = "Place holder";
    std::string name = "Default";

public:
    Card(sf::Texture& t);
    sf::Sprite getSprite() const;
    const std::string& getDescription() const;
    const std::string& getName() const;
    
};


class CardAction : protected Card
{
public:
    void (*action)(State* state);
    CardAction(sf::Texture& t, std::string);
};


class CardTheme : protected Card
{
protected:
    std::string theme = "default";

public:
    CardTheme(sf::Texture& t, std::string theme);
};


class CardGoal : protected Card
{
protected:
    std::string goal = "default";
    std::vector<std::pair<std::string, std::string>> themes = {{"", ""}};
    bool isNumOfThemes = false, isNumOfCards = false;

public:
    CardGoal(sf::Texture& t, 
             std::string goal, 
             std::vector<std::pair<std::string, std::string>>& themes,
             bool isNumOfThemes, bool isNumOfCards);
};


struct RulesParams
{
    short int handLimit = -1, 
        themeLimit = -1, play = -1, take = -1;
    bool castling = false, blindGame = false, 
        duplet = false, withoutHands = false, enough = false,
        rich = false, random = false, poverty = false,
        utilize = false, dance = false, spinAndTurn = false;
};

class CardRule : protected Card
{
protected:
    RulesParams params;

public:
    CardRule(sf::Texture& t, RulesParams& params);
};
