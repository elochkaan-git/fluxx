#include "gui.hpp"

void
updateTextSize(tgui::Gui& gui);
void
updateWindowSize(tgui::Gui& gui, int id);

const std::vector<sf::Vector2u> SUPPORTED_RESOLUTIONS = {
    { 800, 600 },  // HD
    { 1024, 768 }, // XGA
    { 1280, 720 }, // 720p
    { 1366, 768 }, // Common laptop
    { 1600, 900 }, // HD+
    { 1920, 1080 } // Full HD
                   // {2560, 1440},  // 2K
                   // {3840, 2160}   // 4K
};

bool
runExample(tgui::Gui& gui)
{
    try {
        updateTextSize(gui);
        loadMainMenu(gui);
        return true;
    } catch (const tgui::Exception& e) {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return false;
    }
}

void
loadMainMenu(tgui::Gui& gui)
{
    gui.removeAllWidgets();
    updateTextSize(gui);

    sf::Vector2f availableSize = gui.getView().getSize();

    auto picture = tgui::Picture::create("./resources/img/main_cover.png");
    picture->setPosition({ "3%", "5%" });
    sf::Vector2f pictureSize = picture->getSize();

    float scaleY = availableSize.y / pictureSize.y;
    float scale = scaleY - 0.1f;
    picture->setSize({ pictureSize.x * scale, pictureSize.y * scale });
    gui.add(picture);

    const sf::Vector2<tgui::String> buttonSize{ "22%", "8%" };

    auto settingsButton = tgui::Button::create("Settings");
    settingsButton->setSize({ buttonSize.x, buttonSize.y });
    settingsButton->setOrigin({ 0.5f, 0.5f });
    settingsButton->setPosition({ "75%", "50%" });
    gui.add(settingsButton, "Settings");

    settingsButton->onPress(&loadSettings, std::ref(gui));

    auto playButton = tgui::Button::create("Play");
    playButton->setSize({ buttonSize.x, buttonSize.y });
    playButton->setOrigin({ 0.5f, 0.5f });
    playButton->setPosition({ "Settings.x", "Settings.top - 10 - height" });
    gui.add(playButton);

    playButton->onPress(&loadGameSelect, std::ref(gui));

    auto exitButton = tgui::Button::create("Quit");
    exitButton->setSize({ buttonSize.x, buttonSize.y });
    exitButton->setOrigin({ 0.5f, 0.5f });
    exitButton->setPosition({ "Settings.x", "Settings.bottom + 10 + height" });
    gui.add(exitButton);

    exitButton->onPress([] { exit(0); });
}

void
loadGameSelect(tgui::Gui& gui)
{
    gui.removeAllWidgets();

    const sf::Vector2<tgui::String> buttonSize{ "30%", "8%" };

    auto backButton = tgui::Button::create("Back");
    backButton->setSize({ buttonSize.x, buttonSize.y });
    backButton->setOrigin({ 0.5f, 0.5f });
    backButton->setPosition({ "50%", "75%" });
    gui.add(backButton, "Back");

    backButton->onPress(&loadMainMenu, std::ref(gui));

    auto createGButton = tgui::Button::create("Create game");
    createGButton->setSize({ buttonSize.x, buttonSize.y });
    createGButton->setOrigin({ 0.5f, 0.5f });
    createGButton->setPosition({ "Back.x", "Back.top - height - 20" });
    gui.add(createGButton, "Create");

    createGButton->onClick(&loadGameCreate, std::ref(gui));

    auto joinGButton = tgui::Button::create("Join game");
    joinGButton->setSize({ buttonSize.x, buttonSize.y });
    joinGButton->setOrigin({ 0.5f, 0.5f });
    joinGButton->setPosition({ "Create.x", "Create.top - height - 20" });
    gui.add(joinGButton, "Join");

    auto ipEditBox = tgui::EditBox::create();
    ipEditBox->setSize({ buttonSize.x, buttonSize.y });
    ipEditBox->setOrigin({ 0.5f, 0.5f });
    ipEditBox->setDefaultText("Enter host's ip");
    ipEditBox->setPosition({ "Join.x", "Join.top - height - 20" });
    gui.add(ipEditBox);
}

