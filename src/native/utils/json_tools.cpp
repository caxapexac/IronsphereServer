#include "json_tools.hpp"
#include "../game/base_game.hpp"
#include "../game/realtime.hpp"
#include "../game/stepped.hpp"
#include "../tilemap/abstract_tilemap.hpp"
#include "../tilemap/hexagonal.hpp"
#include "../tilemap/square.hpp"

std::unique_ptr<game::base_game> nlohmann::json_tools::unpack_game (json& package) {
    if (!package.contains("type")) {
        throw todo_exception("Add here more checks please");
    }
    std::unique_ptr<game::base_game> result;

    std::string type = package["type"];
    if (type == game::base_game_type) result = std::make_unique<game::base_game>();
    else if (type == game::realtime_type) result = std::make_unique<game::realtime>();
    else if (type == game::stepped_type) result = std::make_unique<game::stepped>();
    else throw todo_exception("Unknown game type");

    result->deserialize(package);
    return result;
}

std::unique_ptr<tilemap::abstract_tilemap> nlohmann::json_tools::unpack_tilemap (json& package) {
    if (!package.contains("type")) {
        throw todo_exception("Add here more checks please");
    }
    std::unique_ptr<tilemap::abstract_tilemap> result;

    std::string type = package["type"];
    if (type == tilemap::hexagonal_type) result = std::make_unique<tilemap::hexagonal>();
    else if (type == tilemap::square_type) result = std::make_unique<tilemap::square>();
    else throw todo_exception("Unknown tilemap type");

    result->deserialize(package);
    return result;
}

tile::base_tile* nlohmann::json_tools::unpack_tile (json& package) {
    if (!package.contains("type")) {
        throw todo_exception("Add here more checks please");
    }
    tile::base_tile* result;

    std::string type = package["type"];
    if (type == tile::tile_type) result = new tile::base_tile();
    else if (type == tile::damage_type) result = new tile::damage_dealer(0, 0);
    else if (type == tile::money_type) result = new tile::money_dealer(0, 0);
    else throw todo_exception("Unknown tile type");

    result->deserialize(package);
    return result;
}

void nlohmann::json_tools::print_tilemap (tilemap::abstract_tilemap& tilemap) {
    std::cout << "[abstract_tilemap] " << tilemap.scale.x << "x" << tilemap.scale.y << std::endl;
    for (int ny = 0; ny < tilemap.scale.y; ++ny) {
        for (int nx = 0; nx < tilemap.scale.x; ++nx) {
            tile::base_tile& t = tilemap.get_tile(nx, ny);
            if (t.is_occupied()) {
                 std::cout << t.get_occupier_id() << "\t";
            }
            else {
                std::cout << ".\t";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

