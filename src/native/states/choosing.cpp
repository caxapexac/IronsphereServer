#include "choosing.hpp"
#include "../lobby/session.hpp"


states::choosing::choosing (online::session& context) : session(context) {
    session.game = nullptr;
}

const std::string& states::choosing::type () const {
    return states::choosing_type;
}

void states::choosing::load (json& input, json& output) {
    session.game = json_tools::unpack_game(input);
    if (session.game != nullptr) {
        output = {{"success", "[state_choose.setup] The game was setup game type"}};
    }
    else {
        output = {{"error", "[state_choose.setup] Unknown game type"}};
    }
}

void states::choosing::save (json& output) {
    output = {{"error", "[state_choose.save] wrong transition"}};
}

void states::choosing::join (json& input, json& output) {
    auto result = session.players_uid.emplace(input.get<int>()); //TODO other type checks
    if (result.second) {
        output = {{"success", "[state_choose.join] Player was added into the room"}};
    }
    else {
        output = {{"error", "[state_choose.join] Player was already in the room"}};
    }
}

void states::choosing::quit (json& input, json& output) {
    if (session.players_uid.erase(input.get<int>()) != 0) {
        output = {{"success", "[state_choose.quit] Player was removed from the room"}};
    }
    else {
        output = {{"error", "[state_choose.quit] Player wasn't in the room"}};
    }
}

void states::choosing::play (json& output) {
    if (session.game != nullptr) {
        output = {{"success", "[state_choose.pause] The game was started"}};
        session.transition_to(std::make_unique<state_play>(session));
    }
    else {
        output = {{"error", "[state_choose.pause] The game wasn't setup"}};
    }
}

void states::choosing::pause (json& output) {
    output = {{"error", "[state_choose.pause] wrong transition"}};
}

void states::choosing::stop (json& output) {
    output = {{"error", "[state_choose.stop] wrong transition"}};
}

void states::choosing::setup (json& input, json& output) {
    // TODO game generation API
    //session.game = json_tools::unpack_game(input);
    if (session.game != nullptr) {
        output = {{"success", "[state_choose.setup] The game was setup game type"}};
    }
    else {
        output = {{"error", "[state_choose.setup] Unknown game type"}};
    }
}

void states::choosing::update (json& output) {
    session.get_info(output);
}

void states::choosing::signal (json& input, json& output) {
    output = {{"error", "[state_choose.signal] wrong transition"}};
}






