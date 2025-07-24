#include "gamegui.hpp"
#include "TGUI/Texture.hpp"
#include "card.hpp"


void
loadCardsToHand(tgui::Gui& gui);

void
loadCardsToTable(tgui::Gui& gui);

void
loadCardsToGoal(tgui::Gui&gui);

void
loadCardsToRules(tgui::Gui&gui);

inline unsigned
returnSelectedId(tgui::Gui& gui){
    auto card = gui.get<tgui::Picture>("Selected");
    if(card){
        return card->getUserData<unsigned>();
    }
    return 0;
}

void
makeGlow(tgui::Picture::Ptr card)
{
    auto glowTexture = card->getRenderer()->getTexture();
    glowTexture.setColor(tgui::Color::Yellow);
    card->getRenderer()->setTexture(glowTexture);
}

void
makeNormal(tgui::Picture::Ptr card)
{
    if (card->getWidgetName() != "Selected") {
        auto glowTexture = card->getRenderer()->getTexture();
        glowTexture.setColor(tgui::Color::White);
        card->getRenderer()->setTexture(glowTexture);
    }
}

void
selectCard(tgui::Gui& gui, tgui::Picture::Ptr card)
{
    auto last =  gui.get<tgui::Picture>("Selected");
    if (last) {
        last->setWidgetName(std::to_string(last->getUserData<unsigned>()));
        makeNormal(last);
        last->setIgnoreMouseEvents(false);
    }
    card->setWidgetName("Selected");
    auto glowTexture = card->getRenderer()->getTexture();
    glowTexture.setColor(tgui::Color::Green);
    card->getRenderer()->setTexture(glowTexture);
    card->setIgnoreMouseEvents(true);
}

auto
createCard(const Cards* Card, tgui::Gui& gui)
{
    auto card = tgui::Picture::create(Card->getTexture());
    unsigned id = Card->getId();
    card->setUserData(id);
    card->setWidgetName(std::to_string(id));
    auto sizeOfCard = card->getSize();
    auto resolution = gui.getWindow()->getSize();
    // card->setSize("15%", "15%");
    card->onMouseEnter(&makeGlow, card);
    card->onMouseLeave(&makeNormal, card);
    card->onClick(&selectCard, std::ref(gui), card);

    float scaleY = resolution.y / sizeOfCard.y;
    float scale = scaleY * 0.15f;
    card->setSize({ sizeOfCard.x * scale, sizeOfCard.y * scale });
    return card;
}

void
showCardsButtonOnToggle(tgui::Gui& gui, bool isDown)
{
    auto hand = gui.get<tgui::ScrollablePanel>("Hand");
    if (isDown) {
        hand->showWithEffect(tgui::ShowEffectType::SlideFromBottom, 300);
    } else {
        hand->hideWithEffect(tgui::ShowEffectType::SlideToBottom, 300);
    }
}

void test(tgui::Gui& gui){
    State& state = State::getInstance();
    unsigned selectedId = returnSelectedId(gui);
    if(selectedId){
        /*
            1)Play
            2)define type
            3)delete from hand
        */
       Cards* selectedCard = state.getCardById(selectedId);
       gui.remove(gui.get<tgui::Picture>("Selected"));
       selectedCard->play(&state);
       if(state.checkWinner()){
        exit(0);
       }
       
       switch (selectedCard->getType())
       {
       case Type::THEME:
        loadCardsToTable(gui);
        break;
       case Type::GOAL:
        loadCardsToGoal(gui);
        break;
       case::Type::RULE:
        loadCardsToRules(gui);
        break;
       }
       state.nextMove();
       loadCardsToHand(gui);
       state.currentPlayer()->takeCards(state);
    }
}



////////////////////////////////////////////////////////////////////////////

