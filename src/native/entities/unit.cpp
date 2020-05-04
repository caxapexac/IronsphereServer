#include "unit.hpp"

#include <utility>

unit::unit (base_game& ngame, unit_prototype* nprototype, int nplayer_id, int nid) : abstract_unit(ngame) {
    prototype = nprototype; // TODO prototype can't be null cuz it will crash if we forget to init it
    // TODO I think it shold be (storage + json) constructor
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
    if (prototype) prototype->update(this); //FIXME
}

void unit::signal (json& input) {
    if (prototype) prototype->signal(this, input); //FIXME
}

std::vector<vector2<int>>& unit::get_path () {
    return parameters.get_path();
}

void unit::set_path (std::vector<vector2<int>> data) {
    parameters.set_path(std::move(data));
}

