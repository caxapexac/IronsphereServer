#include "unit.hpp"

ent::unit::unit (unit_prototype* nprototype, int nplayer_id, int nid) {
    prototype = nprototype;
    player_id = nplayer_id;
    id = nid;
    is_dirty = true;
}

void ent::unit::serialize (json& package) const {
    ensure_cache();
    package = cache;
}

void ent::unit::deserialize (json& package) {
    parameter_map::deserialize(package);
    if (package.contains("prototype")) prototype = new unit_prototype(package["prototype"]);
    else prototype = nullptr; // TODO optimize
    id = package["id"].get<int>();
    player_id = package["player_id"].get<int>();
}

void ent::unit::serialize_public (json& package) const {
    ensure_cache();
    package = cache_public;
}

void ent::unit::set_dirty () {
    is_dirty = true;
}

void ent::unit::set_prototype (unit_prototype* nprototype) {
    delete nprototype; // TODO will crash if prototype was lightweight
    prototype = nprototype;
}

int ent::unit::get_player_id () {
    return player_id;
}

int ent::unit::get_id () {
    return id;
}

void ent::unit::update (game::base_game& context) {
    if (prototype) prototype->update(*this, context); //FIXME
}

void ent::unit::signal (game::base_game& context, json& input) {
    if (prototype) prototype->signal(*this, context, input); //FIXME
}

void ent::unit::command (unit& sender, game::base_game& context, json& input) {
    if (prototype) prototype->command(sender, *this, context, input); //FIXME
}

void ent::unit::ensure_cache () const {
    if (is_dirty) {
        cache = {};
        cache["player_id"] = player_id;
        cache["id"] = id;
        cache_public = cache;

        parameter_map::serialize(cache);
        if (prototype) {
            prototype->serialize(cache["prototype"]);
            prototype->get_cache_public(*this, cache_public); //FIXME
        }
        is_dirty = false;
    }
}








