#include "damage_dealer.hpp"
#include "base_tile.hpp"

tile::damage_dealer::damage_dealer (float nheight, int ndamage) : tile::base_tile(nheight), damage(ndamage) { }

tile::damage_dealer::damage_dealer (json& package) {
    damage_dealer::deserialize(package);
}

void tile::damage_dealer::serialize (json& package) const {
    base_tile::serialize(package);
    package[j_damage_dealer::damage] = damage;
}

void tile::damage_dealer::deserialize (json& package) {
    base_tile::deserialize(package);
    damage = package[j_damage_dealer::damage].get<int>();
}

const std::string& tile::damage_dealer::type () const {
    return j_damage_dealer::type;
}

void tile::damage_dealer::on_unit_enter (ent::unit& sender) {
    base_tile::on_unit_enter(sender);
}

void tile::damage_dealer::on_unit_touch (ent::unit& sender) {
    base_tile::on_unit_touch(sender);
}

void tile::damage_dealer::on_unit_exit (ent::unit& sender) {
    base_tile::on_unit_exit(sender);
}



