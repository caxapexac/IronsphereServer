#include "com_move.hpp"
#include "../entities/unit.hpp"
#include "../game/base_game.hpp"

const std::string& com_move::type () const {
    return com_move_type;
}

void com_move::setup_prototype (unit_prototype& prototype) {
    prototype.set_parameter("position", vector2<int>(0, 0));
    prototype.set_parameter("is_moving", false);
    prototype.set_parameter("move_target", vector2<int>(0, 0));
}

void com_move::command (unit& sender, unit& owner, base_game& context, json& input) {
    throw todo_exception("Nobody can stop me");
}

void com_move::signal (unit& owner, base_game& context, json& input) {
    if (input.contains("is_moving")) {
        owner.get_parameter<bool>("is_moving") = input["is_moving"].get<bool>();
    }
    if (input.contains("move_target")) {
        vector2<int> move_target = owner.get_parameter<vector2<int>>("move_target");
    }
}

void com_move::update (unit& owner, base_game& context) {
    bool is_moving = owner.get_parameter<bool>("is_moving");
    if (is_moving) {
        vector2<int> move_target = owner.get_parameter<vector2<int>>("move_target");
        vector2<int> position = owner.get_parameter<vector2<int>>("position");

        if (context.get_tilemap())

        std::queue<vector2<int>>& path = owner.get_path();

    }

    if (path.empty()) {
        owner.set_parameter("move_state", "stand");
        // TODO check if occupied then find another tile without units
    }
    else {
        owner.set_parameter("move_state", "move");
        vector2<int> next_position = path.front();
        path.pop();
        // const tile* next_tile = context.get_tile(next_position); TODO maybe check occupied and recalculate
        // and use "target" for it
        owner.set_parameter("position", next_position);
    }

}



