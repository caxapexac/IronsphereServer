#include "com_attack.hpp"
#include "../entities/unit.hpp"

const std::string com_attack::type = "com_attack";

std::string com_attack::get_name () {
    return type;
}

void com_attack::signal (unit& sender, json& input) {
    // From player and unit

}

void com_attack::update (unit& sender) {
    // From serverd
}
