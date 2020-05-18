#include "base_game.hpp"

base_game::base_game () {
    factory = unit_factory();
    units = std::map<int, unit*>();
    players = std::map<int, player*>();
    tilemap = nullptr; // TODO create tilemap
}

void base_game::serialize (json& package) const {
    factory.serialize(package["factory"]);
    json_tools::pack_map_int_of_ptrs(units, package["units"]);
    json_tools::pack_map_int_of_ptrs(players, package["players"]);
    if (tilemap) tilemap->serialize(package["tilemap"]);
}

void base_game::deserialize (json& package) {
    factory.deserialize(package["factory"]);
    for (const auto& i : package["units"].items()) {
        unit* item = new unit();
        item->deserialize(i.value());
        units[std::stoi(i.key())] = item; //TODO very bad (need to check at least)
    }
    for (const auto& i : package["players"].items()) {
        player* item = new player();
        item->deserialize(i.value());
        players[std::stoi(i.key())] = item; //TODO very bad (need to check at least)
    }
    if (package.contains("tilemap")) tilemap = json_tools::unpack_tilemap(package["tilemap"]);
}

const std::string& base_game::type () const {
    return base_game_type;
}

void base_game::get_static_content (json& output) {
    tilemap->serialize(output);
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
        throw todo_exception("wrong json");
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
        target->signal(*this, input["command"]);
        output = {{"success", "[game.signal] Your command was sent"}};
    }
}

unit& base_game::make_unit (const std::string& prototype_name, int player_uid) {
    unit* result = factory.make_unit(prototype_name, player_uid);
    units[result->get_id()] = result;
    return *units[result->get_id()];
    // TODO simplify
}

unit_prototype* base_game::get_prototype (const std::string& prototype_name) {
    return factory.get_prototype(prototype_name);
}

void base_game::set_prototype (unit_prototype* prototype) {
    factory.set_prototype(prototype);
}

unit* base_game::get_unit (int id) {
    return units[id];
}

player& base_game::get_player (int uid) {
    return *players[uid];
}

void base_game::set_player (int uid, player* nplayer) {
    if (players[uid] != nullptr) throw todo_exception("Player with this uid is already exist");
    // TODO maybe replace instead of exception
    players[uid] = nplayer;
}

abstract_tilemap& base_game::get_tilemap () {
    return *tilemap;
}

void base_game::set_tilemap (std::unique_ptr<abstract_tilemap> ntilemap) {
    tilemap = std::move(ntilemap);
}

void base_game::frame () {
    for (const auto& i : units) {
        i.second->update(*this);
    }
}

void base_game::calculate_client_data(int player_uid, json& output) {
    //TODO
}








