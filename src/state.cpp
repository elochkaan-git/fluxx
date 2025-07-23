#include "state.hpp"
#include "card.hpp"
#include "player.hpp"
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>
#include <random>
#include <string>
#include <variant>
#include <vector>

using json = nlohmann::json;

/**
 * @brief Функция для загрузки карт согласно файлу-конфигурации
 *
 * @param state Игровое состояние
 */
void
loadCards(State* state)
{
    unsigned short int id = 0;
    std::ifstream f("./config/cards.json"); // Загружаем конфиг
    json data = json::parse(f);

    for (const auto& e : data) {
        if (e["category"] == "theme") {
            for (const auto& c : e["cards"]) {
                state->addCardTheme(id, c["name"], c["imgPath"]);
                id++;
            }
        } else if (e["category"] == "goal") {
            std::vector<unsigned short int> themes;
            themes.reserve(4);
            bool isNumOfThemes = false, isNumOfCards = false;

            // Проходимся по картам-целям
            for (const auto& c : e["cards"]) {
                isNumOfThemes = false, isNumOfCards = false;
                // Проходимся по названиям тем каждой цели из конфига
                for (const std::string& theme : c["themes"]) {
                    if (theme == "В десяточку!") {
                        isNumOfCards = true;
                        break;
                    } else if (theme == "5 тем") {
                        isNumOfThemes = true;
                        break;
                    } else
                        // Проходимся по картам из колоды
                        for (const Cards& card : state->getDeck()) {
                            // Если карта - это карта-тема, то...
                            if (std::holds_alternative<CardTheme>(card)) {
                                // ...cравниваем ее имя с темой, указанной в
                                // цели
                                CardTheme currentCard =
                                  std::get<CardTheme>(card);
                                if (currentCard.getName() == theme) {
                                    // При соответствии добавляем Id найденной
                                    // карты во временный массив
                                    themes.push_back(currentCard.getId());
                                }
                            }
                        }
                }
                state->addCardGoal(id,
                                   c["name"],
                                   c["imgPath"],
                                   themes,
                                   isNumOfThemes,
                                   isNumOfCards);
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

/**
 * @brief Конструктор для начального игрового состояния
 *
 * @param numOfPlayers Количество игроков
 */
State::State(unsigned short int numOfPlayers)
  : goals(0)
{
    // Инициализируем игроков и присвиваем каждому уникальный id
    unsigned short int id = 0;
    std::vector<Player*> players(numOfPlayers);
    for (Player*& p : players) {
        p = new Player(id++);
    }

    this->players = players;
    params.play = 1;
    params.take = 1;

    loadCards(this);

    // Перемешиваем колоду после загрузки
    // std::random_device rd;
    // std::mt19937 g(rd());
    // std::shuffle(deck.begin(), deck.end(), g);
}

/**
 * @brief Деструктор игрового состояния. Очищает память от игроков
 *
 */
State::~State()
{
    for (Player*& p : players)
        delete p;
}

/**
 * @brief Возвращает Id карты с верха колоды
 *
 * @return unsigned short int Id верхней карты
 */
unsigned short int
State::getCardFromTop()
{
    Cards t = deck[currentCardID++];
    if (std::holds_alternative<CardTheme>(t)) {
        return std::get<CardTheme>(t).getId();
    } else if (std::holds_alternative<CardGoal>(t)) {
        return std::get<CardGoal>(t).getId();
    } else if (std::holds_alternative<CardAction>(t)) {
        return std::get<CardAction>(t).getId();
    } else if (std::holds_alternative<CardRule>(t)) {
        return std::get<CardRule>(t).getId();
    }
    return 0;
}

/**
 * @brief Возвращает текущие правила игры
 *
 * @return const RulesParams* Указатель на текущие правила
 */
const RulesParams*
State::getRules() const
{
    return &this->params;
}

/**
 * @brief Добавляет в колоду карту-тему
 *
 * @param id Id карты
 * @param name Название карты
 * @param imgPath Путь до изображения
 */
void
State::addCardTheme(unsigned short int id,
                    std::string name,
                    std::string imgPath)
{
    this->deck.push_back(CardTheme(id, name, imgPath));
}

/**
 * @brief Добавляет в колоду карту-цель
 *
 * @param id Id карты
 * @param name Название карты
 * @param imgPath Путь до изображения
 * @param themes Вектор Id карт-тем?
 * @param isNumOfThemes Цель на количество тем?
 * @param isNumOfCards Цель на количество карт?
 */
void
State::addCardGoal(unsigned short int id,
                   std::string name,
                   std::string imgPath,
                   std::vector<unsigned short int>& themes,
                   bool isNumOfThemes,
                   bool isNumOfCards)
{
    this->deck.push_back(
      CardGoal(id, name, imgPath, themes, isNumOfThemes, isNumOfCards));
}

/**
 * @brief Добавляет в колоду карту-действия
 *
 * @param id Id карты
 * @param name Название карты
 * @param imgPath Путь до изображения
 * @param action название действия (см. файл actions.hpp и actions.cpp)
 */
void
State::addCardAction(unsigned short int id,
                     std::string name,
                     std::string imgPath,
                     std::string action)
{
    this->deck.push_back(CardAction(id, name, imgPath, action));
}

/**
 * @brief Добавляет в колоду карту-правило
 *
 * @param id Id карты
 * @param name Название карты
 * @param imgPath Путь до изображения
 * @param params Параметры правил
 */
void
State::addCardRule(unsigned short int id,
                   std::string name,
                   std::string imgPath,
                   RulesParams& params)
{
    this->deck.push_back(CardRule(id, name, imgPath, params));
}

/**
 * @brief Устанавливает правила для текущей игры
 *
 * @param goalId Id новой карты-цели
 */
void
State::setGoal(unsigned short int goalId)
{
    unsigned short int numberOfGoals = goals.size();
    if (params.duplet && numberOfGoals == 2) {
        // TODO: Для Савелия
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

/**
 * @brief Возвращает указатель на победителя, иначе nullptr
 *
 * @return Player* Указатель на победителя
 */
Player*
State::checkWinner()
{
    unsigned short int count = 0;
    for (unsigned short int& goal : goals) {
        std::vector<unsigned short int> temp =
          std::get<CardGoal>(*getCardById(goal)).getThemes();
        for (Player* p : players) {
            if (isNumOfCards && p->numOfCardsInHands() >= 10)
                return p;
            else if (isNumOfThemes && p->getThemes().size() >= 5)
                return p;
            else
                for (const unsigned short int& card : p->getThemes()) {
                    if (std::find(temp.begin(), temp.end(), card) != temp.end())
                        count++;
                }
            if (count >= 2)
                return p;
            count = 0;
        }
    }
    return nullptr;
}

/**
 * @brief Возвращает колоду
 *
 * @return const std::vector<Cards>& Колода
 */
const std::vector<Cards>&
State::getDeck() const
{
    return this->deck;
}

/**
 * @brief Возвращает указатель на текущего игрока
 *
 * @return Player* Текущий игрок
 */
Player*
State::currentPlayer()
{
    return players[currentPlayerID];
}

/**
 * @brief Возвращает указатель на следующего игрока
 *
 * @return Player*
 */
Player*
State::nextPlayer()
{
    if (currentPlayerID + 1 > players.size() - 1)
        return players[0];
    else
        return players[currentPlayerID + 1];
}

/**
 * @brief Возвращает указатель на n-ого игрока от текущего игрока
 *
 * @param n Количество позиций от текущего игрока
 * @return Player* Указатель на игрока
 */
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

/**
 * @brief Смена хода на следующий. Меняет ID текущего игрока
 *
 */
void
State::nextMove()
{
    if (currentPlayerID + 1 > players.size() - 1)
        currentPlayerID = 0;
    else
        currentPlayerID++;
}

/**
 * @brief Возвращает количество карт, которые нужно взять
 *
 * @return const unsigned short int Количество карт
 */
const unsigned short int
State::howManyTake() const
{
    return params.take;
}

/**
 * @brief Возвращает количество карт, которые нужно сыграть
 *
 * @return const unsigned short int Количество карт
 */
const unsigned short int
State::howManyPlay() const
{
    return params.play;
}

/**
 * @brief Добавляет новое правило в вектор правил
 *
 * @param ruleId Id карты-правила
 */
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

/**
 * @brief Обновляет текущие правила игры
 *
 */
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

/**
 * @brief Очищает правила до базовых
 *
 */
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

/**
 * @brief Возвращает указатель на карту по переданному Id
 * @code {.cpp}
 * Cards* card = state.getCardById(2);
 * std::visit(CardPlay{&state}, card); // Необходимо, чтобы сыграть карту
 * std::visit(CardSprite{}, card); // Необходимо, чтобы получить спрайт карты
 * std::visit(CardId{}, card); // Необходимо, чтобы получить Id карты
 * @endcode
 *
 * @param id Id карты
 * @return Cards* Указатель на карту
 */
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
    return nullptr;
}

/**
 * @brief Возвращает вектор указателей на игроков
 *
 * @code {.cpp}
 * for(Player*& p : state.getPlayers()) {
 *     auto id = p->getId();
 *     auto themes = p->getThemes();
 *     // etc
 * }
 * @endcode
 * @return std::vector<Player*>& Вектор указателей на игроков
 */
std::vector<Player*>&
State::getPlayers()
{
    return this->players;
}