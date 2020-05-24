#include "realtime.hpp"

const std::string& game::realtime::type () const {
    return j_realtime::type;
}

void game::realtime::serialize_concrete_player (int player_uid, json& package) {
    if (player_uid == 0) {
        // TODO it is admin, return all
    }

    if (players[player_uid] == nullptr) {
        throw todo_exception(std::to_string(player_uid) + " player isn't in lobby");
    }

    json_tools::pack_map_int_of_ptrs(players, package[j_abstract_game::players]); // TODO serialize_public

    // TODO Smoke of war
    int team = players[player_uid]->get_team();
    for (const auto& i : units) {
        if (players[i.second->get_player_id()]->get_team() == team) {
            i.second->serialize(package[j_abstract_game::units][std::to_string(i.first)]);
        }
        else {
            i.second->serialize_public(package[j_abstract_game::units][std::to_string(i.first)]);
        }
    }
    // TODO

    // TODO send messages from units (signals queue to animate the game)
}

void game::realtime::update (json& output) {
    for (const auto& i : units) {
        i.second->update(*this);
    }
}