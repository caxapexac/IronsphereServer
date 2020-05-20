#include "realtime.hpp"

const std::string& game::realtime::type () const {
    return realtime_type;
}

bool game::realtime::check_end_game (json& output) {
    return false;
}

void game::realtime::frame () {

}

void game::realtime::calculate_client_data (int player_uid, json& output) {

}

