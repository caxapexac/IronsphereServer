#include "unit_factory.hpp"

int unit_factory::get_id () {
    return next_id++;
}

unit_factory::unit_factory () {
    next_id = 1;
    prototypes = std::map<std::string, unit_prototype*>();
}

void unit_factory::serialize (json& package) const {
    package["next_id"] = next_id;
    for (const auto& i : prototypes) {
        i.second->serialize(package["prototypes"][i.first]);
    }
}

void unit_factory::deserialize (json& package) {
    next_id = package["next_id"].get<int>();
    for (auto& i : package["prototypes"].items()) {
        prototypes[i.key()] = new unit_prototype(i.value());
    }
}

unit_prototype* unit_factory::get_prototype (const std::string& prototype_name) {
    if (prototypes[prototype_name] == nullptr) {
        throw todo_exception("Yo n**igga you can't get this stuff cuz it gonna blow your mind in segfault");
    }
    return prototypes[prototype_name];
}

void unit_factory::set_prototype (const std::string& prototype_name, unit_prototype* prototype) {
    if (prototypes[prototype_name] != nullptr) {
        throw todo_exception("Double kill");
    }
    prototypes[prototype_name] = prototype; // FIXME memory leak
}

unit* unit_factory::make_unit (const std::string& prototype_name, int player_uid) {
    if (prototypes[prototype_name] == nullptr) {
        throw todo_exception("This freaking prototype wasn't literally exist. Im not torch just sweet throwed");
    }
    return new unit(get_prototype(prototype_name), player_uid, get_id());
}


