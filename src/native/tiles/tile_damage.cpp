#include "tile_damage.hpp"

tile_damage::tile_damage (float nheight, int ndamage) : tile(nheight), damage(ndamage) {}

void tile_damage::serialize (json& package) const {
    tile::serialize(package);
    package["damage"] = damage;
}

void tile_damage::deserialize (json& package) {
    tile::deserialize(package);
    damage = package["damage"].get<int>();
}

const std::string& tile_damage::type () const {
    return tile_damage_type;
}

void tile_damage::on_unit_enter (unit& sender) {
    tile::on_unit_enter(sender);
}

void tile_damage::on_unit_touch (unit& sender) const {
    tile::on_unit_touch(sender);
}

void tile_damage::on_unit_exit (unit& sender) {
    tile::on_unit_exit(sender);
}


