#include "gamegui.hpp"

void initfunctionalPanel(tgui::Gui &gui){
  auto functionalPanel = tgui::Panel::create();
  functionalPanel->setWidth("15%");
  functionalPanel->getRenderer()->setBackgroundColor("rgb(80,  80,  80)");
  functionalPanel->setAutoLayout(tgui::AutoLayout::Leftmost);
  functionalPanel->getRenderer()->setPadding({"3%"});

  gui.add(functionalPanel);

  const sf::Vector2<tgui::String> buttonSize{"30%", "8%"};

  auto backButton = tgui::Button::create("Exit");
  functionalPanel->add(backButton);
  backButton->setAutoLayout(tgui::AutoLayout::Top);
  backButton->setHeight(buttonSize.y);
  backButton->onClick(&loadMainMenu, std::ref(gui));

  auto showCardsButton = tgui::Button::create("Show");
  functionalPanel->add(showCardsButton);
  showCardsButton->setAutoLayout(tgui::AutoLayout::Bottom);
  showCardsButton->setHeight(buttonSize.y);
  showCardsButton->onClick(&loadMainMenu, std::ref(gui));

  auto confirmButton = tgui::Button::create("Confirm");
  functionalPanel->add(confirmButton);
  confirmButton->setAutoLayout(tgui::AutoLayout::Bottom);
  confirmButton->setHeight(buttonSize.y);
  confirmButton->onClick(&loadMainMenu, std::ref(gui));
}

void initPlayersBoardCards(tgui::Gui &gui){
  auto firstPlayerCards = tgui::ScrollablePanel::create();
  firstPlayerCards->getVerticalScrollbar()->setPolicy(
      tgui::Scrollbar::Policy::Never);
  firstPlayerCards->getRenderer()->setBackgroundColor("rgb(120, 141, 233)");

  auto fourthPlayerCards = tgui::ScrollablePanel::create();
  fourthPlayerCards->getVerticalScrollbar()->setPolicy(
      tgui::Scrollbar::Policy::Never);
  fourthPlayerCards->getRenderer()->setBackgroundColor("rgb(120, 233, 126)");

  auto splitBottom = tgui::SplitContainer::create();
  splitBottom->setHeight("20%");
  splitBottom->setSplitterOffset("50%");
  splitBottom->setAutoLayout(tgui::AutoLayout::Bottom);
  splitBottom->add(firstPlayerCards);
  splitBottom->add(fourthPlayerCards);
  gui.add(splitBottom);

  auto secondPlayerCards = tgui::ScrollablePanel::create();
  secondPlayerCards->getVerticalScrollbar()->setPolicy(
      tgui::Scrollbar::Policy::Never);
  secondPlayerCards->getRenderer()->setBackgroundColor("rgb(233, 156, 120)");

  auto thirdPlayerCards = tgui::ScrollablePanel::create();
  thirdPlayerCards->getVerticalScrollbar()->setPolicy(
      tgui::Scrollbar::Policy::Never);
  thirdPlayerCards->getRenderer()->setBackgroundColor("rgb(207, 120, 233)");

  auto splitTop = tgui::SplitContainer::create();
  splitTop->setHeight("20%");
  splitTop->setSplitterOffset("50%");
  splitTop->setAutoLayout(tgui::AutoLayout::Top);
  splitTop->add(secondPlayerCards);
  splitTop->add(thirdPlayerCards);
  gui.add(splitTop);

  /*
    Test block
  */
  for(int i = 0; i < 5; i++){
    auto Test = tgui::Picture::create("./resources/img/default.png");
    firstPlayerCards->add(Test);
    Test->setScale(0.3f);
    Test->setPosition(i*80, 0);
    
  }
  for(int i = 0; i < 5; i++){
    auto Test = tgui::Picture::create("./resources/img/default.png");
    secondPlayerCards->add(Test);
    Test->setScale(0.3f);
    Test->setPosition(i*80, 0);
    
  }

  for(int i = 0; i < 5; i++){
    auto Test = tgui::Picture::create("./resources/img/default.png");
    thirdPlayerCards->add(Test);
    Test->setScale(0.3f);
    Test->setPosition(i*80, 0);
    
  }

  for(int i = 0; i < 5; i++){
    auto Test = tgui::Picture::create("./resources/img/default.png");
    fourthPlayerCards->add(Test);
    Test->setScale(0.3f);
    Test->setPosition(i*80, 0);
  }

}

void initGoalPanel(tgui::Gui &gui){
  auto goalPanel = tgui::HorizontalWrap::create();
  goalPanel->setAutoLayout(tgui::AutoLayout::Left);
  goalPanel->setWidth({"25%"});
  goalPanel->getRenderer()->setPadding({5}); // Keep 5px on all sides as empty space
  goalPanel->getRenderer()->setSpaceBetweenWidgets(10); // Put a 10px gap beside and below widgets
  for(int i = 0; i < 6; i++){
    auto Test = tgui::Picture::create("./resources/img/default.png");
    // Test->setSize(Test->s);  
    goalPanel->add(Test);
  }
  gui.add(goalPanel);

}

void initRulePanel(tgui::Gui &gui){
  auto rulePanel = tgui::HorizontalWrap::create();
  rulePanel->setAutoLayout(tgui::AutoLayout::Right);
  rulePanel->setWidth({"25%"});
  rulePanel->getRenderer()->setPadding({5}); // Keep 5px on all sides as empty space
  rulePanel->getRenderer()->setSpaceBetweenWidgets(10); // Put a 10px gap beside and below widgets
  for(int i = 0; i < 6; i++){
    auto Test = tgui::Picture::create("./resources/img/default.png");
    Test->setSize(50, 50);
    rulePanel->add(Test);
  }
  gui.add(rulePanel);

}

void loadGame(tgui::Gui &gui, int numberOfPlayers) {
  gui.removeAllWidgets();

  /*
      Initialization main panels for main game window
  */
  initfunctionalPanel(gui);
  initPlayersBoardCards(gui);
  initGoalPanel(gui);
  initRulePanel(gui);

  auto centralPanel = tgui::Panel::create();
  // centralPanel->getRenderer()->setSpaceBetweenWidgets(10.f);
  centralPanel->setAutoLayout(tgui::AutoLayout::Fill);
  // centralPanel->setWidth({"40%"});

  auto Deck = tgui::Picture::create("./resources/img/default.png");
  centralPanel->add(Deck);
  Deck->setPosition({"10%","10%"});
  Deck->setScale(0.3f);
  auto StateLabel = tgui::Label::create("Main label");
  StateLabel->setText("Place holder");
  centralPanel->add(StateLabel);
  StateLabel->setPosition({"10%","50%"});
  auto Dump = tgui::Picture::create("./resources/img/default.png");
  Dump->setScale(0.3f);
  centralPanel->add(Dump);
  Dump->setPosition({"10%","70%"});
  gui.add(centralPanel);

   
  
}