#include "playing.hpp"
#include "choosing.hpp"
#include "holding.hpp"
#include "../online/session.hpp"


states::playing::playing (online::session& context) : session(context) { }

const std::string& states::playing::type () const {
    return states::playing_type;
}

void states::playing::load (json& input, json& output) {
    output[out_signal::error] = "[state_play.load] wrong transition";
}

void states::playing::save (json& output) {
    output[out_signal::error] = "[state_play.save] wrong transition";
}

void states::playing::join (int player_uid, json& output) {
    output[out_signal::error] = "[state_play.join] wrong transition";
}

void states::playing::quit (int player_uid, json& output) {
    output[out_signal::error] = "[state_play.quit] connection lost. You can rejoin";
}

void states::playing::play (json& output) {
    output[out_signal::error] = "[state_play.play] wrong transition";
}

void states::playing::pause (json& output) {
    session.transition_to(std::make_unique<states::holding>(session));
    output[out_signal::success] = "[state_play.pause] The game was paused";
}

void states::playing::stop (json& output) {
    session.transition_to(std::make_unique<states::choosing>(session));
    output[out_signal::success] = "[state_play.stop] The game was stopped";
}

void states::playing::setup (json& input, json& output) {
    output[out_signal::error] = "[state_play.setup] wrong transition";
}

void states::playing::update (json& output) {
    session.game->update(output);
    if (session.game->check_end_game(output["records"])) {
        OBSOLETE // TODO maybe finishing state
        session.transition_to(std::make_unique<states::choosing>(session));
    }
}

void states::playing::signal (json& input, json& output) {
    // TODO maybe try catch with success/error response to client
    session.game->signal(input, output);
}

