#ifndef LOGIC_JSON_TOOLS_H
#define LOGIC_JSON_TOOLS_H

#include "json.hpp"

class a_unit;
class tile;
class abstract_tilemap;
class abstract_strategy;
class abstract_state;
class a_effect;
class game_storage;
class game_session;

using json = nlohmann::json;

enum serializers {
    serial_save, //For saving
    serial_info, //For getting lobby information
    serial_gameplay //For
};

/// Static helper serialization class
class json_tools {
private:
    json_tools () = default;
public:
    /// Abstract unpackers
    // FIXME after creating new strategy
    static std::unique_ptr<abstract_strategy> unpack_strategy (json& package);
    // FIXME after creating new state
    static std::unique_ptr<abstract_state> unpack_state (json& package, game_session& session);
    // FIXME after creating new tilemap
    static std::unique_ptr<abstract_tilemap> unpack_tilemap (json& package);
    // FIXME after creating new type
    static tile* unpack_tile (json& package); // TODO Спросить Тимура про массив умных указателей

    template<typename T>
    static void pack_vector (const std::vector<T>& vec, json& package, serializers type);

    template<typename T>
    static std::vector<T> unpack_vector (const json& package);

    template<typename T>
    static void pack_map (const std::map<std::string, T>& map, json& package, serializers type);

    template<typename T>
    static std::map<std::string, T> unpack_map (const json& package);
};

#endif //LOGIC_JSON_TOOLS_H