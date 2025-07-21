#include "core.hpp"
#include <variant>

struct CardVisitor {
    State* state;
    CardVisitor(State* state) { this->state = state; }

    void operator()(CardTheme& card) {
        card.play(state);
    }

    void operator()(CardGoal& card) {
        card.play(state);
    }

    void operator()(CardAction& card) {
        card.play(state);
    }

    void operator()(CardRule& card) {
        card.play(state);
    }
};

void
update(unsigned short int numOfPlayers)
{
    std::vector<Player*> players(numOfPlayers);
    for (Player*& p : players)
        p = new Player();
    State state(players);

    // const Card* t = &std::get<CardTheme>(*state.getCardById(0));
    // t->play(&state);

    unsigned short int takes = 0, moves = 0;
    while (!state.checkWinner()) {
        for (Player*& p : players)
            if (p->isFirstTurn())
                p->takeCards(state);
            else
                while (takes < state.howManyTake()) {
                    p->takeCards(state);
                    takes++;
                }
        takes = 0;

        while (moves < state.howManyPlay()) {
            // TODO: Для Савелия
            // Реализовать метод, который возвращает название выбранной карты
            // или ее id на нее
            // Далее разыгрывается выбранная карта
            Cards* temp = state.getCardById(2);
            std::visit(CardVisitor{&state}, *temp);
            moves++;
        }

        // Конец цикла
        takes = 0;
        moves = 0;
        state.nextMove();
    }

    for (Player*& p : players)
        delete p;
}