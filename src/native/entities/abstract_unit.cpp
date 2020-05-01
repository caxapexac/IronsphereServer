#include "abstract_unit.hpp"
#include "../structs/game_storage.hpp"

abstract_unit::abstract_unit (game_storage& nstorage) : storage(nstorage) {
    prototype = nullptr;
    parameters = parameter_map();
}

void abstract_unit::serialize (json& package, serializers type) const {
    package["prototype"] = prototype->get_name();
    parameters.serialize(package["parameters"], serial_save);
}

void abstract_unit::deserialize (json& package) {
    prototype = storage.factory.get_prototype(package["prototype"]); //TODO bad
    parameters.deserialize(package["parameters"]);
}
