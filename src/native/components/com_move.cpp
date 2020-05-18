#include "com_move.hpp"
#include "../entities/unit.hpp"
#include "../game/base_game.hpp"

const std::string& com_move::type () const {
    return com_move_type;
}

void com_move::setup_prototype (unit_prototype& prototype) {
    prototype.set_parameter("position", vector2<int>(-1, -1));
    prototype.set_parameter("is_moving", false);
    prototype.set_parameter("move_target", vector2<int>(-1, -1));
}

void com_move::command (unit& sender, unit& owner, base_game& context, json& input) {
    throw todo_exception("Nobody can stop me");
}

void com_move::signal (unit& owner, base_game& context, json& input) {
    if (input.contains("is_moving")) {
        bool moving = input["is_moving"].get<bool>();
        owner.set_parameter("is_moving", input["is_moving"].get<bool>());
    }
    if (input.contains("move_target")) {
        vector2<int> move_target = vector2<int>(input["move_target"]);
        owner.set_parameter<vector2<int>>("move_target", move_target);
        vector2<int> position = owner.get_parameter<vector2<int>>("position");
        owner.set_path(context.get_tilemap().get_path(position, move_target));
    }
}

void com_move::update (unit& owner, base_game& context) {
    bool is_moving = owner.get_parameter<bool>("is_moving");
    if (is_moving) {
        vector2<int> move_target = owner.get_parameter<vector2<int>>("move_target");
        vector2<int> position = owner.get_parameter<vector2<int>>("position");

        if (context.get_tilemap().get_distance(position, move_target) <= 1) { // TODO normal float distance and parameters
            owner.set_parameter<bool>("is_moving", false);
            context.get_tilemap()[position].on_unit_enter(owner);
        }
        else {
            std::queue<vector2<int>>& path = owner.get_path();
            if (path.empty()) {
                owner.set_parameter<bool>("is_moving", false);
                context.get_tilemap()[position].on_unit_enter(owner);
                // TODO check if occupied then find another tile without units
            }
            else {
                vector2<int> next_position = path.front();
                path.pop();
                tile& t = context.get_tilemap()[position];
                if (t.get_occupier_id() == owner.get_id()) t.on_unit_exit(owner);
                owner.set_parameter("position", next_position);
                context.get_tilemap()[next_position].on_unit_touch(owner);
                // TODO check occupied (dynamic walls units) and recalculate
            }
        }
    }
}



