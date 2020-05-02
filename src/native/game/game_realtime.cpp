#include "game_realtime.hpp"

const std::string game_realtime::type = "realtime";

bool game_realtime::check_end_game (json& output) {
    return false;
}

void game_realtime::frame () {

}

void game_realtime::calculate_client_data (int player_uid, json& output) {

}
