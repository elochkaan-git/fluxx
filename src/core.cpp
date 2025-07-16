#include "core.hpp"

void update(unsigned short int numOfPlayers)
{
    std::vector<Player*> players(numOfPlayers);
    for(Player*& p : players) p = new Player();
    State state(players);

    players[0]->takeCards(state);
    players[0]->takeCards(state);
    state.setGoal(players[0]->getCard(2));
    players[0]->setThemes(players[0]->getCardT(0));
    players[0]->setThemes(players[0]->getCardT(1));

    state.checkWinner();


    for(Player* p : players) delete p;
}