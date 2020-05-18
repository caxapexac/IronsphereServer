#include "state_play.hpp"
#include "../lobby/game_session.hpp"

state_play::state_play (game_session& context) : session(context) { }

const std::string& state_play::type () const {
    return state_play_type;
}

void state_play::load (json& input, json& output) {
    output = {{"error", "[state_play.load] wrong transition"}};
}

void state_play::save (json& output) {
    output = {{"error", "[state_play.save] wrong transition"}};
}

void state_play::join (json& input, json& output) {
    output = {{"error", "[state_play.join] wrong transition"}};
}

void state_play::quit (json& input, json& output) {
    output = {{"warning", "[state_play.quit] connection lost. You can rejoin"}};
}

void state_play::play (json& output) {
    output = {{"error", "[state_play.play] wrong transition"}};
}

void state_play::pause (json& output) {
    session.transition_to(std::make_unique<state_pause>(session));
    output = {{"success", "[state_play.pause] The game was paused"}};
}

void state_play::stop (json& output) {
    session.transition_to(std::make_unique<state_choose>(session));
    output = {{"success", "[state_play.stop] The game was stopped"}};
}

void state_play::setup (json& input, json& output) {
    output = {{"error", "[state_play.setup] wrong transition"}};
}

void state_play::update (json& output) {
    session.game->update(output);
    if (session.game->check_end_game(output["records"])) {
        session.transition_to(std::make_unique<state_choose>(session));
    }
}

void state_play::signal (json& input, json& output) {
    // TODO maybe try catch with success/error response to client
    session.game->signal(input, output);
}
