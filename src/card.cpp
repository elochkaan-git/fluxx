#include "card.hpp"
#include "actions.hpp"

Card::Card(sf::Texture& t) :
    sprite(t, {{10, 10}, {50, 60}}) {}

sf::Sprite Card::getSprite() const {
    return this->sprite;
}

CardAction::CardAction(sf::Texture& t, std::string action) : Card(t) {
    this->action = actions[action];
}

CardTheme::CardTheme(sf::Texture& t, std::string theme) : Card(t) {
    this->theme = theme;
}

CardGoal::CardGoal(sf::Texture& t, std::string goal, 
    std::vector<std::pair<std::string, std::string>>& themes, 
    bool isNumOfThemes, bool isNumOfCards) : Card(t)
{
    this->goal = goal;
    this->themes = themes;
    this->isNumOfThemes = isNumOfThemes;
    this->isNumOfCards = isNumOfCards;
}

CardRule::CardRule(sf::Texture& t, RulesParams& params) : Card(t) {
    this->params = params;
}