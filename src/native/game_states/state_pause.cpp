#include "state_pause.hpp"
#include "../lobby/game_session.hpp"

state_pause::state_pause (game_session& context) : abstract_state(context) { }

void state_pause::join (json& input, json& output) {
    output = {{"error", "[pause.join] wrong transition"}};
}

void state_pause::quit (json& input, json& output) {
    output = {{"warning", "[pause.quit] connection lost. You can rejoin"}};
}

void state_pause::play (json& output) {
    session.transition_to(std::make_unique<state_play>(session));
    output = {{"success", "[pause.play] The game was continued"}};
}

void state_pause::pause (json& output) {
    output = {{"error", "[pause.pause] wrong transition"}};
}

void state_pause::stop (json& output) {
    session.transition_to(std::make_unique<state_finish>(session));
    output = {{"success", "[pause.stop] The game was stopped"}};
}

void state_pause::setup (json& input, json& output) {
    output = {{"error", "[pause.setup] wrong transition"}};
}

void state_pause::update (json& output) {
    //TODO throw pause state
    output = {{"success", "[pause.update] Press play to continue"}};
}

void state_pause::action (json& input, json& output) {
    output = {{"error", "[pause.action] wrong transition"}};
}

void state_pause::serialize (json& package, serializers type) const {
    package = "state_pause";
}