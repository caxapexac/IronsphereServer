#include "json_tools.hpp"
#include "../game/base_game.hpp"
#include "../game/game_realtime.hpp"
#include "../game/game_stepped.hpp"
#include "../tilemap/abstract_tilemap.hpp"
#include "../tilemap/tilemap_hexagonal.hpp"
#include "../tilemap/tilemap_square.hpp"

std::unique_ptr<base_game> json_tools::unpack_game (json& package) {
    if (!package.contains("type")) {
        throw todo_exception("Add here more checks please");
    }
    std::unique_ptr<base_game> result;

    std::string type = package["type"];
    if (type == base_game_type) result = std::make_unique<base_game>();
    else if (type == game_realtime_type) result = std::make_unique<game_realtime>();
    else if (type == game_stepped_type) result = std::make_unique<game_stepped>();
    else throw todo_exception("Unknown game type");

    result->deserialize(package);
    return result;
}

std::unique_ptr<abstract_tilemap> json_tools::unpack_tilemap (json& package) {
    if (!package.contains("type")) {
        throw todo_exception("Add here more checks please");
    }
    std::unique_ptr<abstract_tilemap> result;

    std::string type = package["type"];
    if (type == tilemap_hexagonal_type) result = std::make_unique<tilemap_hexagonal>();
    else if (type == tilemap_square_type) result = std::make_unique<tilemap_square>();
    else throw todo_exception("Unknown tilemap type");

    result->deserialize(package);
    return result;
}

tile* json_tools::unpack_tile (json& package) {
    if (!package.contains("type")) {
        throw todo_exception("Add here more checks please");
    }
    tile* result;

    std::string type = package["type"];
    if (type == tile_type) result = new tile();
    else if (type == tile_damage_type) result = new tile_damage(0, 0);
    else if (type == tile_money_type) result = new tile_money(0, 0);
    else throw todo_exception("Unknown tile type");

    result->deserialize(package);
    return result;
}

void json_tools::print_tilemap (abstract_tilemap& tilemap) {
    std::cout << "[abstract_tilemap] " << tilemap.scale.x << "x" << tilemap.scale.y << std::endl;
    for (int ny = 0; ny < tilemap.scale.y; ++ny) {
        for (int nx = 0; nx < tilemap.scale.x; ++nx) {
            tile& t = tilemap.get_tile(nx, ny);
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

