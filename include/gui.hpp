#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <fstream>

#include "gamegui.hpp"

bool runExample(tgui::Gui& gui);
void loadMainMenu(tgui::Gui& gui);
void loadGameSelect(tgui::Gui& gui);
void loadSettings(tgui::Gui& gui);
void loadGameCreate(tgui::Gui& gui);
