#include "attack.hpp"
#include "../entities/unit.hpp"
#include "../game/base_game.hpp"

const std::string& com::attack::type () const {
    return attack_type;
}

void com::attack::serialize_public (const ent::unit& owner, json& package) const {

}

void com::attack::setup_prototype (ent::unit_prototype& prototype) {

}

void com::attack::command (ent::unit& sender, ent::unit& owner, game::base_game& context, json& input) {

}

void com::attack::signal (ent::unit& owner, game::base_game& context, json& input) {

}

void com::attack::update (ent::unit& owner, game::base_game& context) {

}





