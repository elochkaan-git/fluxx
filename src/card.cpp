#include "card.hpp"
#include "actions.hpp"
#include <memory>
#include <string>

/*
 *  МЕТОДЫ РОДИТЕЛЬСКОГО КЛАССА
 */
Card::Card(std::string name, sf::Texture& t)
  : sprite(t, { { 10, 10 }, { 50, 60 } })
  , name(name)
{
}

const sf::Sprite&
Card::getSprite() const
{
    return this->sprite;
}

const std::string&
Card::getName() const
{
    return this->name;
}

/*
 *  МЕТОДЫ КЛАССА КАРТЫ-ТЕМЫ
 */
CardTheme::CardTheme(std::string name, sf::Texture& t)
  : Card(name, t)
{
}

// void CardTheme::play(State* state)
// {
//     state
// }

bool
CardTheme::operator==(const CardTheme& other) const
{
    if (this->name == other.getName())
        return true;
    return false;
}

bool
CardTheme::operator==(const std::shared_ptr<CardTheme> other) const
{
    if (this->name == other->getName())
        return true;
    return false;
}
/*
 *  МЕТОДЫ КЛАССА КАРТЫ-ДЕЙСТВИЯ
 */
CardAction::CardAction(std::string name, sf::Texture& t, std::string action)
  : Card(name, t)
{
    this->action = actions[action];
}

// void CardAction::play(State* state)
// {
//     this->action(state);
// }


/*
 *  МЕТОДЫ КЛАССА КАРТЫ-ЦЕЛИ
 */
CardGoal::CardGoal(std::string name,
                   sf::Texture& t,
                   std::vector<std::shared_ptr<CardTheme>>& themes,
                   bool isNumOfThemes,
                   bool isNumOfCards)
  : Card(name, t)
{
    this->themes = themes;
    this->isNumOfThemes = isNumOfThemes;
    this->isNumOfCards = isNumOfCards;
}

const std::vector<std::shared_ptr<CardTheme>>
CardGoal::getThemes() const
{
    return this->themes;
}

/*
 *  МЕТОДЫ КЛАССА КАРТЫ-ПРАВИЛА
 */
CardRule::CardRule(std::string name, sf::Texture& t, RulesParams& params)
  : Card(name, t)
{
    this->params = params;
}