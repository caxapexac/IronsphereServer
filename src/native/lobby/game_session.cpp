#include "game_session.hpp"

game_session::game_session (const std::string& nsession_name) {
    session_name = nsession_name;
    players_uid = std::set<int>();
    state = std::make_unique<state_choose>(*this);
    game = nullptr;
}

std::string game_session::get_session_name () {
    return session_name;
}

int game_session::get_player_count () {
    return players_uid.size();
}

void game_session::get_info (json& output) {
    output["session_name"] = session_name;
    output["players_uid"] = players_uid;
    if (game) game->serialize(output["game"], serial_save);
}

void game_session::join (json& input, json& output) {
    state->join(input, output);
}

void game_session::quit (json& input, json& output) {
    state->quit(input, output);
}

void game_session::play (json& output) {
    state->play(output);
}

void game_session::pause (json& output) {
    state->pause(output);
}

void game_session::stop (json& output) {
    state->stop(output);
}

void game_session::setup (json& input, json& output) {
    state->setup(input, output);
}

void game_session::update (json& output) {
    state->update(output);
}

void game_session::signal (json& input, json& output) {
    state->signal(input, output);
}

void game_session::transition_to (std::unique_ptr<ihandler> nstate) {
    state = std::move(nstate);
    //TODO log?
}


