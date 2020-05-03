#include "json_tools.hpp"
#include "../game/abstract_game.hpp"
#include "../game/game_realtime.hpp"
#include "../game/game_stepped.hpp"
#include "../field/tilemap_hexagonal.hpp"
#include "../field/tilemap_square.hpp"

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

    if (type == tilemap_hexagonal::type) result = std::make_unique<tilemap_hexagonal>();
    else if (type == tilemap_square::type) result = std::make_unique<tilemap_square>();
    //throw; or log

    result->deserialize(package);
    return result;
}

tile* json_tools::unpack_tile (json& package) {
    std::string type = package["type"];
    tile* result;

    if (type == tile_damage::type) result = new tile_damage();
    else if (type == tile_money::type) result = new tile_money();
    else result = new tile();

    result->deserialize(package);
    return result;
}



