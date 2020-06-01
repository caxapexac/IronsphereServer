#include "mortal.hpp"
#include "../entities/unit.hpp"
#include "../game/abstract_game.hpp"

const std::string& com::mortal::type () const {
    return j_mortal::type;
}

void com::mortal::serialize_public (const ent::unit& owner, json& package) const {
    package[j_mortal::hp] = owner.get_parameter<float>(j_mortal::hp);
    package[j_mortal::armor] = owner.get_parameter<float>(j_mortal::armor);
    package[j_mortal::is_alive] = owner.get_parameter<bool>(j_mortal::is_alive);
}

void com::mortal::setup_prototype (ent::unit_prototype& prototype) {
    prototype.set_parameter(j_mortal::armor, 0.0);
    prototype.set_parameter(j_mortal::hp, 1.0);
    prototype.set_parameter(j_mortal::evading_chance, 0.0);
    prototype.set_parameter(j_mortal::is_alive, true);
}

void com::mortal::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) {
    float damage = input[j_attack::damage].get<float>();
    srand(owner.get_id());
    float evade = (rand() % 100) / 100;
    if (evade > owner.get_parameter<float>(j_mortal::evading_chance)) {
        float armor = owner.get_parameter<float>(j_mortal::armor);
        float hp = owner.get_parameter<float>(j_mortal::hp);
        if (armor - damage >= 0) {
            armor -= damage;
        } else {
            hp += armor - damage;
            armor = 0.0;
        }
        owner.set_parameter(j_mortal::armor, armor);
        owner.set_parameter(j_mortal::hp, hp);
        if (hp <= 0) owner.set_parameter(j_mortal::is_alive, false);
    }
}

void com::mortal::signal (ent::unit& owner, game::abstract_game& context, json& input) {
    if (input.contains(j_mortal_signal::armor)) {
        owner.set_parameter(j_mortal::armor, input[j_mortal_signal::armor].get<float>());
    }
    if (input.contains(j_mortal_signal::hp)) {
        owner.set_parameter(j_mortal::hp, input[j_mortal_signal::hp].get<float>());
    }
    if (input.contains(j_mortal_signal::evading_chance)) {
        owner.set_parameter(j_mortal::evading_chance, input[j_mortal_signal::evading_chance].get<float>());
    }
}

void com::mortal::update (ent::unit& owner, game::abstract_game& context) {
    // TODO: regeneration?
}








