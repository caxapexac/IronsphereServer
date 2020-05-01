#include "json_tools.hpp"
#include <memory>
#include "../structs/game_storage.hpp"
#include "../game_strategies/abstract_strategy.hpp"
#include "../game_strategies/strategy_realtime.hpp"
#include "../game_strategies/strategy_stepped.hpp"
#include "../game_states/state_play.hpp"
#include "../game_states/state_choose.hpp"
#include "../game_states/state_pause.hpp"
#include "../game_states/state_finish.hpp"
#include "../structs_field/tilemap_hexagonal.hpp"
#include "../structs_field/tilemap_square.hpp"

std::unique_ptr<abstract_strategy> json_tools::unpack_strategy (json& package) {
    std::string type = package["type"]; //TODO enum
    if (type == "realtime") return std::make_unique<strategy_realtime>(package);
    else if (type == "stepped") return std::make_unique<strategy_stepped>(package);
    //throw; or log
    return nullptr;
}

std::unique_ptr<abstract_state> json_tools::unpack_state (json& package, game_session& session) {
    if (package == "choose") return std::make_unique<state_choose>(session);
    else if (package == "play") return std::make_unique<state_play>(session);
    else if (package == "pause") return std::make_unique<state_pause>(session);
    else if (package == "finish") return std::make_unique<state_finish>(session);
    //throw; or log
    return nullptr;
}

std::unique_ptr<abstract_tilemap> json_tools::unpack_tilemap (json& package) {
    std::string type = package["type"];
    if (type == "hexagonal") return std::make_unique<tilemap_hexagonal>(package);
    else if (type == "square") return std::make_unique<tilemap_square>(package);
    //throw; or log
    return nullptr;
}

tile* json_tools::unpack_tile (json& package) {
    if (!package.contains("type")) return new tile(package);
    std::string type = package["type"];
    if (type == "money") return new tile_money(package);
    else if (type == "damage") return new tile_damage(package);
    //throw; or log
    return nullptr;
}

template<typename T>
void json_tools::pack_vector (const std::vector<T>& vec, json& package, serializers type) {
    package = json::array();
    for (auto i : vec) {
        json j;
        i.serialize(j, type);
        package.push_back(j); //TODO remove alloc (use index)
    }
}

template<typename T>
std::vector<T> json_tools::unpack_vector (const json& package) {
    static_assert(std::is_convertible<T*, iserializable*>::value, "vector class may only contain serializable objects");
    if (package.type() != json::value_t::array) {
        // TODO exception
    }
    std::vector<T> vec = std::vector<T>();
    for (auto& i : package) { //TODO check is it working
        T item;
        item.deserialize(i); //TODO json constructor
        vec.push_back(item);
    }
    return vec;
}

template<typename T>
void json_tools::pack_map (const std::map<std::string, T>& map, json& package, serializers type) {
    package = {};
    for (auto const& i : map) {
        json j;
        i.second.serialize(j, type);
        package[i.first] = j; //TODO check
    }
}

template<typename T>
std::map<std::string, T> json_tools::unpack_map (const json& package) {
    std::map<std::string, T> map = std::map<std::string, T>(); //TODO no alloc
    for (auto const& i : package.items()) {
        T element = T();
        element.deserialize(i.value());
        map[i.key()] = element; //TODO check
    }
    return map;
}

