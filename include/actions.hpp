#pragma once

#include <map>
#include <string>

class State;
extern std::map<std::string, void(*)(State*)> actions;