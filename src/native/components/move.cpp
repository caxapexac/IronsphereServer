#include "move.hpp"
#include "../entities/unit.hpp"
#include "../game/base_game.hpp"

const std::string& com::move::type () const {
    return com::move_type;
}

void com::move::serialize_public (const ent::unit& owner, json& output) const {
    owner.get_parameter<stts::vector2<int>>(p::position).serialize(output[p::position]);
    output[p::is_moving] = owner.get_parameter<bool>(p::is_moving);
    // TODO p_position (float) and p_tile_position (int)
}

void com::move::setup_prototype (ent::unit_prototype& prototype) {
    prototype.set_parameter(p::position, stts::vector2<int>(-1, -1));
    prototype.set_parameter(p::is_moving, false);
    prototype.set_parameter(p::move_target, stts::vector2<int>(-1, -1));
    prototype.set_parameter(p::move_path, std::list<stts::vector2<int>>());
}

void com::move::command (ent::unit& sender, ent::unit& owner, game::base_game& context, json& input) {
    throw todo_exception("Nobody can stop me");
}

void com::move::signal (ent::unit& owner, game::base_game& context, json& input) {
    if (input.contains(p::is_moving)) {
        bool moving = input[p::is_moving].get<bool>();
        owner.set_parameter(p::is_moving, input[p::is_moving].get<bool>());
    }
    if (input.contains(p::move_target)) {
        stts::vector2<int> move_target = stts::vector2<int>(input[p::move_target]);
        owner.set_parameter(p::move_target, move_target);
        stts::vector2<int> position = owner.get_parameter<stts::vector2<int>>(p::position);
        owner.set_parameter(p::move_path, context.get_tilemap().get_path(position, move_target));
    }
}

void com::move::update (ent::unit& owner, game::base_game& context) {
    bool is_moving = owner.get_parameter<bool>(p::is_moving);
    if (is_moving) {
        stts::vector2<int> move_target = owner.get_parameter<stts::vector2<int>>(p::move_target);
        stts::vector2<int> position = owner.get_parameter<stts::vector2<int>>(p::position);

        if (context.get_tilemap().get_distance(position, move_target) <= 1) { // TODO normal float distance and parameters
            owner.set_parameter<bool>(p::is_moving, false);
            context.get_tilemap()[position].on_unit_enter(owner);
        }
        else {
            // TODO is it fast enough?
            std::list<stts::vector2<int>> path = owner.get_parameter<std::list<stts::vector2<int>>>(p::move_path);
            if (path.empty()) {
                owner.set_parameter<bool>(p::is_moving, false);
                context.get_tilemap()[position].on_unit_enter(owner);
                // TODO check if occupied then find another tile without units
            }
            else {
                stts::vector2<int> next_position = path.front();
                path.pop_front();
                owner.set_parameter<std::list<stts::vector2<int>>>(p::move_path, path);
                tile::base_tile& t = context.get_tilemap()[position];
                if (t.get_occupier_id() == owner.get_id()) t.on_unit_exit(owner);
                owner.set_parameter(p::position, next_position);
                context.get_tilemap()[next_position].on_unit_touch(owner);
                // TODO check occupied (dynamic walls units) and recalculate
            }
        }
    }
}





