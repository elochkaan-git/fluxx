#include "core.hpp"

void
update(unsigned short int numOfPlayers)
{
    State state(numOfPlayers);
    for (Player*& p : state.getPlayers())
        p->takeCards(state);

    unsigned short int moves = 0;
    bool fl = false;
    while (!state.checkWinner()) {
        if (fl)
            state.currentPlayer()->takeCards(state);

        while (moves < state.howManyPlay()) {
            // TODO: Для Савелия
            // Реализовать метод, который возвращает название выбранной карты
            // или ее id на нее
            // Далее разыгрывается выбранная карта
            Cards* temp = state.getCardById(2);
            std::visit(CardPlay{ &state }, *temp);
            moves++;
        }

        // Конец цикла
        fl = true;
        moves = 0;
        state.nextMove();
    }
}