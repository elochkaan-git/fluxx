#include "main.hpp"
#include "core.hpp"

bool runExample(tgui::BackendGui& gui)
{
    try
    {
        loadMainMenu(gui);
        return true;
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return false;
    }
}

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


void loadMainMenu(tgui::BackendGui& gui)
{
    gui.removeAllWidgets();
    
    tgui::Theme theme{"./themes/Black.txt"};

    auto picture = tgui::Picture::create("../../resources/img/main_cover.png");
    picture->setPosition({"3%", 30});
    gui.add(picture);


    auto settingsButton = tgui::Button::create("Settings");
    settingsButton->setRenderer(theme.getRenderer("Button"));
    settingsButton->setSize({200, 40});
    settingsButton->setOrigin({0.5f, 0.5f});
    settingsButton->setPosition({"80%", "50%"});
    gui.add(settingsButton, "Settings");

    settingsButton->onPress(&loadGameSelect, std::ref(gui));

    auto playButton = tgui::Button::create("Play");
    playButton->setRenderer(theme.getRenderer("Button"));
    playButton->setSize({200, 40});
    playButton->setOrigin({0.5f, 0.5f});
    playButton->setPosition({"Settings.x", "Settings.top - 10 - height"});
    gui.add(playButton);

    playButton->onPress(&loadGameSelect, std::ref(gui));

    auto exitButton = tgui::Button::create("Quit");
    exitButton->setRenderer(theme.getRenderer("Button"));
    exitButton->setSize({200, 40});
    exitButton->setOrigin({0.5f, 0.5f});
    exitButton->setPosition({"Settings.x", "Settings.bottom + 10 + height"});
    gui.add(exitButton);

    exitButton->onPress([]{ exit(0); });

}

void loadGameSelect(tgui::BackendGui& gui)
{
    gui.removeAllWidgets();

    tgui::Theme theme{"./themes/Black.txt"};

    auto backButton = tgui::Button::create("Back");
    backButton->setRenderer(theme.getRenderer("Button"));
    backButton->setSize({200, 40});
    backButton->setOrigin({0.5f, 0.5f});
    backButton->setPosition({"50%", "50%"});
    gui.add(backButton);

    backButton->onPress(&loadMainMenu, std::ref(gui));
}