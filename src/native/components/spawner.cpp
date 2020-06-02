#include "spawner.hpp"
#include "../entities/unit.hpp"
#include "../game/abstract_game.hpp"

const std::string& com::spawner::type () const {
    return j_spawner::type;
}

void com::spawner::serialize_public (const ent::unit& owner, json& output) const {
    output[j_spawner::production_object] = owner.get_parameter<std::string>(j_spawner::production_object);
}

void com::spawner::setup_prototype (ent::unit_prototype& prototype) {
    prototype.set_parameter(j_spawner::production_object, std::string("solemn"));
    prototype.set_parameter(j_spawner::production_line, 0);
    prototype.set_parameter(j_spawner::production_tikz, 0);
    prototype.set_parameter(j_spawner::production_cost, 10);
    prototype.set_parameter(j_spawner::is_producing, false);
}

void com::spawner::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) {
    // TODO: nihil
}

void com::spawner::signal (ent::unit& owner, game::abstract_game& context, json& input) {
    if (input.contains(j_spawner_signal::production_line)) {
        int com_line = input[j_spawner_signal::production_line].get<int>();
        if (com_line >= 0) {
            owner.set_parameter(j_spawner::production_line, com_line);
            owner.set_parameter(j_spawner::is_producing, (com_line > 0));
        }
    }
}

void com::spawner::update (ent::unit& owner, game::abstract_game& context) {
    bool producing = owner.get_parameter<bool>(j_spawner::is_producing);
    if (producing) {
        int tikz = owner.get_parameter<int>(j_spawner::production_tikz);
        int line = owner.get_parameter<int>(j_spawner::production_line);
        if (tikz == 10) { // FIXME random tikz value?
            int money;
            context.get_player(owner.get_player_id()).get(stts::player_params::money, money);
            money -= 10;
            if (money < 0) {
                return;
            } else {
                context.get_player(owner.get_player_id()).set(stts::player_params::money, money);
            }

            stts::vector2<int> pos = owner.get_parameter<stts::vector2<int>>(j_locationable::position);
            std::vector<stts::vector2<int>> nei = context.get_tilemap().get_neighbours(pos);
            bool spawned = false;
            for (int i = 0; i < nei.size(); ++i)
                if (!context.get_tilemap().get_tile(nei[i]).is_occupied()) {
                    context.get_tilemap().transpose(context.make_unit("solemn", i), nei[i]);
                    spawned = true;
                    break;
                }

            if (spawned) {
                if (line == 0) owner.set_parameter(j_spawner::is_producing, false);
                else owner.set_parameter(j_spawner::production_line, line - 1);
                owner.set_parameter(j_spawner::production_tikz, 0);
            }
        } else {
            owner.set_parameter(j_spawner::production_tikz, tikz + 1);
        }
    }
}