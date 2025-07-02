#include "card.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

/*
 *  Размеры и текстура взяты просто для тестирования и примера
 */
Card::Card(sf::Texture& t) 
    : sprite(t, {{10u, 50u}, {60u, 100u}}) {}

sf::Sprite Card::getSprite() {
    return this->sprite;
}