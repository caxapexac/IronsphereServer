#include "holding.hpp"
#include "choosing.hpp"
#include "playing.hpp"
#include "../online/session.hpp"


states::holding::holding (online::session& context) : session(context) { }

const std::string& states::holding::type () const {
    return states::holding_type;
}

void states::holding::load (json& input, json& output) {
    output[out_signal::error] = "[state_pause.load] wrong transition";
}

void states::holding::save (json& output) {
    session.game->serialize(output[out_game_save::game]);
    output[out_signal::success] = "[state_pause.join] wrong transition";
}

void states::holding::join (int player_uid, json& output) {
    output[out_signal::error] = "[state_pause.join] wrong transition";
}

void states::holding::quit (int player_uid, json& output) {
    output[out_signal::error] = "[state_pause.quit] connection lost. You can rejoin";
}

void states::holding::play (json& output) {
    session.transition_to(std::make_unique<playing>(session));
    output[out_signal::success] = "[state_pause.play] The game was continued";
}

void states::holding::pause (json& output) {
    output[out_signal::error] = "[state_pause.pause] wrong transition";
}

void states::holding::stop (json& output) {
    session.transition_to(std::make_unique<states::choosing>(session));
    output[out_signal::success] = "[state_pause.stop] The game was stopped";
}

void states::holding::setup (json& input, json& output) {
    output[out_signal::error] = "[state_pause.setup] wrong transition";
}

void states::holding::update (json& output) {
    // Nothing
}

void states::holding::signal (json& input, json& output) {
    output[out_signal::error] = "[state_pause.signal] wrong transition";
}



