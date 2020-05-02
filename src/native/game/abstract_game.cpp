#include "abstract_game.hpp"

abstract_game::abstract_game () : factory(unit_factory(*this)) {
    units = std::map<int, unit>();
    players = std::map<int, player>();
}

void abstract_game::serialize (json& package, serializers type) const {
    factory.serialize(package["factory"], serial_save);
    json_tools::pack_map(units, package["units"], serial_save);
    json_tools::pack_map(players, package["players"], serial_save);
    field->serialize(package["field"], type);
}

void abstract_game::deserialize (json& package) {
    factory.deserialize(package["factory"]);
    units = json_tools::unpack_map<int, unit>(package["units"]);
    players = json_tools::unpack_map<int, player>(package["players"]);
    field = json_tools::unpack_tilemap(package["field"]);
}
