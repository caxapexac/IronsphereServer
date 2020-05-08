#include "abstract_unit.hpp"
#include "../game/base_game.hpp"

abstract_unit::abstract_unit (base_game& ngame) : game(ngame) {
    prototype = nullptr;
    parameters = parameter_map();
}

void abstract_unit::serialize (json& package) const {
    if (prototype) package["prototype"] = prototype->get_name();
    parameters.serialize(package["parameters"]);
}

void abstract_unit::deserialize (json& package) {
    if (package.contains("prototype")) prototype = game.get_prototype(package["prototype"]);
    parameters.deserialize(package["parameters"]);
}