void
initfunctionalPanel(tgui::Gui& gui)
{
    auto functionalPanel = tgui::Panel::create();
    functionalPanel->setWidth("15%");
    functionalPanel->getRenderer()->setBackgroundColor("rgb(80,  80,  80)");
    functionalPanel->setAutoLayout(tgui::AutoLayout::Leftmost);
    functionalPanel->getRenderer()->setPadding({ "3%" });

    gui.add(functionalPanel);

    const sf::Vector2<tgui::String> buttonSize{ "30%", "8%" };

    auto backButton = tgui::Button::create("Exit");
    functionalPanel->add(backButton);
    backButton->setAutoLayout(tgui::AutoLayout::Top);
    backButton->setHeight(buttonSize.y);
    backButton->onClick(&loadMainMenu, std::ref(gui));

    auto showCardsButton = tgui::ToggleButton::create("Show");
    functionalPanel->add(showCardsButton);
    showCardsButton->setAutoLayout(tgui::AutoLayout::Bottom);
    showCardsButton->setHeight(buttonSize.y);
    showCardsButton->onToggle([showCardsButton, &gui](bool isDown) {
        if (isDown) {
            showCardsButton->setText("Hide");

        } else {
            showCardsButton->setText("Show");
        }
        showCardsButtonOnToggle(gui, isDown);
    });

    auto confirmButton = tgui::Button::create("Confirm");
    functionalPanel->add(confirmButton);
    confirmButton->setAutoLayout(tgui::AutoLayout::Bottom);
    confirmButton->setHeight(buttonSize.y);
    confirmButton->onClick(&test, std::ref(gui));

    auto startGameButton = tgui::Button::create("Start\ngame");
    functionalPanel->add(startGameButton);
    startGameButton->setSize({ "100%", "16%" });
    startGameButton->setOrigin(0.5f, 0.5f);
    startGameButton->setPosition({ "50%", "50%" });

    startGameButton->onClick(&loadMainMenu, std::ref(gui));
}

void
initPlayersBoardCards(tgui::Gui& gui, int numberOfPlayers)
{
    auto firstPlayerCards = tgui::ScrollablePanel::create();
    firstPlayerCards->setWidgetName("1cards");
    firstPlayerCards->getVerticalScrollbar()->setPolicy(
      tgui::Scrollbar::Policy::Never);
    firstPlayerCards->getRenderer()->setBackgroundColor("rgb(120, 141, 233)");

    auto fourthPlayerCards = tgui::ScrollablePanel::create();
    fourthPlayerCards->setWidgetName("4cards");
    fourthPlayerCards->getVerticalScrollbar()->setPolicy(
      tgui::Scrollbar::Policy::Never);
    fourthPlayerCards->getRenderer()->setBackgroundColor("rgb(120, 233, 126)");

    auto splitBottom = tgui::SplitContainer::create();
    splitBottom->setWidgetName("splitB");
    splitBottom->setHeight("20%");
    splitBottom->setSplitterOffset("100%");
    splitBottom->setAutoLayout(tgui::AutoLayout::Bottom);
    splitBottom->add(firstPlayerCards, "firstPlayerCards");

    gui.add(splitBottom, "splitBottom");

    auto secondPlayerCards = tgui::ScrollablePanel::create();
    secondPlayerCards->setWidgetName("2cards");
    secondPlayerCards->getVerticalScrollbar()->setPolicy(
      tgui::Scrollbar::Policy::Never);
    secondPlayerCards->getRenderer()->setBackgroundColor("rgb(233, 156, 120)");

    auto thirdPlayerCards = tgui::ScrollablePanel::create();
    thirdPlayerCards->setWidgetName("3cards");
    thirdPlayerCards->getVerticalScrollbar()->setPolicy(
      tgui::Scrollbar::Policy::Never);
    thirdPlayerCards->getRenderer()->setBackgroundColor("rgb(207, 120, 233)");

    auto splitTop = tgui::SplitContainer::create();
    splitTop->setHeight("20%");
    splitTop->setSplitterOffset("100%");
    splitTop->setAutoLayout(tgui::AutoLayout::Top);
    splitTop->add(secondPlayerCards, "secondPlayerCards");

    gui.add(splitTop, "splitTop");

    switch (numberOfPlayers) {
        case 4:
            splitBottom->add(fourthPlayerCards, "fourthPlayerCards");
            splitBottom->setSplitterOffset("50%");
        case 3:
            splitTop->add(thirdPlayerCards, "thirdPlayerCards");
            splitTop->setSplitterOffset("50%");
            break;
    }
}

void
initGoalPanel(tgui::Gui& gui)
{
    auto goalPanel = tgui::HorizontalWrap::create();
    goalPanel->setWidgetName("Goals");
    goalPanel->setAutoLayout(tgui::AutoLayout::Left);
    goalPanel->setWidth({ "20%" });
    goalPanel->getRenderer()->setPadding(
      { 5 }); // Keep 5px on all sides as empty space
    goalPanel->getRenderer()->setSpaceBetweenWidgets(
      10); // Put a 10px gap beside and below widgets
    gui.add(goalPanel);
}

void
initRulePanel(tgui::Gui& gui)
{
    auto rulePanel = tgui::HorizontalWrap::create();
    rulePanel->setWidgetName("Rules");
    rulePanel->setAutoLayout(tgui::AutoLayout::Right);
    rulePanel->setWidth({ "20%" });
    rulePanel->getRenderer()->setPadding(
      { 5 }); // Keep 5px on all sides as empty space
    rulePanel->getRenderer()->setSpaceBetweenWidgets(
      10); // Put a 10px gap beside and below widgets
    gui.add(rulePanel);
}

