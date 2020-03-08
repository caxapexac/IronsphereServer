#include "state_choose.hpp"
#include "../lobby/game_session.hpp"

state_choose::state_choose (game_session& context) : abstract_state(context) {
    session.map = nullptr;
    session.players = nullptr;
}

void state_choose::join (json& input, json& output) {
    session.players_id.push_back(input.get<int>()); //TODO other type checks
    output = {{"success", "[choose.join] Player was added into the room"}};
}

void state_choose::quit (json& input, json& output) {
    session.players_id.erase(session.players_id.begin() + input.get<int>());
    output = {{"success", "[choose.quit] Player was removed from the room"}};
}

void state_choose::play (json& output) {
    if (session.strategy == nullptr) {
        output = {{"error", "[choose.pause] cant start without strategy"}};
        return;
    }
    session.transition_to(std::make_unique<state_play>(session));
    session.map->serialize(output["map"], serial_save); //TODO check working
}

void state_choose::pause (json& output) {
    output = {{"error", "[choose.pause] wrong transition"}};
}

void state_choose::stop (json& output) {
    output = {{"error", "[choose.stop] wrong transition"}};
}

void state_choose::setup (json& input, json& output) {

    //Setup strategy
}

void state_choose::update (json& output) {
    //Return strategy
    if (session.strategy != nullptr) {
        session.strategy->serialize(output["strategy"], serial_info);
    }
}

void state_choose::action (json& input, json& output) {
    output = {{"error", "[choose.action] wrong transition"}};
}

void state_choose::serialize (json& package, serializers type) const {
    package = "state_choose";
}





