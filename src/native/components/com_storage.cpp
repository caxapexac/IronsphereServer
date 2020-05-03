#include "com_storage.hpp"

const std::string com_storage::type = "com_storage";

std::string com_storage::get_name () {
    return type;
}

void com_storage::signal (unit& sender, json& input) {

}

void com_storage::update (unit& sender) {

}
