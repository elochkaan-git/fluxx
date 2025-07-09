#include "state.hpp"
#include "card.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

void loadImages(State* state)
{
    std::vector<Cards> result(99);
    std::ifstream f("../../config/cards.json");
    json data = json::parse(f);
    
    for(const auto& e : data)
    {
        if(e["category"] == "theme")
        {
            for(const auto& c : e["cards"])
            {
                state->addCardTheme(c["name"], c["imgPath"]);
            }
        }
    }

    f.close();
}

State::State(std::vector<Player*>& players) {
    this->players = players;
    params.play = 1;
    params.take = 1;
        
    loadImages(this);
}

const Cards State::getCard() {
    return deck[currentCardID++];
}

const RulesParams* State::getRules() const
{
    return &this->params;
}

void State::addCardTheme(std::string name, std::string imgPath)
{   
    sf::Texture temp(imgPath);
    auto ptr = std::make_shared<CardTheme>(temp, name);
    this->deck.push_back(ptr);
}