#include "game_storage.hpp"

game_storage::game_storage () : factory(unit_factory(*this)) { }

void game_storage::serialize (json& package, serializers type) const {
    factory.serialize(package["factory"], serial_save);
    map->serialize(package["map"], type);
    json_tools::pack_vector<player>(players, package["players"], type);
}

void game_storage::deserialize (json& package) {
    factory.deserialize(package["factory"]);
    map = json_tools::unpack_tilemap(package["map"]);
    players = json_tools::unpack_vector<player>(package["players"]);
}


