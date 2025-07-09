#include "main.hpp"
#include "core.hpp"


void update(unsigned short int numOfPlayers)
{
    std::vector<Player*> players(numOfPlayers);
    for(Player* p : players) p = new Player();
    State state(players);


    for(Player* p : players) delete p;
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Fluxx", sf::Style::Titlebar | sf::Style::Close);
    tgui::Gui gui{window};
    if (runExample(std::ref(gui)))
        gui.mainLoop(sf::Color::Black);
}
