#include "abstract_game.hpp"

abstract_game::abstract_game () : factory(unit_factory(*this)) {
    units = std::map<int, unit*>();
    players = std::map<int, player*>();
}

void abstract_game::serialize (json& package) const {
    factory.serialize(package["factory"]);
    //json_tools::pack_map(units, package["units"]); FIXME
    //json_tools::pack_map(players, package["players"]); FIXME
    field->serialize(package["field"]);
}

void abstract_game::deserialize (json& package) {
    factory.deserialize(package["factory"]);
    //units = json_tools::unpack_map<int, unit*>(package["units"]); FIXME
    // players = json_tools::unpack_map<int, player*>(package["players"]); FIXME
    field = json_tools::unpack_tilemap(package["field"]);
}

void abstract_game::get_field (json& output) {
    field->serialize(output);
}

unit& abstract_game::make_unit (const std::string& prototype_name, int player_id) {
    unit* result = factory.make_unit(prototype_name, player_id);
    units[result->get_id()] = result;
    return *units[result->get_id()];
    // TODO simplify
}

unit_prototype* abstract_game::get_prototype (const std::string& prototype_name) {
    return factory.get_prototype(prototype_name);
}

unit* abstract_game::get_unit (int id) {
    return units[id];
}

player* abstract_game::get_player (int uid) {
    return players[uid];
}

tile* abstract_game::get_tile (const vector2<int>& position) {
    return field->get_tile(position);
}

void abstract_game::update (json& output) {
    frame();
    // TODO send messages from frame (signals queue)
    for (const auto& i : players) {
        calculate_client_data(i.first, output["players_data"][std::to_string(i.first)]);
    }
}

void abstract_game::signal (json& input, json& output) {
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
        target->signal(input["command"]);
        output = {{"success", "[game.signal] Your command was sent"}};
    }
}

