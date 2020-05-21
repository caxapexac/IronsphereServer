#include "unit_prototype.hpp"
#include "../game/base_game.hpp"


ent::unit_prototype::unit_prototype (const std::string& nname, unit_prototype* nprototype) {
    prototype = nprototype;
    name = nname;
    components = std::map<std::string, icomponent*>();
}

ent::unit_prototype::unit_prototype (json& package) {
    deserialize(package);
}

void ent::unit_prototype::serialize (json& package) const {
    parameter_map::serialize(package);
    if (prototype) prototype->serialize(package["prototype"]);
    package["name"] = name;
    package["components"] = json::array();
    for (const auto& key : components) package["components"].push_back(key.second->type());
}

void ent::unit_prototype::deserialize (json& package) {
    parameter_map::deserialize(package);
    if (package.contains("prototype")) prototype = new unit_prototype(package["prototype"]);
    else prototype = nullptr; // TODO optimize
    name = package["name"].get<std::string>();
    components = std::map<std::string, icomponent*>();
    for (const auto& componentName : package["components"]) components[componentName] = com::component_storage::get_component(componentName);
}

const std::string& ent::unit_prototype::type () const {
    return name;
}

void ent::unit_prototype::add_component (const std::string& component_name) {
    icomponent* component = com::component_storage::get_component(component_name);
    component->setup_prototype(*this);
    components[component_name] = component;
}

void ent::unit_prototype::get_cache_public (const ent::unit& head, json& output) const {
    for (const auto& i : components) i.second->serialize_public(head, output);
}

void ent::unit_prototype::update (ent::unit& head, game::base_game& game, int ttl) {
    if (--ttl <= 0) throw todo_exception("I don't know how but you have unit with 128 layers of inheritance");
    for (const auto& i : components) i.second->update(head, game);
    if (prototype) prototype->update(head, game, ttl);
}

void ent::unit_prototype::signal (ent::unit& head, game::base_game& game, json& input, int ttl) {
    if (--ttl <= 0) throw todo_exception("I don't know how but you have unit with 128 layers of inheritance");
    if (components[input[in_game_signal::command_data::component]] != nullptr) {
        components[input[in_game_signal::command_data::component]]->signal(head, game, input);
    }
    else if (prototype) {
        prototype->signal(head, game, input, ttl);
    }
    else {
        // There is no component in this unit you want to signal
        // TODO maybe have output from signal
    }
}

void ent::unit_prototype::command (ent::unit& sender, ent::unit& head, game::base_game& context, json& input, int ttl) {
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




