#include "game_storage.hpp"

game_storage::game_storage (json& package) {
    deserialize(package);
}

game_storage::game_storage (std::unique_ptr<a_tilemap> nmap, std::unique_ptr<std::vector<player>> nplayers) {
    map = std::move(nmap);
    players = std::move(nplayers);
}

void game_storage::serialize (json& package, serializers type) const {
    map->serialize(package["map"], type);
    json_tools::pack_vector<player>(*players, package["players"], type);
}

void game_storage::deserialize (json& package) {
    map = json_tools::unpack_tilemap(package["map"]);
    players = json_tools::unpack_vector<player>(package["players"]);
}


