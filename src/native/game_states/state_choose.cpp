#include "state_choose.hpp"
#include "../lobby/game_session.hpp"

state_choose::state_choose (game_session& context) : session(context) {
    session.game = nullptr;
}

const std::string& state_choose::type () const {
    return state_choose_type;
}

void state_choose::join (json& input, json& output) {
    auto result = session.players_uid.emplace(input.get<int>()); //TODO other type checks
    if (result.second) {
        output = {{"success", "[choose.join] Player was added into the room"}};
    }
    else {
        output = {{"error", "[choose.join] Player was already in the room"}};
    }
}

void state_choose::quit (json& input, json& output) {
    if (session.players_uid.erase(input.get<int>()) != 0) {
        output = {{"success", "[choose.quit] Player was removed from the room"}};
    }
    else {
        output = {{"error", "[choose.quit] Player wasn't in the room"}};
    }
}

void state_choose::play (json& output) {
    if (session.game != nullptr) {
        output = {{"success", "[choose.pause] The game was started"}};
        session.transition_to(std::make_unique<state_play>(session));
    }
    else {
        output = {{"error", "[choose.pause] The game wasn't setup"}};
    }
}

void state_choose::pause (json& output) {
    output = {{"error", "[choose.pause] wrong transition"}};
}

void state_choose::stop (json& output) {
    output = {{"error", "[choose.stop] wrong transition"}};
}

void state_choose::setup (json& input, json& output) {
    session.game = json_tools::unpack_game(input);
    if (session.game != nullptr) {
        output = {{"success", "[choose.setup] The game was setup game type"}};
    }
    else {
        output = {{"error", "[choose.setup] Unknown game type"}};
    }
}

void state_choose::update (json& output) {
    session.get_info(output);
}

void state_choose::signal (json& input, json& output) {
    output = {{"error", "[choose.signal] wrong transition"}};
}






