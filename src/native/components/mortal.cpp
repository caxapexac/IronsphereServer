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
    prototype.set_parameter(j_mortal::armor, (float) 10.0);
    prototype.set_parameter(j_mortal::hp, (float) 10.0);
    prototype.set_parameter(j_mortal::evading_chance, (float) 0.25);
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
        if (hp <= 0) {
            owner.set_parameter(j_mortal::is_alive, false);
            context.get_tilemap().get_tile(owner.get_parameter<stts::vector2<int>>(j_locationable::position)).on_unit_exit(owner);
        }
    }
}

void com::mortal::signal (ent::unit& owner, game::abstract_game& context, json& input) {
    // FIXME: nothing??
}

void com::mortal::update (ent::unit& owner, game::abstract_game& context) {
    // TODO: regeneration?
}








