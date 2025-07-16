#include "state.hpp"
#include "card.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>

using json = nlohmann::json;

void loadImages(State* state)
{   
    std::vector<Cards> result(99);
    std::ifstream f("../config/cards.json");
    json data = json::parse(f);
    
    for(const auto& e : data)
    {
        if(e["category"] == "theme")
        {
            for(const auto& c : e["cards"])
            {
                state->addCardTheme(c["name"], c["imgPath"], c["theme"]);
            }
        }
        else if(e["category"] == "action")
        {
            for(const auto& c : e["cards"])
            {
                state->addCardAction(c["name"], c["imgPath"], c["action"]);
            }
        }
        else if(e["category"] == "goal")
        {
            for(const auto& c : e["cards"])
            {   
                std::vector<std::string> temp = c["themes"];
                state->addCardGoal(c["name"], c["imgPath"], temp, false, false);
            }
        }
        else if(e["category"] == "rule")
        {
            for(const auto& c : e["cards"])
            {   
                RulesParams temp;
                if(c["rulesParams"].contains("handLimit")) temp.handLimit             = c["rulesParams"]["handLimit"];
                else if(c["rulesParams"].contains("themeLimit")) temp.themeLimit      = c["rulesParams"]["themeLimit"];
                else if(c["rulesParams"].contains("play")) temp.play                  = c["rulesParams"]["play"];
                else if(c["rulesParams"].contains("take")) temp.take                  = c["rulesParams"]["take"];
                else if(c["rulesParams"].contains("castling")) temp.castling          = c["rulesParams"]["castling"];
                else if(c["rulesParams"].contains("blindGame")) temp.blindGame        = c["rulesParams"]["blindGame"];
                else if(c["rulesParams"].contains("duplet")) temp.duplet              = c["rulesParams"]["duplet"];
                else if(c["rulesParams"].contains("withoutHands")) temp.withoutHands  = c["rulesParams"]["withoutHands"];
                else if(c["rulesParams"].contains("enough")) temp.enough              = c["rulesParams"]["enough"];
                else if(c["rulesParams"].contains("rich")) temp.rich                  = c["rulesParams"]["rich"];
                else if(c["rulesParams"].contains("random")) temp.random              = c["rulesParams"]["random"];
                else if(c["rulesParams"].contains("poverty")) temp.poverty            = c["rulesParams"]["povetry"];
                else if(c["rulesParams"].contains("utilize")) temp.utilize            = c["rulesParams"]["utilize"];
                else if(c["rulesParams"].contains("dance")) temp.dance                = c["rulesParams"]["dance"];
                else if(c["rulesParams"].contains("spinAndTurn")) temp.spinAndTurn    = c["rulesParams"]["spinAndTurn"];

                state->addCardRule(c["name"], c["imgPath"], temp);
            }
        }
    }

    f.close();
}

State::State(std::vector<Player*>& players) 
{
    this->players = players;
    params.play = 1;
    params.take = 1;
        
    loadImages(this);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

const Cards State::getCard() 
{
    return deck[currentCardID++];
}

const RulesParams* State::getRules() const
{
    return &this->params;
}

void State::addCardTheme(std::string name, std::string imgPath, std::string theme)
{   
    sf::Texture temp(imgPath);
    auto ptr = std::make_shared<CardTheme>(name, temp, theme);
    this->deck.push_back(ptr);
}

void State::addCardAction(std::string name, std::string imgPath, std::string action)
{
    sf::Texture temp(imgPath);
    auto ptr = std::make_shared<CardAction>(name, temp, action);
    this->deck.push_back(ptr);
}

void State::addCardGoal(std::string name, std::string imgPath, std::vector<std::string>& themes, bool isNumOfThemes, bool isNumOfCards)
{   
    sf::Texture temp(imgPath);
    auto ptr = std::make_shared<CardGoal>(name, temp, themes, isNumOfThemes, isNumOfCards);
    this->deck.push_back(ptr);
}

void State::addCardRule(std::string name, std::string imgPath, RulesParams& params)
{   
    sf::Texture temp(imgPath);
    auto ptr = std::make_shared<CardRule>(name, temp, params);
    this->deck.push_back(ptr);
}