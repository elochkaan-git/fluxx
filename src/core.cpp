#include "core.hpp"

void
update(unsigned short int numOfPlayers)
{
    State state(numOfPlayers);
    for (Player*& p : state.getPlayers())
        p->takeCards(state);

    unsigned short int moves = 0;
    bool fl = false, t = 0;
    while (!state.checkWinner()) {
        if (fl)
            state.currentPlayer()->takeCards(state);

        if (state.getRules()->play == 999)
            t = 1;
        else
            t = 0;
        while (moves < state.howManyPlay() - t &&
               state.currentPlayer()->numOfCardsInHands() != 0) {
            // TODO: Для Савелия
            // Реализовать метод, который возвращает название выбранной карты
            // или ее id на нее
            // Далее разыгрывается выбранная карта
            state.getCardById(2)->play(&state);
            moves++;
        }

        // Конец цикла
        fl = true;
        moves = 0;
        state.nextMove();
    }
}