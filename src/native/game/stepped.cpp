#include "stepped.hpp"

const std::string& game::stepped::type () const {
    return game::stepped_type;
}

bool game::stepped::check_end_game (json& output) {
    return false;
}

void game::stepped::frame () {

}

void game::stepped::calculate_client_data (int player_uid, json& output) {

}


