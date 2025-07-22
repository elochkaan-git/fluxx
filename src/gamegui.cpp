#include "gamegui.hpp"

void makeGlow(tgui::Picture::Ptr card){
  auto glowTexture = card->getRenderer()->getTexture();
  glowTexture.setColor(tgui::Color::Yellow);
  
  card->getRenderer()->setTexture(glowTexture);
}

void makeNormal(tgui::Picture::Ptr card){
  if(card->getWidgetName() != "SelectedCard"){
  auto glowTexture = card->getRenderer()->getTexture();
  glowTexture.setColor(tgui::Color::White);
  card->getRenderer()->setTexture(glowTexture);
  }
}

void selectCard(tgui::Gui& gui ,tgui::Picture::Ptr card){
  auto lastSelected = gui.get<tgui::Picture>("SelectedCard");
  if(lastSelected){
    lastSelected->setWidgetName("NonSelected");
    makeNormal(lastSelected);
  }
  card->setWidgetName("SelectedCard");
  auto glowTexture = card->getRenderer()->getTexture();
  glowTexture.setColor(tgui::Color::Green);
  card->getRenderer()->setTexture(glowTexture);
}

auto createCard(const tgui::String& pathToTexture, tgui::Gui& gui){
  auto card = tgui::Picture::create(pathToTexture);
  auto sizeOfCard = card->getSize();
  auto resolution = gui.getWindow()->getSize();
  // card->setSize("15%", "15%");
  card->onMouseEnter(&makeGlow, card);
  card->onMouseLeave(&makeNormal, card);
  card->onClick(&selectCard, std::ref(gui), card);

  float scaleY = resolution.y / sizeOfCard.y;
  float scale = scaleY * 0.15f;
  card->setSize({sizeOfCard.x * scale, sizeOfCard.y * scale});
  return card;

}

void showCardsButtonOnToggle(tgui::Gui& gui, bool isDown){
  auto hand = gui.get<tgui::ScrollablePanel>("Hand");
  if(isDown){
    hand->showWithEffect(tgui::ShowEffectType::SlideFromBottom, 400);
  }
  else{
    hand->hideWithEffect(tgui::ShowEffectType::SlideToBottom, 400);
  }
}

////////////////////////////////////////////////////////////////////////////

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

  auto showCardsButton = tgui::ToggleButton::create("Show");
  functionalPanel->add(showCardsButton);
  showCardsButton->setAutoLayout(tgui::AutoLayout::Bottom);
  showCardsButton->setHeight(buttonSize.y);
  showCardsButton->onToggle([showCardsButton, &gui](bool isDown){
  if (isDown) {
    showCardsButton->setText("Hide");

  }
  else {
    showCardsButton->setText("Show");
  }
  showCardsButtonOnToggle(gui, isDown);
  });

  auto confirmButton = tgui::Button::create("Confirm");
  functionalPanel->add(confirmButton);
  confirmButton->setAutoLayout(tgui::AutoLayout::Bottom);
  confirmButton->setHeight(buttonSize.y);
  confirmButton->onClick(&loadMainMenu, std::ref(gui));

  auto startGameButton = tgui::Button::create("Start\ngame");
  functionalPanel->add(startGameButton);
  startGameButton->setSize({"100%", "16%"});
  startGameButton->setOrigin(0.5f,0.5f);
  startGameButton->setPosition({"50%", "50%"});
  
  startGameButton->onClick(&loadMainMenu, std::ref(gui));
}

