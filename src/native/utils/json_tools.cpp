#include "json_tools.hpp"
#include "../game/base_game.hpp"
#include "../game/game_realtime.hpp"
#include "../game/game_stepped.hpp"
#include "../tilemap/tilemap_hexagonal.hpp"
#include "../tilemap/tilemap_square.hpp"

std::unique_ptr<base_game> json_tools::unpack_game (json& package) {
    std::unique_ptr<base_game> result;

    if  (!package.contains("type")) {
        result = std::make_unique<base_game>();
    }
    else {
        std::string type = package["type"];
        if (type == game_realtime::type) result = std::make_unique<game_realtime>();
        else if (type == game_stepped::type) result = std::make_unique<game_stepped>();
        // else throw; TODO
    }

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
    tile* result;

    if  (!package.contains("type")) {
        result = new tile();
    }
    else {
        std::string type = package["type"];
        if (type == tile_damage::type) result = new tile_damage();
        else if (type == tile_money::type) result = new tile_money();
        // else throw; TODO
    }

    result->deserialize(package);
    return result;
}



