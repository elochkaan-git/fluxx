#include "core.hpp"

void update(unsigned short int numOfPlayers)
{
    std::vector<Player*> players(numOfPlayers);
    for(Player* p : players) p = new Player();
    State state(players);


    for(Player* p : players) delete p;
}