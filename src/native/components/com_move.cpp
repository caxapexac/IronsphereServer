#include "com_move.hpp"
#include "../entities/unit.hpp"
#include "../game/base_game.hpp"

const std::string& com_move::type () const {
    return com_move_type;
}

void com_move::setup_prototype (unit_prototype& prototype) {

}

void com_move::command (unit& sender, unit& owner, base_game& context, json& input) {
    if (input["type"] == "") {

    }
}

void com_move::signal (unit& owner, base_game& context, json& input) {
    if (input["type"] == "move_to") {
        vector2<int> target = vector2<int>(input["position"]);
        vector2<int> current_position;
        if (!owner.get_parameter("position", current_position)) throw todo_exception("No unit position");
        std::queue<vector2<int>> path = context.get_tilemap().get_path(current_position, target);
        owner.set_path(path);
        owner.set_parameter("target", target);
    }
    //else if (input["type"] == "move_to") {
    //
    //}
}

void com_move::update (unit& owner, base_game& context) {
    //std::string state;
    //if (!owner.get_parameter("move_state", state)) state = "stand";

    std::queue<vector2<int>>& path = owner.get_path();
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



