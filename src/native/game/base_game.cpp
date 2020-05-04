#include "base_game.hpp"

base_game::base_game () : factory(unit_factory(*this)) {
    units = std::map<int, unit*>();
    players = std::map<int, player*>();
    // TODO create field
}

void base_game::serialize (json& package) const {
    factory.serialize(package["factory"]);
    json_tools::pack_map_of_ptrs(units, package["units"]);
    json_tools::pack_map_of_ptrs(players, package["players"]);
    field->serialize(package["field"]);
}

void base_game::deserialize (json& package) {
    factory.deserialize(package["factory"]);
    for (const auto& i : package["units"].items()) {
        unit* item = new unit(*this);
        item->deserialize(i.value());
        units[std::stoi(i.key())] = item; //TODO very bad (need to check at least)
    }
    for (const auto& i : package["players"].items()) {
        player* item = new player();
        item->deserialize(i.value());
        players[std::stoi(i.key())] = item; //TODO very bad (need to check at least)
    }
    field = json_tools::unpack_tilemap(package["field"]);
}

void base_game::get_field (json& output) {
    field->serialize(output);
}

unit& base_game::make_unit (const std::string& prototype_name, int player_id) {
    unit* result = factory.make_unit(prototype_name, player_id);
    units[result->get_id()] = result;
    return *units[result->get_id()];
    // TODO simplify
}

unit_prototype* base_game::get_prototype (const std::string& prototype_name) {
    return factory.get_prototype(prototype_name);
}

unit* base_game::get_unit (int id) {
    return units[id];
}

player* base_game::get_player (int uid) {
    return players[uid];
}

const tile* base_game::get_tile (const vector2<int>& position) {
    return field->get_tile(position);
}

void base_game::update (json& output) {
    frame();
    // TODO send messages from frame (signals queue)
    for (const auto& i : players) {
        calculate_client_data(i.first, output["players_data"][std::to_string(i.first)]);
    }
}

bool base_game::check_end_game (json& output) {
    return false; //TODO
}

void base_game::signal (json& input, json& output) {
    if (input["selected_units"].type() != json::value_t::array) {
        // TODO exception
        // TODO more checkings
    }

    int sender_uid = input["player_uid"].get<int>();

    for (auto& i : input["selected_units"]) { //TODO check is it working
        int id = i.get<int>(); // TODO type checking
        unit* target = get_unit(id);
        if (target == nullptr) {
            output = {{"error", "[game.signal] Unit with this id doesn't exist check your internet connection"}};
            continue;
        }
        if (target->get_player_id() != sender_uid) {
            output = {{"error", "[game.signal] This unit is not yours"}};
            continue;
        }
        // TODO is command normal
        target->signal(input["command"]);
        output = {{"success", "[game.signal] Your command was sent"}};
    }
}

void base_game::frame () {
    //TODO
}

void base_game::calculate_client_data(int player_uid, json& output) {
    //TODO
}


