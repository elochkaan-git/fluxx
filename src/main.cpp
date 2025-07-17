#include "core.hpp"
#include "gui.hpp"
#include <stdio.h>

int main() {
  // update(3);
  FILE *settings = fopen("./config/settings.txt", "r");
  sf::Vector2u resolution;
  fscanf(settings, "%ux%u", &resolution.x, &resolution.y);
  fclose(settings);
  tgui::Theme::setDefault(tgui::Theme::create("./bin/themes/Black.txt"));

  auto window = sf::RenderWindow(sf::VideoMode(resolution), "Fluxx",
                                 sf::Style::Titlebar | sf::Style::Close);
  tgui::Gui gui{window};

  if (runExample(std::ref(gui)))
    gui.mainLoop(sf::Color::Black);
}
