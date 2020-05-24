#include "storage.hpp"


const std::string& com::storage::type () const {
    return j_storage::type;
}

void com::storage::serialize_public (const ent::unit& owner, json& package) const {

}

void com::storage::setup_prototype (ent::unit_prototype& prototype) {

}

void com::storage::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) {

}

void com::storage::signal (ent::unit& owner, game::abstract_game& context, json& input) {

}

void com::storage::update (ent::unit& owner, game::abstract_game& context) {

}








