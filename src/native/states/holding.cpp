#include "holding.hpp"
#include "choosing.hpp"
#include "playing.hpp"
#include "../online/session.hpp"


states::holding::holding (online::session& context) : session(context) { }

const std::string& states::holding::type () const {
    return j_holding::type;
}

void states::holding::game_update (json& output) {
    // Nothing
}

void states::holding::game_load (json& input, json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::holding::game_save (json& output) {
    session.game->serialize(output[out_game_save::game]);
    output[out_signal::success] = LOCATED("Game saved");
}

void states::holding::game_join (int player_uid, json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::holding::game_quit (int player_uid, json& output) {
    output[out_signal::error] = LOCATED("Connection lost. You can rejoin");
}

void states::holding::game_play (json& output) {
    session.transition_to(std::make_unique<playing>(session));
    output[out_signal::success] = LOCATED("The game was continued");
}

void states::holding::game_pause (json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::holding::game_stop (json& output) {
    session.transition_to(std::make_unique<states::choosing>(session));
    output[out_signal::success] = LOCATED("The game was stopped");
}

void states::holding::game_setup (json& input, json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::holding::game_signal (json& input, json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}



