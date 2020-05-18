#include "unit_prototype.hpp"
#include "../game/base_game.hpp"



unit_prototype::unit_prototype (const std::string& nname, unit_prototype* nprototype) {
    prototype = nprototype;
    name = nname;
    components = std::map<std::string, icomponent*>();
}

unit_prototype::unit_prototype (json& package) {
    deserialize(package);
}

void unit_prototype::serialize (json& package) const {
    parameter_map::serialize(package);
    if (prototype) prototype->serialize(package["prototype"]);
    package["name"] = name;
    package["components"] = json::array();
    for (const auto& key : components) package["components"].push_back(key.second->type());
}

void unit_prototype::deserialize (json& package) {
    parameter_map::deserialize(package);
    if (package.contains("prototype")) prototype = new unit_prototype(package["prototype"]);
    else prototype = nullptr; // TODO optimize
    name = package["name"].get<std::string>();
    components = std::map<std::string, icomponent*>();
    for (const auto& componentName : package["components"]) components[componentName] = component_storage::get_component(componentName);
}

const std::string& unit_prototype::type () const {
    return name;
}

void unit_prototype::add_component (const std::string& component_name) {
    icomponent* component = component_storage::get_component(component_name);
    component->setup_prototype(*this);
    components[component_name] = component;
}

void unit_prototype::update (unit& head, base_game& game, int ttl) {
    if (--ttl <= 0) throw todo_exception("I don't know how but you have unit with 128 layers of inheritance");
    for (const auto& i : components) i.second->update(head, game);
    if (prototype) prototype->update(head, game, ttl);
}

void unit_prototype::signal (unit& head, base_game& game, json& input, int ttl) {
    if (--ttl <= 0) throw todo_exception("I don't know how but you have unit with 128 layers of inheritance");
    if (components[input["component"]] != nullptr) {
        components[input["component"]]->signal(head, game, input);
    }
    else if (prototype) {
        prototype->signal(head, game, input, ttl);
    }
    else {
        // There is no component in this unit you want to signal
        // TODO maybe have output from signal
    }
}

void unit_prototype::command (unit& sender, unit& head, base_game& context, json& input, int ttl) {
    if (--ttl <= 0) throw todo_exception("I don't know how but you have unit with 128 layers of inheritance");
    if (components[input["component"]] != nullptr) {
        components[input["component"]]->command(sender, head, context, input);
    }
    else if (prototype) {
        prototype->command(sender, head, context, input, ttl);
    }
    else {
        // There is no component in this unit you want to signal
        // TODO maybe have output from signal
    }
}


