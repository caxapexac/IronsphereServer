#include "tile_money.hpp"

const std::string tile_money::type = "money";

tile_money::tile_money (int nmoney, float nheight) : tile(nheight), money(nmoney) {}

void tile_money::serialize (json& package) const {
    tile::serialize(package);
    package["type"] = type;
    package["money"] = money;
}

void tile_money::deserialize (json& package) {
    tile::deserialize(package);
    money = package["money"].get<int>();
}



