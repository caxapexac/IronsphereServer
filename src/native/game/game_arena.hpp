#ifndef LOGIC_GAME_ARENA_HPP
#define LOGIC_GAME_ARENA_HPP

#include "player.hpp"
#include "../field/tilemap.hpp"
#include "../base/interfaces.hpp"
#include "../structs/transform.hpp"
#include "../other/logger.hpp"
#include "../game/game_rules.hpp"


//TODO template<int P, typename T> //Where P is player count, T : game_rules
class game_arena : public iserializable {
private:
    //static const int player_count = P; //TODO make something not so rubbish-like
    static std::shared_ptr<game_arena> instance; //TODO no singleton cuz there are more than one sessions on the server

    std::shared_ptr<tilemap> map;
    std::shared_ptr<std::vector<std::shared_ptr<player>>> players; //TODO player 0 holds neutral objects, TODO remove second shared_ptr
    std::shared_ptr<game_rules> rule; //TODO T rule;
    int next_id; //TODO maybe into player (optimizing search speed)

public:
    static std::shared_ptr<game_arena> get ();

    explicit game_arena ();
    game_arena (const game_arena& copy);
    game_arena& operator= (const game_arena& copy);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;

    ~game_arena () override;
    int get_unique_id ();
    std::shared_ptr<unit> get_unit_by_id (int id);
};

std::shared_ptr<game_arena> game_arena::instance = nullptr;

std::shared_ptr<game_arena> game_arena::get () {
    if (instance == nullptr) instance = std::make_shared<game_arena>();
    return instance;
}

game_arena::game_arena () {
    next_id = 1;
    //this->map = std::make_shared<tilemap>(seed);
    this->players = std::make_shared<std::vector<std::shared_ptr<player>>>();
    //choreographer::init(this->map);
    //TODO
}

game_arena::game_arena (const game_arena& copy) {
    //TODO
    // next_id = get_unique_id(); //?
}

game_arena& game_arena::operator= (const game_arena& copy) {
    if (this != &copy) {
        //this = game(copy); //TODO ^^^
    }
    return *this;
}

void game_arena::serialize (json& package, serializers type) const {
    switch (type) {
        case serial_full:
        case serial_static:
        case serial_dynamic:
            return std::make_shared<json>(json {{"map",     *map->serialize(type)},
                                                {"players", *json_tools::pack_vector<player>(players, type)},
                                                {"rule",    *rule->serialize(type)},
                                                {"next_id", next_id}});
        default:
            break; //TODO exception
    }
}

void game_arena::deserialize (json& package) {
    map->deserialize(package["map"]);
    players = json_tools::unpack_vector<player>(package["players"]); //TODO memory leak (need move constructor)
    rule->deserialize(package["rule"]);
    next_id = package["next_id"].get<int>();
}

game_arena::~game_arena () {
}

int game_arena::get_unique_id () {
    return next_id++;
}

std::shared_ptr<unit> game_arena::get_unit_by_id (int id) {
    // TODO optimizing
    for (int i = 0; i < players->size(); ++i) {
        for (int j = 0; j < (*players)[i]->get_units()->size(); ++j) {
            std::shared_ptr<unit> current = (*(*players)[i]->get_units())[j];
            if (current->get_id() == id) return current;
        }
    }
    return nullptr; //warning/exception
}


#endif //LOGIC_GAME_ARENA_HPP
