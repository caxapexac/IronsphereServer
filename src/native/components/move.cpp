#include "move.hpp"
#include "../entities/unit.hpp"
#include "../game/abstract_game.hpp"

const std::string& com::move::type () const {
    return j_move::type;
}

void com::move::serialize_public (const ent::unit& owner, json& output) const {
    owner.get_parameter<stts::vector2<int>>(j_move::position).serialize(output[j_move::position]);
    output[j_move::is_moving] = owner.get_parameter<bool>(j_move::is_moving);
    // TODO p_position (float) and p_tile_position (int)
}

void com::move::setup_prototype (ent::unit_prototype& prototype) {
    prototype.set_parameter(j_move::position, stts::vector2<int>(-1, -1));
    prototype.set_parameter(j_move::is_moving, false);
    prototype.set_parameter(j_move::move_target, stts::vector2<int>(-1, -1));
    prototype.set_parameter(j_move::move_path, std::list<stts::vector2<int>>());
}

void com::move::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) {
    throw unimplemented_exception("com::move::command was not implemented");
}

void com::move::signal (ent::unit& owner, game::abstract_game& context, json& input) {
    if (input.contains(j_move::is_moving)) {
        bool moving = input[j_move::is_moving].get<bool>();
        owner.set_parameter(j_move::is_moving, input[j_move::is_moving].get<bool>());
    }
    if (input.contains(j_move::move_target)) {
        stts::vector2<int> move_target = stts::vector2<int>(input[j_move::move_target]);
        owner.set_parameter(j_move::move_target, move_target);
        stts::vector2<int> position = owner.get_parameter<stts::vector2<int>>(j_move::position);
        owner.set_parameter(j_move::move_path, context.get_tilemap().get_path(position, move_target));
    }
}

void com::move::update (ent::unit& owner, game::abstract_game& context) {
    bool is_moving = owner.get_parameter<bool>(j_move::is_moving);
    if (is_moving) {
        stts::vector2<int> move_target = owner.get_parameter<stts::vector2<int>>(j_move::move_target);
        stts::vector2<int> position = owner.get_parameter<stts::vector2<int>>(j_move::position);

        if (context.get_tilemap().get_distance(position, move_target) <= 1) { // TODO normal float distance and parameters
            owner.set_parameter<bool>(j_move::is_moving, false);
            context.get_tilemap()[position].on_unit_enter(owner);
        }
        else {
            // TODO is it fast enough?
            std::list<stts::vector2<int>> path = owner.get_parameter<std::list<stts::vector2<int>>>(j_move::move_path);
            if (path.empty()) {
                owner.set_parameter<bool>(j_move::is_moving, false);
                context.get_tilemap()[position].on_unit_enter(owner);
                // TODO check if occupied then find another tile without units
            }
            else {
                stts::vector2<int> next_position = path.front();
                path.pop_front();
                owner.set_parameter<std::list<stts::vector2<int>>>(j_move::move_path, path);
                tile::base_tile& t = context.get_tilemap()[position];
                if (t.get_occupier_id() == owner.get_id()) t.on_unit_exit(owner);
                owner.set_parameter(j_move::position, next_position);
                context.get_tilemap()[next_position].on_unit_touch(owner);
                // TODO check occupied (dynamic walls units) and recalculate
            }
        }
    }
}





