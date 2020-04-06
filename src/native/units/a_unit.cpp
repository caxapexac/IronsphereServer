#include "a_unit.hpp"

a_unit::a_unit (game_storage& nstorage, int nplayer_id, int nid) : storage(nstorage), player_id(nplayer_id), id(nid) {

}

a_unit::a_unit (game_storage& nstorage, json& package) : storage(nstorage) {
    a_unit::deserialize(package);
}

a_unit::a_unit (const a_unit& copy) : storage(copy.storage), player_id(copy.player_id) {
    id = storage.players->at(player_id).get_id();
}

a_unit& a_unit::operator= (const a_unit& copy) {
    if (this != &copy) {
        // storage = copy.storage; TODO this won't work (maybe use pointer)
        player_id = copy.player_id;
        id = storage.players->at(player_id).get_id();
    }
    return *this;
}

void a_unit::serialize (json& package, serializers type) const {
    package["player_id"] = player_id;
    package["id"] = id;
}

void a_unit::deserialize (json& package) {
    // TODO checking
    // TODO troubles with storage (need reference, maybe through constructor)
    player_id = package["player_id"].get<int>();
    id = package["id"].get<int>();
}

void a_unit::dispose () {
    //TODO for pool
}

int a_unit::get_player_id () {
    return player_id;
}

int a_unit::get_id () {
    return id;
}

void a_unit::update () {
    // TODO optimize
    if (get_effectable()) get_effectable()->update();
    if (get_mortal()) get_mortal()->update();
    if (get_placeable()) get_placeable()->update();
    if (get_storageable()) get_storageable()->update();
    if (get_movable()) get_movable()->update();
}

void a_unit::signal (json& input, json& output) {
    std::string type = input["type"];
    a_ability* ability = nullptr;
    if (type == "effectable") ability = get_effectable();
    else if (type == "mortal") ability = get_mortal();
    else if (type == "placeable") ability = get_placeable();
    else if (type == "storageable") ability = get_storageable();
    else if (type == "movable") ability = get_movable();
    else;//throw; or log

    if (ability) ability->signal(input, output);
    else;//TODO maybe log info (no ability)
}


