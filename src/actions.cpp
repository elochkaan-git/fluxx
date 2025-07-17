#include "actions.hpp"
#include <iostream>

void
test(State* state)
{
    std::cout << "Testing";
}

std::map<std::string, void (*)(State*)> actions = { { "test", test } };