void
loadSettings(tgui::Gui& gui)
{
    gui.removeAllWidgets();
    // updateTextSize(gui);

    const sf::Vector2<tgui::String> buttonSize{ "22%", "8%" };

    auto backButton = tgui::Button::create("Back");
    backButton->setSize({ buttonSize.x, buttonSize.y });
    backButton->setOrigin({ 0.5f, 0.5f });
    backButton->setPosition({ "50%", "80%" });
    gui.add(backButton);

    backButton->onPress(&loadMainMenu, std::ref(gui));

    auto resolutionLable = tgui::Label::create("Resolution");
    resolutionLable->setText("Resolution:");
    resolutionLable->setOrigin(0.5f, 0.5f);
    resolutionLable->setPosition({ "20%", "10%" });
    gui.add(resolutionLable, "ResolutionLable");

    auto resolutionBox = tgui::ComboBox::create();
    resolutionBox->setSize({ buttonSize.x, buttonSize.y });
    resolutionBox->setOrigin(0.5f, 0.5f);
    resolutionBox->setPosition({ "75%", "ResolutionLable.y" });

    {
        tgui::String res_string;
        for (const auto resolution : SUPPORTED_RESOLUTIONS) {
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

    resolutionBox->onItemSelect([&gui](int id) { updateWindowSize(gui, id); });
    gui.add(resolutionBox, "resolutionBox");

    auto nickLable = tgui::Label::create("Resolution");
    nickLable->setText("Change nickname:");
    nickLable->setOrigin(0.5f, 0.5f);
    nickLable->setPosition({ "20%", "20%" });
    gui.add(nickLable, "nickLable");

    auto changeNickButton = tgui::Button::create("OK");
    changeNickButton->setSize(
      { static_cast<unsigned>(gui.getView().getRect().height * 0.08f),
        buttonSize.y });
    changeNickButton->setOrigin({ 0.f, 0.5f });
    changeNickButton->setPosition({ "resolutionBox.right", "20%" });
    gui.add(changeNickButton, "changeNickButton");

    auto nickForm = tgui::EditBox::create();
    nickForm->setWidgetName("nickForm");
    nickForm->setSize({ buttonSize.x, buttonSize.y });
    nickForm->setOrigin({ 1.f, 0.5f });
    nickForm->setPosition({ "resolutionBox.right", "20%" });
    nickForm->setMaximumCharacters(12);
    gui.add(nickForm);

    changeNickButton->onClick([&gui] {
        auto editBox = gui.get<tgui::EditBox>("nickForm");
        const tgui::String& input = editBox->getText();
        if (input.length()) {
            std::ofstream nickfile;
            nickfile.open("./config/nickname.txt", std::ios::trunc);
            nickfile << input;

        } else {
            auto background = tgui::Panel::create();
            background->getRenderer()->setBackgroundColor(tgui::Color::Black);
            background->getRenderer()->setOpacity(0.5f);
            gui.add(background);

            auto message = tgui::MessageBox::create();
            message->setText("You don't entered any symbol!");
            message->addButton("Ok");
            message->setOrigin(0.5f, 0.5f);
            message->setPosition({ "50%", "50%" });
            message->getRenderer()->setTitleBarHeight(0.f);
            message->setButtonAlignment(tgui::HorizontalAlignment::Center);
            message->onButtonPress([background, message] {
                message->getParent()->remove(message->shared_from_this());
                background->getParent()->remove(background->shared_from_this());
            });
            gui.add(message);
        }
    });
}

void
updateTextSize(tgui::Gui& gui)
{
    // Update the text size of all widgets in the gui, based on the current
    // window height
    const float windowHeight = gui.getView().getRect().height;
    gui.setTextSize(static_cast<unsigned int>(0.05f * windowHeight));
}

void
updateWindowSize(tgui::Gui& gui, int id)
{
    std::ofstream settings;
    settings.open("./config/settings.txt", std::ios::trunc);
    gui.getWindow()->setSize(SUPPORTED_RESOLUTIONS[id]);
    settings << SUPPORTED_RESOLUTIONS[id].x << 'x'
             << SUPPORTED_RESOLUTIONS[id].y << '\n';
    updateTextSize(gui);
}

void
loadGameCreate(tgui::Gui& gui)
{
    gui.removeAllWidgets();

    const sf::Vector2<tgui::String> buttonSize{ "30%", "8%" };

    auto backButton = tgui::Button::create("Back");
    backButton->setSize({ buttonSize.x, buttonSize.y });
    backButton->setOrigin({ 0.5f, 0.5f });
    backButton->setPosition({ "50%", "75%" });
    gui.add(backButton, "Back");

    backButton->onPress(&loadGameSelect, std::ref(gui));

    auto createGButton = tgui::Button::create("Create lobby!");
    createGButton->setSize({ buttonSize.x, buttonSize.y });
    createGButton->setOrigin({ 0.5f, 0.5f });
    createGButton->setPosition({ "Back.x", "Back.top - height - 20" });
    gui.add(createGButton, "createB");

    auto numberOfPlayers = tgui::EditBoxSlider::create(2, 4, 2, 0, 1);
    numberOfPlayers->setTextAlignment(tgui::HorizontalAlignment::Center);
    numberOfPlayers->setSize({ buttonSize.x, buttonSize.y });
    numberOfPlayers->setOrigin(0.5f, 0.5f);
    numberOfPlayers->setPosition({ "createB.x", "createB.top - height - 20" });
    gui.add(numberOfPlayers, "Slider");

    auto label = tgui::Label::create("numofp");
    label->setText("Number of players:");
    label->setOrigin(0.5f, 0.5f);
    label->setPosition({ "Slider.x", "Slider.top - height - 20" });
    gui.add(label);

    createGButton->onClick([&gui] {
        auto slider = gui.get<tgui::EditBoxSlider>("Slider");
        float value = slider->getValue();
        loadGame(gui, static_cast<int>(value));
    });
}
