#include "game_session.hpp"

game_session::game_session () {
    players_id = std::vector<int>();
    storage = nullptr;
    strategy = nullptr;
    transition_to(std::make_unique<state_choose>(*this));
}

bool game_session::is_empty () {
    return players_id.empty();
}

abstract_state& game_session::get_state () {
    return *state;
}

int game_session::get_player_index (int player_id) {
    for (int i = 0; i < players_id.size(); ++i) {
        if (players_id[i] == player_id) return i;
    }
    return -1; //TODO const
}

void game_session::transition_to (std::unique_ptr<abstract_state> nstate) {
    state = std::move(nstate);
    //TODO log?
}

void game_session::serialize (json& package, serializers type) const {
    // TODO maybe remove (logic in the state)
    switch (type) {
        case serial_info:
            // TODO players_id
            if (state != nullptr) state->serialize(package["state"], type);
            if (strategy != nullptr) strategy->serialize(package["strategy"], type);
            break;
        case serial_gameplay:
            if (state != nullptr) state->serialize(package["state"], type);
            if (storage != nullptr) storage->serialize(package["storage"], type);
            break;
        case serial_save:
            if (state != nullptr) state->serialize(package["state"], type);
            if (strategy != nullptr) strategy->serialize(package["strategy"], type);
            if (storage != nullptr) storage->serialize(package["storage"], type);
            break;
    }
}

void game_session::deserialize (json& package) {
    state = package.contains("state") ? json_tools::unpack_state(package["state"], *this) : std::make_unique<state_choose>(*this);
    strategy = package.contains("strategy") ? json_tools::unpack_strategy(package["strategy"]) : nullptr;
    storage = package.contains("storage") ? std::make_unique<game_storage>(package["storage"]) : nullptr;
}

