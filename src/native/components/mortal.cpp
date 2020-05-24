#include "mortal.hpp"

const std::string& com::mortal::type () const {
    return j_mortal::type;
}

void com::mortal::serialize_public (const ent::unit& owner, json& package) const {

}

void com::mortal::setup_prototype (ent::unit_prototype& prototype) {

}

void com::mortal::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) {

}

void com::mortal::signal (ent::unit& owner, game::abstract_game& context, json& input) {

}

void com::mortal::update (ent::unit& owner, game::abstract_game& context) {

}








