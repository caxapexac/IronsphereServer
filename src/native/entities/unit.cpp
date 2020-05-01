#include "unit.hpp"

unit::unit (game_storage& nstorage, unit_prototype* nprototype, int nplayer_id, int nid) : abstract_unit(nstorage) {
    set_prototype(nprototype);
    player_id = nplayer_id;
    id = nid;
}

void unit::serialize (json& package, serializers type) const {
    abstract_unit::serialize(package, type);
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

