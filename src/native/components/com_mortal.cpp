#include "com_mortal.hpp"

const std::string com_mortal::type = "com_mortal";

std::string com_mortal::get_name () {
    return type;
}

void com_mortal::signal (unit& sender, json& input) {

}

void com_mortal::update (unit& sender) {

}
