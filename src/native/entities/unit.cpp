#include "unit.hpp"

#include <utility>

unit::unit (abstract_game& nstorage, unit_prototype* nprototype, int nplayer_id, int nid) : abstract_unit(nstorage) {
    prototype = nprototype;
    player_id = nplayer_id;
    id = nid;
}

void unit::serialize (json& package) const {
    abstract_unit::serialize(package);
    package["player_id"] = player_id;
    package["id"] = id;
}

void unit::deserialize (json& package) {
    abstract_unit::deserialize(package);
    id = package["id"].get<int>();
    player_id = package["player_id"].get<int>();
}

int unit::get_player_id () {
    return player_id;
}

int unit::get_id () {
    return id;
}

void unit::update () {
    prototype->update(this);
}

void unit::signal (json& input) {
    prototype->signal(this, input);
}

std::vector<vector2<int>>& unit::get_path () {
    return parameters.get_path();
}

void unit::set_path (std::vector<vector2<int>> data) {
    parameters.set_path(std::move(data));
}

