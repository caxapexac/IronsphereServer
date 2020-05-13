#ifndef LOGIC_JSON_TOOLS_H
#define LOGIC_JSON_TOOLS_H

#include "../base/third_party_includes.hpp"

class tile;
class abstract_tilemap;
class ihandler;
class base_game;
class game_session;

using json = nlohmann::json;

/// Static helper serialization class
class json_tools {
private:
    json_tools () = default;
public:
    /// Abstract unpackers
    // FIXME after creating new game
    static std::unique_ptr<base_game> unpack_game (json& package);
    // FIXME after creating new tilemap
    static std::unique_ptr<abstract_tilemap> unpack_tilemap (json& package);
    // FIXME after creating new type
    static tile* unpack_tile (json& package); // TODO Спросить Тимура про массив умных указателей

    template<typename T>
    static void pack_vector (const std::vector<T>& vec, json& package);

    template<typename T>
    static std::vector<T> unpack_vector (const json& package);

    template<typename T>
    static void pack_queue (const std::queue<T>& queue, json& package);

    template<typename T>
    static std::queue<T> unpack_queue (const json& package);

    template<typename V>
    static void pack_map (const std::map<std::string, V>& map, json& package);

    template<typename V>
    static void pack_map (const std::map<int, V>& map, json& package);

    template<typename V>
    static void pack_map_of_ptrs (const std::map<std::string, V*>& map, json& package);

    template<typename V>
    static void pack_map_of_ptrs (const std::map<int, V*>& map, json& package);

    template<typename V>
    static std::map<std::string, V> unpack_map (const json& package);

    template<typename V>
    static std::map<int, V> unpack_map (const json& package);

    template<typename V>
    static std::map<std::string, V*> unpack_map_of_ptrs (const json& package);

    template<typename V>
    static std::map<int, V*> unpack_map_of_ptrs (const json& package);

    // TODO make it in logger
    static void print_tilemap(const abstract_tilemap& tilemap);
};

// Really
// I hate cpp's templates
// This shit just can't live in .cpp files
// I lost 4 hours trying to realize this freaking compiler's non-obvious errors
// Cpp and it's obsolete compiler is the most evil legacy shareware in the universe
// Seriously, language with 5-strings-length map search (until c++20 wow, 35 years to include map.contains, gracias)
//   just must die

template<typename T>
void json_tools::pack_vector (const std::vector<T>& vec, json& package) {
    package = json::array();
    for (auto i : vec) {
        json j;
        i.serialize(j);
        package.push_back(j); //TODO remove alloc (use index)
    }
}

template<typename T>
std::vector<T> json_tools::unpack_vector (const json& package) {
    //static_assert(std::is_convertible<T*, iserializable*>::value, "vector class may only contain serializable objects");
    if (package.type() != json::value_t::array) {
        // TODO exception
    }
    std::vector<T> vec = std::vector<T>();
    for (auto& i : package) { //TODO check is it working
        T item;
        json j = i;
        item.deserialize(j); //TODO json constructor
        vec.push_back(item);
    }
    return vec;
}

template<typename T>
void json_tools::pack_queue (const std::queue<T>& queue, json& package) {
    // TODO change to no alloc FIXME
    package = json::array();
    std::queue copy = queue; //copy the original queue to the temporary queue
    while (!copy.empty())
    {
        T item = copy.front();
        json j;
        item.serialize(j);
        package.push_back(j); //TODO remove alloc (use index)
        copy.pop();
    }
}

template<typename T>
std::queue<T> json_tools::unpack_queue (const json& package) {
    //static_assert(std::is_convertible<T*, iserializable*>::value, "vector class may only contain serializable objects");
    if (package.type() != json::value_t::array) {
        // TODO exception
    }
    std::queue<T> queue = std::queue<T>();
    for (auto& i : package) { //TODO check is it working
        T item;
        json j = i;
        item.deserialize(j); //TODO json constructor
        queue.push(item);
    }
    return queue;
}

// TODO there is big chunk of map packers/unpackers and it is not good
template<typename V>
void json_tools::pack_map (const std::map<std::string, V>& map, json& package) {
    package = json::object();
    for (auto const& i : map) {
        json j;
        i.second.serialize(j);
        package[i.first] = j;
    }
}

template<typename V>
void json_tools::pack_map (const std::map<int, V>& map, json& package) {
    package = json::object();
    for (auto const& i : map) {
        json j;
        i.second.serialize(j);
        package[std::to_string(i.first)] = j;
    }
}

template<typename V>
void json_tools::pack_map_of_ptrs (const std::map<std::string, V*>& map, json& package) {
    package = json::object();
    for (auto const& i : map) {
        json j;
        i.second->serialize(j);
        package[i.first] = j;
    }
}

template<typename V>
void json_tools::pack_map_of_ptrs (const std::map<int, V*>& map, json& package) {
    package = json::object();
    for (auto const& i : map) {
        json j;
        i.second->serialize(j);
        package[std::to_string(i.first)] = j;
    }
}

template<typename V>
std::map<std::string, V> json_tools::unpack_map (const json& package) {
    std::map<std::string, V> map = std::map<std::string, V>(); //TODO no alloc
    for (auto const& i : package.items()) {
        V element = V();
        element.deserialize(i.value());
        map[i.key()] = element;
    }
    return map;
}

template<typename V>
std::map<int, V> json_tools::unpack_map (const json& package) {
    std::map<int, V> map = std::map<int, V>(); //TODO no alloc
    for (auto const& i : package.items()) {
        V element = V();
        element.deserialize(i.value());
        map[std::stoi(i.key())] = element;
    }
    return map;
}

template<typename V>
std::map<std::string, V*> json_tools::unpack_map_of_ptrs (const json& package) {
    std::map<std::string, V*> map = std::map<std::string, V*>(); //TODO no alloc
    for (auto const& i : package.items()) {
        V* element = new V();
        element->deserialize(i.value());
        map[i.key()] = element;
    }
    return map;
}

template<typename V>
std::map<int, V*> json_tools::unpack_map_of_ptrs (const json& package) {
    std::map<int, V*> map = std::map<int, V*>(); //TODO no alloc
    for (auto const& i : package.items()) {
        V* element = new V();
        element->deserialize(i.value());
        map[std::stoi(i.key())] = element;
    }
    return map;
}

#endif //LOGIC_JSON_TOOLS_H