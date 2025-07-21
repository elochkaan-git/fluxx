#include "state.hpp"
#include "card.hpp"
#include "player.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>
#include <random>
#include <string>
#include <variant>
#include <vector>

using json = nlohmann::json;

void
loadCards(State* state)
{
    unsigned short int id = 0;
    std::ifstream f("../config/cards_debug.json");
    json data = json::parse(f);

    for (const auto& e : data) {
        if (e["category"] == "theme") {
            for (const auto& c : e["cards"]) {
                state->addCardTheme(id, c["name"], c["imgPath"]);
                id++;
            }
        } else if (e["category"] == "goal") {
            std::vector<unsigned short int> temp;
            temp.reserve(4);

            for (const auto& c : e["cards"]) {
                for (const std::string& theme : c["themes"]) {
                    for (const Cards& card : state->getDeck()) {
                        CardTheme currentCard = std::get<CardTheme>(card);
                        if (currentCard.getName() == theme) {
                            temp.push_back(currentCard.getId());
                        }
                    }
                }
                // TODO: Добавить обработку целей "Количество карт 10" и
                // "Количество тем 5"
                state->addCardGoal(
                  id, c["name"], c["imgPath"], temp, false, false);
                id++;
            }
        } else if (e["category"] == "action") {
            for (const auto& c : e["cards"]) {
                state->addCardAction(id, c["name"], c["imgPath"], c["action"]);
                id++;
            }
        } else if (e["category"] == "rule") {
            for (const auto& c : e["cards"]) {
                RulesParams temp;
                if (c["rulesParams"].contains("handLimit"))
                    temp.handLimit = c["rulesParams"]["handLimit"];
                else if (c["rulesParams"].contains("themeLimit"))
                    temp.themeLimit = c["rulesParams"]["themeLimit"];
                else if (c["rulesParams"].contains("play"))
                    temp.play = c["rulesParams"]["play"];
                else if (c["rulesParams"].contains("take"))
                    temp.take = c["rulesParams"]["take"];
                else if (c["rulesParams"].contains("castling"))
                    temp.castling = c["rulesParams"]["castling"];
                else if (c["rulesParams"].contains("blindGame"))
                    temp.blindGame = c["rulesParams"]["blindGame"];
                else if (c["rulesParams"].contains("duplet"))
                    temp.duplet = c["rulesParams"]["duplet"];
                else if (c["rulesParams"].contains("withoutHands"))
                    temp.withoutHands = c["rulesParams"]["withoutHands"];
                else if (c["rulesParams"].contains("enough"))
                    temp.enough = c["rulesParams"]["enough"];
                else if (c["rulesParams"].contains("rich"))
                    temp.rich = c["rulesParams"]["rich"];
                else if (c["rulesParams"].contains("random"))
                    temp.random = c["rulesParams"]["random"];
                else if (c["rulesParams"].contains("poverty"))
                    temp.poverty = c["rulesParams"]["povetry"];
                else if (c["rulesParams"].contains("utilize"))
                    temp.utilize = c["rulesParams"]["utilize"];
                else if (c["rulesParams"].contains("dance"))
                    temp.dance = c["rulesParams"]["dance"];
                else if (c["rulesParams"].contains("spinAndTurn"))
                    temp.spinAndTurn = c["rulesParams"]["spinAndTurn"];

                state->addCardRule(id, c["name"], c["imgPath"], temp);
                id++;
            }
        }
    }

    f.close();
}

State::State(std::vector<Player*>& players)
  : goals(0)
{
    this->players = players;
    params.play = 1;
    params.take = 1;

    loadCards(this);

    // std::random_device rd;
    // std::mt19937 g(rd());
    // std::shuffle(deck.begin(), deck.end(), g);
}

Cards
State::getCard()
{
    return deck[currentCardID++];
}

const RulesParams*
State::getRules() const
{
    return &this->params;
}

void
State::addCardTheme(unsigned short int id,
                    std::string name,
                    std::string imgPath)
{
    sf::Texture temp(imgPath);
    this->deck.push_back(CardTheme(id, name, temp));
}

void
State::addCardGoal(unsigned short int id,
                   std::string name,
                   std::string imgPath,
                   std::vector<unsigned short int>& themes,
                   bool isNumOfThemes,
                   bool isNumOfCards)
{
    sf::Texture temp(imgPath);
    this->deck.push_back(
      CardGoal(id, name, temp, themes, isNumOfThemes, isNumOfCards));
}

void
State::addCardAction(unsigned short int id,
                     std::string name,
                     std::string imgPath,
                     std::string action)
{
    sf::Texture temp(imgPath);
    this->deck.push_back(CardAction(id, name, temp, action));
}

void
State::addCardRule(unsigned short int id,
                   std::string name,
                   std::string imgPath,
                   RulesParams& params)
{
    sf::Texture temp(imgPath);
    this->deck.push_back(CardRule(id, name, temp, params));
}

void
State::setGoal(unsigned short int goalId)
{
    unsigned short int numberOfGoals = goals.size();
    if (params.duplet && numberOfGoals == 2) {
        // Реализовать метод, который возвращает указатель на выбранную тему
        // Она будет заменена на предоставленную
    } else if (params.duplet && numberOfGoals < 2) {
        goals.push_back(goalId);
    } else if (numberOfGoals == 1) {
        goals[0] = goalId;
    } else {
        goals.push_back(goalId);
    }
}

