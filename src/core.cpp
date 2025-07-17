#include "core.hpp"

void
update(unsigned short int numOfPlayers)
{
    std::vector<Player*> players(numOfPlayers);
    for (Player*& p : players)
        p = new Player();
    State state(players);

    unsigned short int takes = 0, moves = 0;
    while(state.checkWinner()) {
        for (Player*& p : players)
            if (p->isFirstTurn()) p->takeCards(state);
            else while(takes < state.howManyTake()) {
                p->takeCards(state);
                takes++;
            }
            takes = 0;

        while(moves < state.howManyPlay()) {
            // Реализовать метод, который возвращает название выбранной карты
            // или указатель std::shared_ptr на нее
            // Далее разыгрывается выбранная карта
            moves++;
        }

        // Конец цикла
        takes = 0; moves = 0;
        state.nextMove();
    }

    for (Player*& p : players)
        delete p;
}