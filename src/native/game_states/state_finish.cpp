#include "state_finish.hpp"
#include "../lobby/game_session.hpp"

state_finish::state_finish (game_session& context) : abstract_state(context) { }

void state_finish::join (json& input, json& output) {
    output = {{"error", "[finish.join] wrong transition"}};
}

void state_finish::quit (json& input, json& output) {
    session.players_id.erase(session.players_id.begin() + input.get<int>());
    output = {{"success", "[finish.quit] Player was removed from the room"}};
}

void state_finish::play (json& output) {
    session.map = nullptr;
    session.players = nullptr;
    session.transition_to(std::make_unique<state_play>(session));
}

void state_finish::pause (json& output) {

}

void state_finish::stop (json& output) {

}

void state_finish::setup (json& input, json& output) {

}

void state_finish::update (json& output) {
    //TODO throw records
}

void state_finish::action (json& input, json& output) {

}

void state_finish::serialize (json& package, serializers type) const {
    package = "state_finish";
}