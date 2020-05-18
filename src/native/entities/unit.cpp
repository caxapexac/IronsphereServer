#include "unit.hpp"

unit::unit (unit_prototype* nprototype, int nplayer_id, int nid){
    prototype = nprototype;
    player_id = nplayer_id;
    id = nid;
}

void unit::serialize (json& package) const {
    parameter_map::serialize(package);
    if (prototype) prototype->serialize(package["prototype"]);
    package["player_id"] = player_id;
    package["id"] = id;
}

void unit::deserialize (json& package) {
    parameter_map::deserialize(package);
    if (package.contains("prototype")) prototype = new unit_prototype(package["prototype"]);
    else prototype = nullptr; // TODO optimize
    id = package["id"].get<int>();
    player_id = package["player_id"].get<int>();
}

void unit::set_prototype (unit_prototype* nprototype) {
    delete nprototype; // TODO will crash if prototype was lightweight
    prototype = nprototype;
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
