#include "unit_factory.hpp"
#include "../components/com_attack.hpp"
#include "../components/com_mortal.hpp"
#include "../components/com_moving.hpp"
#include "../components/com_storage.hpp"

// TODO add new components
// TODO use static get_name instead of constant strings
std::map<std::string, icomponent*> unit_factory::components = {{"com_attack",  new com_attack()},
                                                               {"com_mortal",  new com_mortal()},
                                                               {"com_moving",  new com_moving()},
                                                               {"com_storage", new com_storage()}};

int unit_factory::get_id () {
    return next_id++;
}

unit_factory::unit_factory (abstract_game& nstorage) : storage(nstorage) {
    next_id = 1;
    prototypes = std::map<std::string, unit_prototype*>();
}

void unit_factory::serialize (json& package) const {
    //json_tools::pack_map(prototypes, package["prototypes"]); FIXME
}

void unit_factory::deserialize (json& package) {
    for (auto& i : package) {
        auto* element = get_prototype(i["name"]);
        element->deserialize(i);
    }
}

icomponent* unit_factory::get_component (const std::string& component_name) {
    if (components[component_name] == nullptr) throw std::exception(); //TODO cooler exceptions
    return components[component_name];
}

unit_prototype* unit_factory::get_prototype (const std::string& prototype_name) {
    if (prototypes[prototype_name] == nullptr) {
        prototypes[prototype_name] = new unit_prototype(storage, prototype_name); //TODO fix memory leak
    }
    return prototypes[prototype_name];
}

unit* unit_factory::make_unit (const std::string& prototype_name, int player_uid) {
    // TODO check json
    // and throw exception
    return new unit(storage, get_prototype(prototype_name), player_uid, get_id());
}

