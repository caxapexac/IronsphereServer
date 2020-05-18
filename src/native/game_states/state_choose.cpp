#include "state_choose.hpp"
#include "../lobby/game_session.hpp"

state_choose::state_choose (game_session& context) : session(context) {
    session.game = nullptr;
}

const std::string& state_choose::type () const {
    return state_choose_type;
}

void state_choose::load (json& input, json& output) {
    session.game = json_tools::unpack_game(input);
    if (session.game != nullptr) {
        output = {{"success", "[state_choose.setup] The game was setup game type"}};
    }
    else {
        output = {{"error", "[state_choose.setup] Unknown game type"}};
    }
}

void state_choose::save (json& output) {
    output = {{"error", "[state_choose.save] wrong transition"}};
}

void state_choose::join (json& input, json& output) {
    auto result = session.players_uid.emplace(input.get<int>()); //TODO other type checks
    if (result.second) {
        output = {{"success", "[state_choose.join] Player was added into the room"}};
    }
    else {
        output = {{"error", "[state_choose.join] Player was already in the room"}};
    }
}

void state_choose::quit (json& input, json& output) {
    if (session.players_uid.erase(input.get<int>()) != 0) {
        output = {{"success", "[state_choose.quit] Player was removed from the room"}};
    }
    else {
        output = {{"error", "[state_choose.quit] Player wasn't in the room"}};
    }
}

void state_choose::play (json& output) {
    if (session.game != nullptr) {
        output = {{"success", "[state_choose.pause] The game was started"}};
        session.transition_to(std::make_unique<state_play>(session));
    }
    else {
        output = {{"error", "[state_choose.pause] The game wasn't setup"}};
    }
}

void state_choose::pause (json& output) {
    output = {{"error", "[state_choose.pause] wrong transition"}};
}

void state_choose::stop (json& output) {
    output = {{"error", "[state_choose.stop] wrong transition"}};
}

void state_choose::setup (json& input, json& output) {
    // TODO game generation API
    //session.game = json_tools::unpack_game(input);
    if (session.game != nullptr) {
        output = {{"success", "[state_choose.setup] The game was setup game type"}};
    }
    else {
        output = {{"error", "[state_choose.setup] Unknown game type"}};
    }
}

void state_choose::update (json& output) {
    session.get_info(output);
}

void state_choose::signal (json& input, json& output) {
    output = {{"error", "[state_choose.signal] wrong transition"}};
}






