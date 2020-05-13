#include "unit.hpp"

unit::unit (unit_prototype* nprototype, int nplayer_id, int nid) : abstract_unit(nprototype) {
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

void unit::update (base_game& context) {
    if (prototype) prototype->update(*this, context); //FIXME
}

void unit::signal (base_game& context, json& input) {
    if (prototype) prototype->signal(*this, context, input); //FIXME
}

void unit::command (unit& sender, base_game& context, json& input) {
    if (prototype) prototype->command(sender, *this, context, input); //FIXME
}

std::queue<vector2<int>>& unit::get_path () {
    return parameters.get_path();
}

void unit::set_path (std::queue<vector2<int>> data) {
    parameters.set_path(std::move(data));
}
