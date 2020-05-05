#include "unit_prototype.hpp"
#include "../game/base_game.hpp"

unit_prototype::unit_prototype (base_game& ngame, const std::string& nname) : abstract_unit(ngame) {
    name = nname;
    components = std::map<std::string, icomponent*>();
}

void unit_prototype::serialize (json& package) const {
    abstract_unit::serialize(package);
    package["name"] = name;
    package["components"] = json::array();
    for (const auto& i : components) package["components"].push_back(i.second->get_name());
}

void unit_prototype::deserialize (json& package) {
    abstract_unit::deserialize(package);
    name = package["name"].get<std::string>();
    components = std::map<std::string, icomponent*>();
    for (const auto& i : package["components"]) components[i] = unit_factory::get_component(i);
}

std::string unit_prototype::get_name () {
    return name;
}

void unit_prototype::add_component (const std::string& component_name) {
    components[component_name] = unit_factory::get_component(component_name);
}

void unit_prototype::update (unit* head, int ttl) {
    if (--ttl <= 0) throw std::exception(); //
    for (const auto& i : components) i.second->update(*head);
    if (prototype) prototype->update(head, ttl);
}

void unit_prototype::signal (unit* head, json& input, int ttl) {
    if (--ttl <= 0) throw std::exception(); //
    if (components[input["component"]] != nullptr) {
        components[input["component"]]->signal(*head, input);
    }
    else if (prototype) {
        prototype->signal(head, input, ttl);
    }
    else {
        // There is no component in this unit you want to signal
        // TODO maybe have output from signal
    }
}
