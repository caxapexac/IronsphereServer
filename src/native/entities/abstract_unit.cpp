#include "abstract_unit.hpp"
#include "../game/abstract_game.hpp"

abstract_unit::abstract_unit (abstract_game& nstorage) : storage(nstorage) {
    prototype = nullptr;
    parameters = parameter_map();
}

void abstract_unit::serialize (json& package) const {
    package["prototype"] = prototype->get_name();
    parameters.serialize(package["parameters"]);
}

void abstract_unit::deserialize (json& package) {
    prototype = storage.get_prototype(package["prototype"]); //TODO bad
    parameters.deserialize(package["parameters"]);
}
