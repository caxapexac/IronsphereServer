#include "json_tools.hpp"
#include "../game/abstract_game.hpp"
#include "../game/game_realtime.hpp"
#include "../game/game_stepped.hpp"
#include "../structs_field/tilemap_hexagonal.hpp"
#include "../structs_field/tilemap_square.hpp"

std::unique_ptr<abstract_game> json_tools::unpack_game (json& package) {
    std::string type = package["type"]; //TODO enum
    std::unique_ptr<abstract_game> result;

    if (type == game_realtime::type) result = std::make_unique<game_realtime>();
    else if (type == game_stepped::type) result = std::make_unique<game_stepped>();
    else return nullptr; //throw; or log

    result->deserialize(package);
    return result;
}

std::unique_ptr<abstract_tilemap> json_tools::unpack_tilemap (json& package) {
    std::string type = package["type"];
    std::unique_ptr<abstract_tilemap> result;

    if (type == tilemap_hexagonal::type) result = std::make_unique<tilemap_hexagonal>(package);
    else if (type == tilemap_square::type) result = std::make_unique<tilemap_square>(package);
    //throw; or log

    result->deserialize(package);
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

template<typename K, typename V>
void json_tools::pack_map (const std::map<K, V>& map, json& package, serializers type) {
    package = {};
    for (auto const& i : map) {
        json j;
        i.second.serialize(j, type);
        package[i.first] = j; //TODO check
    }
}

template<typename K, typename V>
std::map<K, V> json_tools::unpack_map (const json& package) {
    std::map<K, V> map = std::map<K, V>(); //TODO no alloc
    for (auto const& i : package.items()) {
        V element = V();
        element.deserialize(i.value());
        map[i.key()] = element; //TODO check
    }
    return map;
}


