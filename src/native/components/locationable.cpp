#include "locationable.hpp"
#include "../entities/unit.hpp"
#include "../game/abstract_game.hpp"

const std::string& com::locationable::type () const {
    return j_move::type;
}

void com::locationable::serialize_public (const ent::unit& owner, json& output) const {
    owner.get_parameter<stts::vector2<int>>(j_locationable::position).serialize(output[j_locationable::position]);
}

void com::locationable::setup_prototype (ent::unit_prototype& prototype) {
    prototype.set_parameter(j_locationable::position, stts::vector2<int>(-1, -1));
}

void com::locationable::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) {}

void com::locationable::signal (ent::unit& owner, game::abstract_game& context, json& input) {}

void com::locationable::update (ent::unit& owner, game::abstract_game& context) {}