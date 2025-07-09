#include "main.hpp"
#include "core.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Fluxx", sf::Style::Titlebar | sf::Style::Close);
    tgui::Gui gui{window};
    if (runExample(std::ref(gui)))
        gui.mainLoop(sf::Color::Black);
}
