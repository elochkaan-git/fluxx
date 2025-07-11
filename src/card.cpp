#include "card.hpp"
#include "actions.hpp"

Card::Card(std::string name, sf::Texture& t) :
    sprite(t, {{10, 10}, {50, 60}}),
    name(name) {}

sf::Sprite Card::getSprite() const {
    return this->sprite;
}

CardAction::CardAction(std::string name, sf::Texture& t, std::string action) : Card(name, t) {
    this->action = actions[action];
}

CardTheme::CardTheme(std::string name, sf::Texture& t, std::string theme) : Card(name, t) {}

CardGoal::CardGoal(std::string name, sf::Texture& t, std::vector<std::string>& themes, 
    bool isNumOfThemes, bool isNumOfCards) : Card(name, t)
{
    this->themes = themes;
    this->isNumOfThemes = isNumOfThemes;
    this->isNumOfCards = isNumOfCards;
}

CardRule::CardRule(std::string name, sf::Texture& t, RulesParams& params) : Card(name, t) {
    this->params = params;
}