bool
State::checkWinner()
{
    unsigned short int count = 0;
    for (unsigned short int& goal : goals) {
        std::vector<unsigned short int> temp =
          std::get<CardGoal>(*getCardById(goal)).getThemes();
        for (Player* p : players) {
            for (const unsigned short int& card : p->getThemes()) {
                if (std::find(temp.begin(), temp.end(), card) != temp.end())
                    count++;
            }
            if (count >= 2)
                return true;
            count = 0;
        }
    }
    return false;
}

const std::vector<Cards>&
State::getDeck() const
{
    return this->deck;
}

Player*
State::currentPlayer()
{
    return players[currentPlayerID];
}

Player*
State::nextPlayer()
{
    if (currentPlayerID + 1 > players.size() - 1)
        return players[0];
    else
        return players[currentPlayerID + 1];
}

Player*
State::nextPlayer(unsigned short int n)
{
    if (currentPlayerID + n > players.size() - 1)
        return players[currentPlayerID + n - players.size()];
    else if (currentPlayerID + n < 0)
        return players[players.size() - currentPlayerID + n + 1];
    else
        return players[currentPlayerID + n];
}

void
State::nextMove()
{
    if (currentPlayerID + 1 > players.size() - 1)
        currentPlayerID = 0;
    else
        currentPlayerID++;
}

const unsigned short int
State::howManyTake() const
{
    return params.take;
}

const unsigned short int
State::howManyPlay() const
{
    return params.play;
}

void
State::addRule(unsigned short int ruleId)
{
    if (std::get<CardRule>(*getCardById(ruleId)).getName().find("Тяни") !=
        std::string::npos) {
        for (unsigned short int& ptr : rules) {
            if (std::get<CardRule>(*getCardById(ptr)).getName().find("Тяни") !=
                std::string::npos) {
                ptr = ruleId;
                break;
            }
        }
    } else if (std::get<CardRule>(*getCardById(ruleId))
                 .getName()
                 .find("Сыграй") != std::string::npos) {
        for (unsigned short int& ptr : rules) {
            if (std::get<CardRule>(*getCardById(ptr))
                  .getName()
                  .find("Сыграй") != std::string::npos) {
                ptr = ruleId;
                break;
            }
        }
    } else if (std::get<CardRule>(*getCardById(ruleId))
                 .getName()
                 .find("Предел тем") != std::string::npos) {
        for (unsigned short int& ptr : rules) {
            if (std::get<CardRule>(*getCardById(ptr))
                  .getName()
                  .find("Предел тем") != std::string::npos) {
                ptr = ruleId;
                break;
            }
        }
    } else if (std::get<CardRule>(*getCardById(ruleId))
                 .getName()
                 .find("Предел руки") != std::string::npos) {
        for (unsigned short int& ptr : rules) {
            if (std::get<CardRule>(*getCardById(ptr))
                  .getName()
                  .find("Предел руки") != std::string::npos) {
                ptr = ruleId;
                break;
            }
        }
    } else {
        rules.push_back(ruleId);
    }

    updateRules();
}

void
State::updateRules()
{
    clearRules();
    for (unsigned short int& ptr : rules) {
        RulesParams ruleParams =
          std::get<CardRule>(*getCardById(ptr)).getParams();
        if (ruleParams.take > 1)
            params.take = ruleParams.take;
        else if (ruleParams.play > 1)
            params.play = ruleParams.play;
        else if (ruleParams.themeLimit > -1)
            params.themeLimit = ruleParams.themeLimit;
        else if (ruleParams.handLimit > -1)
            params.handLimit = ruleParams.handLimit;

        params.blindGame |= ruleParams.blindGame;
        params.castling |= ruleParams.castling;
        params.dance |= ruleParams.dance;
        params.duplet |= ruleParams.duplet;
        params.enough |= ruleParams.enough;
        params.inflation |= ruleParams.inflation;
        params.poverty |= ruleParams.poverty;
        params.random |= ruleParams.random;
        params.rich |= ruleParams.rich;
        params.spinAndTurn |= ruleParams.spinAndTurn;
        params.utilize |= ruleParams.utilize;
        params.withoutHands |= ruleParams.withoutHands;
    }
}

void
State::clearRules()
{
    params.take = 1;
    params.play = 1;
    params.themeLimit = -1;
    params.handLimit = -1;
    params.blindGame = false;
    params.castling = false;
    params.dance = false;
    params.duplet = false;
    params.enough = false;
    params.inflation = false;
    params.poverty = false;
    params.random = false;
    params.rich = false;
    params.spinAndTurn = false;
    params.utilize = false;
    params.withoutHands = false;
}

Cards*
State::getCardById(unsigned short int id)
{
    for (Cards& card : deck) {
        if (std::holds_alternative<CardTheme>(card)) {
            CardTheme t = std::get<CardTheme>(card);
            if (t.getId() == id)
                return &card;
        } else if (std::holds_alternative<CardGoal>(card)) {
            CardGoal t = std::get<CardGoal>(card);
            if (t.getId() == id)
                return &card;
        } else if (std::holds_alternative<CardAction>(card)) {
            CardAction t = std::get<CardAction>(card);
            if (t.getId() == id)
                return &card;
        } else {
            CardRule t = std::get<CardRule>(card);
            if (t.getId() == id)
                return &card;
        }
    }
}