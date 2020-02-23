#ifndef LOGIC_GAME_HPP
#define LOGIC_GAME_HPP

#include "player.hpp"
#include "../field/tilemap.hpp"
#include "../base/interfaces.hpp"
#include "../structs/transform.hpp"
#include "../other/logger.hpp"
#include "../game/game_rules.hpp"


//TODO template<int P, typename T> //Where P is player count, T : game_rules
class game : public iserializable {
private:
    //static const int player_count = P; //TODO make something not so rubbish-like
    static std::shared_ptr<game> instance; //TODO no singleton cuz there are more than one sessions on the server

    std::shared_ptr<tilemap> map;
    std::shared_ptr<std::vector<std::shared_ptr<player>>> players; //TODO player 0 holds neutral objects, TODO remove second shared_ptr
    std::shared_ptr<game_rules> rule; //TODO T rule;
    int next_id; //TODO maybe into player (optimizing search speed)

public:
    static std::shared_ptr<game> get ();

    explicit game ();
    game (const game& copy);
    game& operator= (const game& copy);
    std::shared_ptr<json> serialize (serializers type) const override;
    void deserialize (json& package) override;

    ~game () override;
    int get_unique_id ();
    std::shared_ptr<unit> get_unit_by_id (int id);
};

std::shared_ptr<game> game::instance = nullptr;

std::shared_ptr<game> game::get () {
    if (instance == nullptr) instance = std::make_shared<game>();
    return instance;
}

game::game () {
    next_id = 1;
    //this->map = std::make_shared<tilemap>(seed);
    this->players = std::make_shared<std::vector<std::shared_ptr<player>>>();
    //choreographer::init(this->map);
    //TODO
}

game::game (const game& copy) {
    //TODO
    // next_id = get_unique_id(); //?
}

game& game::operator= (const game& copy) {
    if (this != &copy) {
        //this = game(copy); //TODO ^^^
    }
    return *this;
}

std::shared_ptr<json> game::serialize (serializers type) const {
    switch (type) {
        case serial_full:
        case serial_own:
        case serial_enemy:
            return std::make_shared<json>(json {{"map",     *map->serialize(type)},
                                                {"players", *json_tools::pack_vector<player>(players, type)},
                                                {"rule",    *rule->serialize(type)},
                                                {"next_id", next_id}});
        default:
            break; //TODO exception
    }
}

void game::deserialize (json& package) {
    map->deserialize(package["map"]);
    players = json_tools::unpack_vector<player>(package["players"]); //TODO memory leak (need move constructor)
    rule->deserialize(package["rule"]);
    next_id = package["next_id"].get<int>();
}

game::~game () {
}

int game::get_unique_id () {
    return next_id++;
}

std::shared_ptr<unit> game::get_unit_by_id (int id) {
    // TODO optimizing
    for (int i = 0; i < players->size(); ++i) {
        for (int j = 0; j < (*players)[i]->get_units()->size(); ++j) {
            std::shared_ptr<unit> current = (*(*players)[i]->get_units())[j];
            if (current->get_id() == id) return current;
        }
    }
    return nullptr; //warning/exception
}


#endif //LOGIC_GAME_HPP
