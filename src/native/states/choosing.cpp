#include "choosing.hpp"
#include "holding.hpp"
#include "playing.hpp"
#include "../online/session.hpp"


states::choosing::choosing (online::session& context) : session(context) {
    session.game = nullptr;
}

const std::string& states::choosing::type () const {
    return states::choosing_type;
}

void states::choosing::load (json& input, json& output) {
    session.game = json_tools::unpack_game(input[in_game_load::game]);
    if (session.game != nullptr) {
        output[out_signal::success] = "[state_choose.setup] The game was setup game type";
        session.transition_to(std::make_unique<states::holding>(session));
    }
    else {
        output[out_signal::error] = "[state_choose.setup] Broken saved game";
    }
}

void states::choosing::save (json& output) {
    output[out_signal::error] = "[state_choose.save] wrong transition";
}

void states::choosing::join (int player_uid, json& output) {
    auto result = session.players_uid.emplace(player_uid); //TODO other type checks
    if (result.second) {
        output[out_signal::success] = "[state_choose.join] Player was added into the room";
    }
    else {
        output[out_signal::error] = "[state_choose.join] Player was already in the room";
    }
}

void states::choosing::quit (int player_uid, json& output) {
    if (session.players_uid.erase(player_uid) != 0) {
        output[out_signal::success] = "[state_choose.quit] Player was removed from the room";
    }
    else {
        output[out_signal::error] = "[state_choose.quit] Player wasn't in the room";
    }
}

void states::choosing::play (json& output) {
    if (session.game != nullptr) {
        output[out_signal::success] = "[state_choose.pause] The game was started";
        session.transition_to(std::make_unique<playing>(session));
    }
    else {
        output[out_signal::error] = "[state_choose.pause] The game wasn't setup";
    }
}

void states::choosing::pause (json& output) {
    output[out_signal::error] = "[state_choose.pause] wrong transition";
}

void states::choosing::stop (json& output) {
    output[out_signal::error] = "[state_choose.stop] wrong transition";
}

void states::choosing::setup (json& input, json& output) {
    // TODO game generation API
    //session.game = utils::generate_game(input["game_settings"])
    if (session.game != nullptr) {
        output[out_signal::success] = "[state_choose.setup] The game was setup game type";
    }
    else {
        output[out_signal::error] = "[state_choose.setup] Unknown game type";
    }
}

void states::choosing::update (json& output) {
    // Nothing
}

void states::choosing::signal (json& input, json& output) {
    output[out_signal::error] = "[state_choose.signal] wrong transition";
}








