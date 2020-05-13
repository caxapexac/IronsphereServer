#include "abstract_unit.hpp"
#include "../game/base_game.hpp"

abstract_unit::abstract_unit (unit_prototype* nprototype) {
    prototype = nprototype;
    parameters = parameter_map();
}

void abstract_unit::set_prototype (unit_prototype* nprototype) {
    delete nprototype; // TODO will crash if prototype was lightweight
    prototype = nprototype;
}

void abstract_unit::serialize (json& package) const {
    if (prototype) prototype->serialize(package["prototype"]);
    parameters.serialize(package["parameters"]);
}

void abstract_unit::deserialize (json& package) {
    if (package.contains("prototype")) set_prototype(new unit_prototype(package["prototype"])); // TODO fix memory leak
    else set_prototype(nullptr);
    parameters.deserialize(package["parameters"]);
}

const std::string& abstract_unit::type () const {
    if (prototype) return prototype->type();
    return constants::empty_string;
}

