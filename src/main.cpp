#include "main.hpp"

int main() {
    sf::RenderWindow window = 
        sf::RenderWindow(sf::VideoMode({1280u, 720u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    sf::Texture t("./img/default.png");

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(Card(t).getSprite());
        window.display();
    }
}