void
initPlayerHand(tgui::Gui& gui)
{
    auto hand = tgui::ScrollablePanel::create({ "75%", "50%" });
    hand->setWidgetName("Hand");
    hand->getVerticalScrollbar()->setPolicy(tgui::Scrollbar::Policy::Never);
    hand->getRenderer()->setBackgroundColor("rgb(94, 96, 104)");
    hand->getRenderer()->setBorders(6);
    hand->getRenderer()->setBorderColor("rgb(48, 47, 47)");
    hand->setOrigin(0.5f, 1.f);
    hand->setPosition({ "57.5%", "100%" });

    // TestBlock
    //  tgui::String defaultTexure = "./resources/img/default.png";
    //  for(int i = 0; i < 10; i++){
    //    auto Test = createCard(defaultTexure, gui);
    //    hand->add(Test);
    //    // Test->setScale(0.3f);
    //    Test->setPosition(i*80+4, 4);
    //  }
    gui.add(hand);
    hand->setVisible(false);
}

void
initNicknames(tgui::Gui& gui, int numberOfPlayers)
{

    /*
        Adding NickNamePlaceHolders
    */

    auto firstPlayerNick = tgui::Label::create("PlaceHolder1");
    firstPlayerNick->setWidgetName("1name");
    firstPlayerNick->getRenderer()->setTextSize(
      static_cast<unsigned>(gui.getView().getRect().height * 0.03f));
    firstPlayerNick->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
    firstPlayerNick->setVerticalAlignment(tgui::VerticalAlignment::Center);
    firstPlayerNick->getRenderer()->setBackgroundColor("rgb(110, 110, 110)");
    firstPlayerNick->getRenderer()->setBorders(3);
    firstPlayerNick->setOrigin(0.5f, 1.f);
    firstPlayerNick->setPosition({ "57.5%", "splitBottom.top" });

    auto nickRender = firstPlayerNick->getSharedRenderer();
    auto secondPlayerNick = tgui::Label::create("PlaceHolder2");
    secondPlayerNick->setWidgetName("2name");
    secondPlayerNick->setRenderer(nickRender->getData());
    firstPlayerNick->setRenderer(nickRender->getData());
    secondPlayerNick->setOrigin(0.5f, 0.f);
    secondPlayerNick->setPosition({ "57.5%", "splitTop.bottom" });
    gui.add(firstPlayerNick);
    gui.add(secondPlayerNick);

    auto fourthPlayerNick = tgui::Label::create("PlaceHolder4");
    fourthPlayerNick->setWidgetName("4name");
    auto thirdPlayerNick = tgui::Label::create("PlaceHolder3");
    thirdPlayerNick->setWidgetName("3name");
    switch (numberOfPlayers) {
        case 4:
            firstPlayerNick->setPosition({ "36.25%", "splitBottom.top" });
            fourthPlayerNick->setRenderer(nickRender->getData());
            fourthPlayerNick->setOrigin(0.5f, 1.f);
            fourthPlayerNick->setPosition({ "82.25%", "splitBottom.top" });
            gui.add(fourthPlayerNick);
        case 3:
            secondPlayerNick->setPosition({ "36.25%", "splitTop.bottom" });
            thirdPlayerNick->setRenderer(nickRender->getData());
            thirdPlayerNick->setOrigin(0.5f, 0.f);
            thirdPlayerNick->setPosition({ "82.25%", "splitTop.bottom" });
            gui.add(thirdPlayerNick);
            break;
    }
}

void
initCentralPanel(tgui::Gui& gui)
{
    auto centralPanel = tgui::Panel::create();
    // centralPanel->getRenderer()->setSpaceBetweenWidgets(10.f);
    centralPanel->setAutoLayout(tgui::AutoLayout::Fill);
    // centralPanel->setWidth({"40%"});

    auto StateLabel = tgui::Label::create("Main label");
    StateLabel->setText("Waiting for players");
    centralPanel->add(StateLabel);
    StateLabel->setPosition({ "10%", "50%" });
    gui.add(centralPanel);
}

void
loadCardsToGoal(tgui::Gui&gui){
    auto goals = gui.get<tgui::HorizontalWrap>("Goals");
    goals->removeAllWidgets();
    unsigned howManyCards = 0;
    float scale = 2.f;
    State& state = State::getInstance();
    auto handId = state.getGoalsId();
    for(const auto cardId: handId){
        Cards* card = state.getCardById(cardId);
        auto CardWidget = createCard(card, gui);
        goals->add(CardWidget);
        CardWidget->setScale(scale);
        CardWidget->setPosition(scale*howManyCards*(CardWidget->getSize().x+5)+4, 4);
        howManyCards++;
    }
    goals->setUserData(howManyCards);
}

