#include "gamegui.hpp"

void loadGame(tgui::Gui &gui, int numberOfPlayers) {
  gui.removeAllWidgets();

  /*
      Initialization main panels for main game window
  */
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
}