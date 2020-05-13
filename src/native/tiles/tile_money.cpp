#include "tile_money.hpp"

tile_money::tile_money (float nheight, int nmoney) : tile(nheight), money(nmoney) {}

void tile_money::serialize (json& package) const {
    tile::serialize(package);
    package["money"] = money;
}

void tile_money::deserialize (json& package) {
    tile::deserialize(package);
    money = package["money"].get<int>();
}

const std::string& tile_money::type () const {
    return tile_money_type;
}

void tile_money::on_unit_enter (unit& sender) {
    tile::on_unit_enter(sender);
}

void tile_money::on_unit_touch (unit& sender) {
    tile::on_unit_touch(sender);
}

void tile_money::on_unit_exit (unit& sender) {
    tile::on_unit_exit(sender);
}