void initPlayersBoardCards(tgui::Gui &gui, int numberOfPlayers){
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
  splitBottom->setSplitterOffset("100%");
  splitBottom->setAutoLayout(tgui::AutoLayout::Bottom);
  splitBottom->add(firstPlayerCards);
  
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
  splitTop->setSplitterOffset("100%");
  splitTop->setAutoLayout(tgui::AutoLayout::Top);
  splitTop->add(secondPlayerCards);
  
  gui.add(splitTop);

  switch (numberOfPlayers)
  {
    case 4:
      splitBottom->add(fourthPlayerCards);
      splitBottom->setSplitterOffset("50%");
    case 3:
      splitTop->add(thirdPlayerCards);
      splitTop->setSplitterOffset("50%");
      break;
  }

  /*
    Test block
  */
  tgui::String defaultTexure = "./resources/img/default.png";
  for(int i = 0; i < 5; i++){
    auto Test = createCard(defaultTexure, gui);
    firstPlayerCards->add(Test);
    // Test->setScale(0.3f);
    Test->setPosition(i*80, 0);
    
  }
  for(int i = 0; i < 5; i++){
    auto Test = createCard(defaultTexure, gui);
    secondPlayerCards->add(Test);
    // Test->setScale(0.3f);
    Test->setPosition(i*80, 0);
    
  }

  for(int i = 0; i < 5; i++){
    auto Test = createCard(defaultTexure, gui);
    thirdPlayerCards->add(Test);
    // Test->setScale(0.3f);
    Test->setPosition(i*80, 0);
    
  }

  for(int i = 0; i < 5; i++){
    auto Test = createCard(defaultTexure, gui);
    fourthPlayerCards->add(Test);
    // Test->setScale(0.3f);
    Test->setPosition(i*80, 0);
    
  }

}

void initGoalPanel(tgui::Gui &gui){
  auto goalPanel = tgui::HorizontalWrap::create();
  goalPanel->setAutoLayout(tgui::AutoLayout::Left);
  goalPanel->setWidth({"20%"});
  goalPanel->getRenderer()->setPadding({5}); // Keep 5px on all sides as empty space
  goalPanel->getRenderer()->setSpaceBetweenWidgets(10); // Put a 10px gap beside and below widgets
  for(int i = 0; i < 6; i++){
    goalPanel->add(createCard("./resources/img/default.png", gui));
  }
  gui.add(goalPanel);

}

void initRulePanel(tgui::Gui &gui){
  auto rulePanel = tgui::HorizontalWrap::create();
  rulePanel->setAutoLayout(tgui::AutoLayout::Right);
  rulePanel->setWidth({"20%"});
  rulePanel->getRenderer()->setPadding({5}); // Keep 5px on all sides as empty space
  rulePanel->getRenderer()->setSpaceBetweenWidgets(10); // Put a 10px gap beside and below widgets
  for(int i = 0; i < 6; i++){
    rulePanel->add(createCard("./resources/img/default.png", gui));
  }
  gui.add(rulePanel);

}

void initPlayerHand(tgui::Gui &gui){
  auto hand = tgui::ScrollablePanel::create({"75%", "25%"});
  hand->setWidgetName("Hand");
  hand->getVerticalScrollbar()->setPolicy(
      tgui::Scrollbar::Policy::Never);
  hand->getRenderer()->setBackgroundColor("rgb(94, 96, 104)");
  hand->getRenderer()->setBorders(6);
  hand->getRenderer()->setBorderColor("rgb(48, 47, 47)");
  hand->setOrigin(0.5f,1.f);
  hand->setPosition({"57.5%", "100%"});

  //TestBlock
  tgui::String defaultTexure = "./resources/img/default.png";
  for(int i = 0; i < 10; i++){
    auto Test = createCard(defaultTexure, gui);
    hand->add(Test);
    // Test->setScale(0.3f);
    Test->setPosition(i*80+4, 4);
  }
  gui.add(hand);
  hand->setVisible(false);
}

void loadGame(tgui::Gui &gui, int numberOfPlayers) {
  gui.removeAllWidgets();

  /*
      Initialization main panels for main game window
  */
  initfunctionalPanel(gui);
  initPlayersBoardCards(gui, numberOfPlayers);
  initGoalPanel(gui);
  initRulePanel(gui);
  

  auto centralPanel = tgui::Panel::create();
  // centralPanel->getRenderer()->setSpaceBetweenWidgets(10.f);
  centralPanel->setAutoLayout(tgui::AutoLayout::Fill);
  // centralPanel->setWidth({"40%"});


  auto Deck = createCard("./resources/img/default.png", gui);
  centralPanel->add(Deck);
  Deck->setPosition({"10%","10%"});
  // Deck->setScale(0.3f);
  auto StateLabel = tgui::Label::create("Main label");
  StateLabel->setText("Waiting for players");
  centralPanel->add(StateLabel);
  StateLabel->setPosition({"10%","50%"});
  auto Dump = createCard("./resources/img/default.png", gui);
  // Dump->setScale(0.3f);
  centralPanel->add(Dump);
  Dump->setPosition({"10%","70%"});
  gui.add(centralPanel);

  initPlayerHand(gui);
  
}