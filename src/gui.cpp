#include "gui.hpp"

void updateTextSize(tgui::Gui& gui);
void updateWindowSize(tgui::Gui& gui, int id);

const std::vector<sf::Vector2u> SUPPORTED_RESOLUTIONS = {
    {800, 600},    // HD
    {1024, 768},   // XGA
    {1280, 720},   // 720p
    {1366, 768},   // Common laptop
    {1600, 900},   // HD+
    {1920, 1080}   // Full HD
    // {2560, 1440},  // 2K
    // {3840, 2160}   // 4K
};

bool runExample(tgui::Gui& gui)
{
    try
    {
        updateTextSize(gui);
        loadMainMenu(gui);
        return true;
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return false;
    }
}

void loadMainMenu(tgui::Gui& gui)
{
    gui.removeAllWidgets();
    updateTextSize(gui);
    
    tgui::Theme theme{"./bin/themes/Black.txt"};
    sf::Vector2f availableSize = gui.getView().getSize();

    auto picture = tgui::Picture::create("./resources/img/main_cover.png");
    picture->setPosition({"3%", "5%"});
    sf::Vector2f pictureSize = picture->getSize();
    

    float scaleY = availableSize.y / pictureSize.y;
    float scale = scaleY - 0.1f;
    picture->setSize({pictureSize.x * scale, pictureSize.y * scale});
    gui.add(picture);

    const sf::Vector2<tgui::String> buttonSize{"22%", "8%"};

    auto settingsButton = tgui::Button::create("Settings");
    settingsButton->setRenderer(theme.getRenderer("Button"));
    settingsButton->setSize({buttonSize.x, buttonSize.y});
    settingsButton->setOrigin({0.5f, 0.5f});
    settingsButton->setPosition({"75%", "50%"});
    gui.add(settingsButton, "Settings");

    settingsButton->onPress(&loadSettings, std::ref(gui));

    auto playButton = tgui::Button::create("Play");
    playButton->setRenderer(theme.getRenderer("Button"));
    playButton->setSize({buttonSize.x, buttonSize.y});
    playButton->setOrigin({0.5f, 0.5f});
    playButton->setPosition({"Settings.x", "Settings.top - 10 - height"});
    gui.add(playButton);

    playButton->onPress(&loadGameSelect, std::ref(gui));

    auto exitButton = tgui::Button::create("Quit");
    exitButton->setRenderer(theme.getRenderer("Button"));
    exitButton->setSize({buttonSize.x, buttonSize.y});
    exitButton->setOrigin({0.5f, 0.5f});
    exitButton->setPosition({"Settings.x", "Settings.bottom + 10 + height"});
    gui.add(exitButton);

    exitButton->onPress([]{ exit(0); });

}

void loadGameSelect(tgui::Gui& gui)
{
    gui.removeAllWidgets();
    updateTextSize(gui);

    tgui::Theme theme{"./bin/themes/Black.txt"};

    const sf::Vector2<tgui::String> buttonSize{"22%", "8%"};

    auto backButton = tgui::Button::create("Back");
    backButton->setRenderer(theme.getRenderer("Button"));
    backButton->setSize({buttonSize.x, buttonSize.y});
    // backButton->setTextSize(text_s);
    backButton->setOrigin({0.5f, 0.5f});
    backButton->setPosition({"50%", "50%"});
    gui.add(backButton);

    backButton->onPress(&loadMainMenu, std::ref(gui));
}

void loadSettings(tgui::Gui& gui)
{
    gui.removeAllWidgets();
    // updateTextSize(gui);

    tgui::Theme theme{"./bin/themes/Black.txt"};
    const sf::Vector2<tgui::String> buttonSize{"22%", "8%"};

    auto backButton = tgui::Button::create("Back");
    backButton->setRenderer(theme.getRenderer("Button"));
    backButton->setSize({buttonSize.x, buttonSize.y});
    // backButton->setTextSize(text_s);
    backButton->setOrigin({0.5f, 0.5f});
    backButton->setPosition({"50%", "80%"});
    gui.add(backButton);

    backButton->onPress(&loadMainMenu, std::ref(gui));

    auto resolutionLable = tgui::Label::create("Resolution");
    resolutionLable->setRenderer(theme.getRenderer("Label"));
    resolutionLable->setText("Resolution:");
    resolutionLable->setOrigin(0.5f, 0.5f);
    resolutionLable->setPosition({"20%","10%"});
    gui.add(resolutionLable, "ResolutionLable");

    auto resolutionBox = tgui::ComboBox::create();
    resolutionBox->setRenderer(theme.getRenderer("ComboBox"));
    resolutionBox->setSize({buttonSize.x, buttonSize.y});
    resolutionBox->setOrigin(0.5f, 0.5f);
    resolutionBox->setPosition({"75%", "ResolutionLable.y"});
    
    {
        tgui::String res_string;
        for(const auto resolution: SUPPORTED_RESOLUTIONS){
            res_string = std::to_string(resolution.x);
            res_string.append("x");
            res_string.append(std::to_string(resolution.y));
            resolutionBox->addItem(res_string);
        }
    }
    std::ifstream settings_f;
    settings_f.open("./config/settings.txt");
    tgui::String buf;
    settings_f >> buf;
    settings_f.close();
    resolutionBox->setSelectedItem(buf);

    resolutionBox->onItemSelect([&gui](int id) {
        updateWindowSize(gui, id);
    });
    gui.add(resolutionBox);

}

void updateTextSize(tgui::Gui& gui)
{
    // Update the text size of all widgets in the gui, based on the current window height
    const float windowHeight = gui.getView().getRect().height;
    gui.setTextSize(static_cast<unsigned int>(0.05f * windowHeight));
}

void updateWindowSize(tgui::Gui& gui, int id)
{
    std::ofstream settings;
    settings.open("./config/settings.txt",std::ios::trunc);
    gui.getWindow()->setSize(SUPPORTED_RESOLUTIONS[id]);
    settings << SUPPORTED_RESOLUTIONS[id].x << 'x' << SUPPORTED_RESOLUTIONS[id].y << '\n';
    updateTextSize(gui);
}