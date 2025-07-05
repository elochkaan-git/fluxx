#ifndef MAIN_HPP
#define MAIN_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <vector>
#include <cstdlib>

#include "card.hpp"
#include "player.hpp"
#include "state.hpp"


void loadMainMenu(tgui::BackendGui& gui);
void loadGameSelect(tgui::BackendGui& gui);

#endif