#include "com_move.hpp"

const std::string com_move::type = "com_moving";

std::string com_move::get_name () {
    return type;
}

void com_move::signal (unit& sender, json& input) {

}

void com_move::update (unit& sender) {

}
