#pragma once

#include "card.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

// Объявление класса Player для избежания цикличных включений
class Player;

/**
 * @brief Класс для представления игрового состояния
 *
 */
class State
{
private:
    std::vector<Cards> deck; // Колода
    std::vector<Player*> players;  // Указатели на игроков
    std::vector<unsigned short int> goals,
      rules, dump;            // Id активных карт-целей, карт-правил и карт в сбросе
    RulesParams params; // Текущие правила игры
    // Номера текущего игрока и верхней карты в колоде
    unsigned char currentPlayerID = 0;
    unsigned char currentCardID = 0;
    // Дополнительные цели: количество тем и количество карт
    bool isNumOfThemes = false;
    bool isNumOfCards = false;
    void clearRules();

public:
    State(unsigned short int numOfPlayers);
    void dumpCard(unsigned short int id);
    unsigned short int getCardFromTop();
    Cards* getCardById(unsigned short int id);
    const std::vector<Cards>& getDeck() const;
    void addCardTheme(unsigned short int id,
                      std::string name,
                      std::string imgPath);
    void addCardAction(unsigned short int id,
                       std::string name,
                       std::string imgPath,
                       std::string action);
    void addCardGoal(unsigned short int id,
                     std::string name,
                     std::string imgPath,
                     std::vector<unsigned short int>& themes,
                     bool isNumOfThemes,
                     bool isNumOfCards);
    void addCardRule(unsigned short int id,
                     std::string name,
                     std::string imgPath,
                     RulesParams& params);
    void setGoal(unsigned short int goalId);
    void addRule(unsigned short int ruleId);
    Player* checkWinner();
    Player* currentPlayer();
    Player* nextPlayer();
    Player* nextPlayer(unsigned short int n);
    void nextMove();
    const unsigned short int howManyTake() const;
    const unsigned short int howManyPlay() const;
    const RulesParams* getRules() const;
    void updateRules();
    std::vector<Player*>& getPlayers();
    Player* getPlayerById(unsigned short int id); // TODO: заготовка на будущее
    ~State();
};