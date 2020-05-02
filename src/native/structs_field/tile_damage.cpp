#include "tile_damage.hpp"

const std::string tile_damage::type = "damage";

tile_damage::tile_damage (int ndamage, float nheight) : tile(nheight), damage(ndamage) {}

void tile_damage::serialize (json& package) const {
    tile::serialize(package);
    package["type"] = "damage";
    package["damage"] = damage;
}

void tile_damage::deserialize (json& package) {
    tile::deserialize(package);
    damage = package["damage"].get<int>();
}


