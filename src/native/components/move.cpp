#include "move.hpp"
#include "../entities/unit.hpp"
#include "../game/base_game.hpp"

// TODO
const std::string p_position = "position";
const std::string p_is_moving = "is_moving";
const std::string p_move_target = "move_target";
const std::string p_move_path = "move_path";

const std::string& com::move::type () const {
    return com::move_type;
}

void com::move::setup_prototype (ent::unit_prototype& prototype) {
    prototype.set_parameter(p_position, stts::vector2<int>(-1, -1));
    prototype.set_parameter(p_is_moving, false);
    prototype.set_parameter(p_move_target, stts::vector2<int>(-1, -1));
    prototype.set_parameter(p_move_path, std::list<stts::vector2<int>>());
}

void com::move::command (ent::unit& sender, ent::unit& owner, game::base_game& context, json& input) {
    throw todo_exception("Nobody can stop me");
}

void com::move::signal (ent::unit& owner, game::base_game& context, json& input) {
    if (input.contains(p_is_moving)) {
        bool moving = input[p_is_moving].get<bool>();
        owner.set_parameter(p_is_moving, input[p_is_moving].get<bool>());
    }
    if (input.contains(p_move_target)) {
        stts::vector2<int> move_target = stts::vector2<int>(input[p_move_target]);
        owner.set_parameter<stts::vector2<int>>(p_move_target, move_target);
        stts::vector2<int> position = owner.get_parameter<stts::vector2<int>>(p_position);
        owner.set_parameter(p_move_target, context.get_tilemap().get_path(position, move_target));
    }
}

void com::move::update (ent::unit& owner, game::base_game& context) {
    bool is_moving = owner.get_parameter<bool>(p_is_moving);
    if (is_moving) {
        stts::vector2<int> move_target = owner.get_parameter<stts::vector2<int>>(p_move_target);
        stts::vector2<int> position = owner.get_parameter<stts::vector2<int>>(p_position);

        if (context.get_tilemap().get_distance(position, move_target) <= 1) { // TODO normal float distance and parameters
            owner.set_parameter<bool>(p_is_moving, false);
            context.get_tilemap()[position].on_unit_enter(owner);
        }
        else {
            // TODO is it fast enough?
            std::list<stts::vector2<int>> path = owner.get_parameter<std::list<stts::vector2<int>>>(p_move_path);
            if (path.empty()) {
                owner.set_parameter<bool>(p_is_moving, false);
                context.get_tilemap()[position].on_unit_enter(owner);
                // TODO check if occupied then find another tile without units
            }
            else {
                stts::vector2<int> next_position = path.front();
                path.pop_front();
                tile::base_tile& t = context.get_tilemap()[position];
                if (t.get_occupier_id() == owner.get_id()) t.on_unit_exit(owner);
                owner.set_parameter(p_position, next_position);
                context.get_tilemap()[next_position].on_unit_touch(owner);
                // TODO check occupied (dynamic walls units) and recalculate
            }
        }
    }
}