void
loadCardsToRules(tgui::Gui&gui){
    auto rules = gui.get<tgui::HorizontalWrap>("Rules");
    if(rules){
        rules->removeAllWidgets();
        unsigned howManyCards = 0;
        float scale = 1.f;
        State& state = State::getInstance();
        auto handId = state.getRulesId();
        for(const auto cardId: handId){
            Cards* card = state.getCardById(cardId);
            auto CardWidget = createCard(card, gui);
            rules->add(CardWidget);
            CardWidget->setScale(scale);
            CardWidget->setPosition(scale*howManyCards*(CardWidget->getSize().x+5)+4, 4);
            howManyCards++;
        }
        rules->setUserData(howManyCards);
    }
}

void
loadGame(tgui::Gui& gui, int numberOfPlayers)
{
    gui.removeAllWidgets();

    /*
        Initialization state
    */
    State& state = State::getInstance();
    state.initPlayers(numberOfPlayers);
    for (Player*& p : state.getPlayers())
        p->takeCards(state);

    
    
    /*
    Initialization main panels for main game window
    */
   initPlayersBoardCards(gui, numberOfPlayers); 
    initPlayerHand(gui);
    loadCardsToHand(gui);
    
    initGoalPanel(gui);
    initRulePanel(gui);
    initCentralPanel(gui);
    initNicknames(gui, numberOfPlayers);

    initfunctionalPanel(gui);
    gui.moveWidgetToFront(gui.get<tgui::ScrollablePanel>("Hand"));

}

void
loadCardsToHand(tgui::Gui& gui){
    auto hand = gui.get<tgui::ScrollablePanel>("Hand");
    hand->removeAllWidgets();
    unsigned howManyCards = 0;
    float scale = 3.f;
    State& state = State::getInstance();
    auto handId = state.currentPlayer()->getHand();
    for(const auto cardId: handId){
        Cards* card = state.getCardById(cardId);
        auto CardWidget = createCard(card, gui);
        hand->add(CardWidget);
        CardWidget->setScale(scale);
        CardWidget->setPosition(scale*howManyCards*(CardWidget->getSize().x+5)+4, 4);
        howManyCards++;
    }
    hand->setUserData(howManyCards);
}

void
loadCardsToTable(tgui::Gui& gui){
    State& state = State::getInstance();
    unsigned howManyPlayers = state.getPlayers().size();

    for(int i = 0; i<howManyPlayers; i++){
        tgui::String nameOfCards;
        if(i == 0){
            nameOfCards="firstPlayerCards";
        }else
        if(i == 1){
            nameOfCards="secondPlayerCards";
        }else
        if(i == 2){
            nameOfCards="thirdPlayerCards";
        }else{
            nameOfCards="fourthPlayerCards";
        }
        auto cardsTable = gui.get<tgui::ScrollablePanel>(nameOfCards);

        if(cardsTable){
            cardsTable->removeAllWidgets();
            unsigned howManyCards = 0;
            float scale = 1.5f;
            auto handId = state.getPlayers()[i]->getThemes();
            for(const auto cardId: handId){
                Cards* card = state.getCardById(cardId);
                auto CardWidget = createCard(card, gui);
                cardsTable->add(CardWidget);
                CardWidget->setScale(scale);
                CardWidget->setPosition(scale*howManyCards*(CardWidget->getSize().x+5)+4, 4);
                howManyCards++;
            }
            cardsTable->setUserData(howManyCards);
        }else{
            std::cout << "Cards on table widget not found!\n";
        }
    }
}


// void initOthersHands(tgui::Gui& gui, int numberOfPlayers){
//     auto hands = tgui::TabContainer::create({ "75%", "25%" });
//     hands->setOrigin(0.5f, 0.f);
//     hands->setPosition({"57.5%", 0});
//     // hands->setTabsHeight({"5%"});
//     hands->getTabsRenderer()->setTextSize(static_cast<unsigned>(gui.getView().getRect().height*0.03f));
//     hands->setWidgetName("OthersHand");
//     hands->setTabAlignment(tgui::TabContainer::TabAlign::Bottom);
//     for(int i = 2; i<=numberOfPlayers;i++){
//         // auto bgColor =
//         gui.get<tgui::ScrollablePanel>(std::to_string(i)+"cards")->getRenderer()->getBackgroundColor();
//         auto tab =
//         hands->addTab(gui.get<tgui::Label>(std::to_string(i)+"name")->getText());
//         // std::cout << hands->getPanelCount() << '\n';
//         // hands->getPanel(0)->
//         // getRenderer()->
//         // setBackgroundColor(bgColor);

//     }

//     gui.add(hands);
//     // hands->setVisible(false);
// }