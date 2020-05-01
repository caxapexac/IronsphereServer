#include "state_play.hpp"
#include "../lobby/game_session.hpp"

state_play::state_play (game_session& context) : abstract_state(context) {
    if (session.storage == nullptr) {
        session.storage = session.strategy->generate();
    }
}

void state_play::join (json& input, json& output) {
    output = {{"error", "[play.join] wrong transition"}};
}

void state_play::quit (json& input, json& output) {
    output = {{"warning", "[play.quit] connection lost. You can rejoin"}};
}

void state_play::play (json& output) {
    output = {{"error", "[play.play] wrong transition"}};
}

void state_play::pause (json& output) {
    session.transition_to(std::make_unique<state_pause>(session));
    output = {{"success", "[play.pause] The game was paused"}};
}

void state_play::stop (json& output) {
    session.transition_to(std::make_unique<state_finish>(session));
    output = {{"success", "[play.stop] The game was stopped"}};
}

void state_play::setup (json& input, json& output) {
    output = {{"error", "[play.setup] wrong transition"}};
}

void state_play::update (json& output) {
    //TODO throw play
    //session.strategy->
    for (int i = 0; i < session.players->size(); ++i) {
        //session.players->at(i).update();
    }
}

void state_play::action (json& input, json& output) {

}

void state_play::serialize (json& package, serializers type) const {
    package = "state_play";
}
