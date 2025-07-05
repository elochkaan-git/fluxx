#include "card.hpp"
#include "player.hpp"
#include "state.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <vector>

int main() {
    sf::Texture t("./img/default.png");
    std::vector<Player*> players = {new Player(), new Player()};
    State state(players);
}