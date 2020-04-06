#ifndef LOGIC_JSON_TOOLS_H
#define LOGIC_JSON_TOOLS_H

#include "json.hpp"

class a_unit;
class tile;
class a_tilemap;
class a_strategy;
class a_state;
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
    static std::unique_ptr<a_strategy> unpack_strategy (json& package);
    // FIXME after creating new state
    static std::unique_ptr<a_state> unpack_state (json& package, game_session& session);
    // FIXME after creating new unit
    static std::shared_ptr<a_unit> unpack_unit (json& package, game_storage& storage);
    // FIXME after creating new effect
    static std::shared_ptr<a_effect> unpack_effect (json& package);
    // FIXME after creating new tilemap
    static std::unique_ptr<a_tilemap> unpack_tilemap (json& package);
    // FIXME after creating new type
    static tile* unpack_tile (json& package); // TODO Спросить Тимура про массив умных указателей

    template<typename T>
    static void pack_vector (const std::vector<T>& vec, json& package, serializers type);

    //TODO T : iserializable not good
    template<typename T>
    static std::unique_ptr<std::vector<T>> unpack_vector (const json& package);

    // template<typename T> //TODO T : iserializable not good. How to pass interface iserializable instead of template?
    // static std::shared_ptr<json> pack_vector(const std::shared_ptr<std::vector<std::shared_ptr<T>>>& vec, serializers type);
    //
    // template<typename T>
    // static std::shared_ptr<json> pack_vector(const std::vector<std::shared_ptr<T>>& vec, serializers type);
    //


};

#endif //LOGIC_JSON_TOOLS_H