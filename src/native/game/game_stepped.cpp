#include "game_stepped.hpp"

const std::string& game_stepped::type () const {
    return game_stepped_type;
}

bool game_stepped::check_end_game (json& output) {
    return false;
}

void game_stepped::frame () {

}

void game_stepped::calculate_client_data (int player_uid, json& output) {

}


