#include "com_attack.hpp"
#include "../entities/unit.hpp"

std::string com_attack::get_name () {
    return "com_attack";
}

void com_attack::signal (unit& sender, json& input) {
    // From player and unit

}

void com_attack::update (unit& sender) {
    // From serverd
}
