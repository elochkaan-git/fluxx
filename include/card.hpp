#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

/*
 *  Базовый класс карточки в игре. Имеет поле для хранения спрайта,
 *  конструктор и функцию для получения спрайта.
 */
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

/* 
 *  IDEA: предлагаю для карт действий просто указывать, что это ссылка на
 *  какую-то функцию, которая будет определена где-то в другом месте.
 *  Вопрос лишь в том, как и какие аргументы передавать? Положим, у нас два игрока.
 *  Передавать в качестве аргументов ссылки на них? Ведь действия часто завязаны на
 *  игроках. Это стоит обдумать
 */
// class CardAction : protected Card
// {
// public:
//     void (*ability)();
// };

class ThemeCard : Card
{
private:

};


