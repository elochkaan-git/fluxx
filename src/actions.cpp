#include "actions.hpp"
#include "player.hpp"

void
allGetOne(State* state)
{
    for (Player*& p : state->getPlayers())
        p->takeCards(*state);
}

void
beEasier(State* state)
{   
    std::vector<unsigned short int> ids = state->getRulesId();
    for (unsigned short int id; id < ids.size() / 2; ++id) {
        state->dumpCard(id);
    }
}

void
bigCleaning(State* state)
{   
    auto deck = state->getDeck();
    state->clearDump();
    state->dumpCard(std::find(deck.begin(), deck.end(), "Будь проще")->getId());
    state->shuffleDeck();
    state->setCurrentCardId(0);
}

void
borderless(State* state)
{
    
}

std::map<std::string, void (*)(State*)> actions = { 
    { "allGetOne", allGetOne },
    { "beEasier", beEasier },
    { "bigCleaning", bigCleaning },
    { "borderless", borderless }
};
