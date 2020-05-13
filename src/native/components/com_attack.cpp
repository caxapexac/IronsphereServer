#include "com_attack.hpp"
#include "../entities/unit.hpp"


const std::string& com_attack::type () const {
    return com_attack_type;
}

void com_attack::setup_prototype (unit_prototype& prototype) {

}

void com_attack::command (unit& sender, unit& owner, base_game& context, json& input) {

}

void com_attack::signal (unit& owner, base_game& context, json& input) {

}

void com_attack::update (unit& owner, base_game& context) {

}




