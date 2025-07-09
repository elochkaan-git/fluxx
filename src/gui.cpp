#include "gui.hpp"

void updateTextSize(tgui::Gui& gui);
void updateWindowSize(tgui::Gui& gui, int id);

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
    
    tgui::Theme theme{"./build/bin/themes/Black.txt"};

    auto picture = tgui::Picture::create("./resources/img/main_cover.png");
    picture->setPosition({"3%", 30});
    gui.add(picture);

    unsigned int standart_h = 60, standart_w = 200, text_s=30;

    auto settingsButton = tgui::Button::create("Settings");
    settingsButton->setRenderer(theme.getRenderer("Button"));
    settingsButton->setSize({standart_w, standart_h});
    settingsButton->setTextSize(text_s);
    settingsButton->setOrigin({0.5f, 0.5f});
    settingsButton->setPosition({"80%", "50%"});
    gui.add(settingsButton, "Settings");

    settingsButton->onPress(&loadSettings, std::ref(gui));

    auto playButton = tgui::Button::create("Play");
    playButton->setRenderer(theme.getRenderer("Button"));
    playButton->setSize({standart_w, standart_h});
    playButton->setTextSize(text_s);
    playButton->setOrigin({0.5f, 0.5f});
    playButton->setPosition({"Settings.x", "Settings.top - 10 - height"});
    gui.add(playButton);

    playButton->onPress(&loadGameSelect, std::ref(gui));

    auto exitButton = tgui::Button::create("Quit");
    exitButton->setRenderer(theme.getRenderer("Button"));
    exitButton->setSize({standart_w, standart_h});
    exitButton->setTextSize(text_s);
    exitButton->setOrigin({0.5f, 0.5f});
    exitButton->setPosition({"Settings.x", "Settings.bottom + 10 + height"});
    gui.add(exitButton);

    exitButton->onPress([]{ exit(0); });

}

void loadGameSelect(tgui::Gui& gui)
{
    gui.removeAllWidgets();
    updateTextSize(gui);

    tgui::Theme theme{"./build/bin/themes/Black.txt"};

    unsigned int standart_h = 60, standart_w = 200, text_s=30;

    auto backButton = tgui::Button::create("Back");
    backButton->setRenderer(theme.getRenderer("Button"));
    backButton->setSize({standart_w, standart_h});
    // backButton->setTextSize(text_s);
    backButton->setOrigin({0.5f, 0.5f});
    backButton->setPosition({"50%", "50%"});
    gui.add(backButton);

    backButton->onPress(&loadMainMenu, std::ref(gui));
}

void loadSettings(tgui::Gui& gui)
{
    gui.removeAllWidgets();
    updateTextSize(gui);

    tgui::Theme theme{"./build/bin/themes/Black.txt"};
    unsigned int standart_h = 40, standart_w = 200, text_s=25;

    auto backButton = tgui::Button::create("Back");
    backButton->setRenderer(theme.getRenderer("Button"));
    backButton->setSize({standart_w, standart_h});
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
    // resolutionLable->setTextSize(text_s);
    gui.add(resolutionLable, "ResolutionLable");

    auto resolutionBox = tgui::ComboBox::create();
    resolutionBox->setRenderer(theme.getRenderer("ComboBox"));
    resolutionBox->setSize(standart_w, standart_h);
    resolutionBox->setOrigin(0.5f, 0.5f);
    resolutionBox->setPosition({"75%", "ResolutionLable.y"});
    
    resolutionBox->addItem("1920x1080");
    resolutionBox->addItem("1680x1050");
    resolutionBox->addItem("1600x900");
    resolutionBox->addItem("1536x864");
    resolutionBox->addItem("1440x900");
    resolutionBox->addItem("1366x768");
    resolutionBox->addItem("1280x1024");
    resolutionBox->addItem("1280x800");
    resolutionBox->addItem("1024x768");
    resolutionBox->addItem("800x600");

    std::ifstream settings_f;
    settings_f.open("settings.txt");
    tgui::String buf;
    settings_f >> buf;
    std::cout << buf;
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
    settings.open("settings.txt",std::ios::trunc);
    switch (id)
    {
    case 0:
        gui.getWindow()->setSize({1920, 1080});
        break;
    case 1:
        gui.getWindow()->setSize({1680, 1050});
        break;
    case 2:
        gui.getWindow()->setSize({1600, 900});
        break;
    case 3:
        gui.getWindow()->setSize({1536, 864});
        break;
    case 4:
        gui.getWindow()->setSize({1440, 900});
        break;
    case 5:
        gui.getWindow()->setSize({1366, 768});
        break;
    case 6:
        gui.getWindow()->setSize({1280, 1024});
        break;
    case 7:
        gui.getWindow()->setSize({1280, 800});
        break;
    case 8:
        gui.getWindow()->setSize({1024, 768});
        break;
    case 9:
        gui.getWindow()->setSize({800, 600});
        break;
    }
    auto size = gui.getWindow()->getSize();
    settings << size.x << 'x' << size.y << '\n';
    updateTextSize(gui);
    loadSettings(gui);
}