#include "session.hpp"
#include "../states/choosing.hpp"

online::session::session (const std::string& nsession_name) {
    session_name = nsession_name;
    players_uid = std::set<int>();
    state = std::make_unique<states::choosing>(*this);
    game = nullptr;
}

const std::string& online::session::type () const {
    return online::session_type;
}

std::string online::session::get_session_name () {
    return session_name;
}

int online::session::get_player_count () {
    return players_uid.size();
}

void online::session::session_info (json& output) {
    output[out_server_info::session_info::state] = state->type();
    output[out_server_info::session_info::session_name] = get_session_name();
    output[out_server_info::session_info::player_count] = get_player_count();
}

void online::session::info (json& output) {
    output[out_signal::type] = api_type::game_info;
    output[out_game_info::players_uid] = players_uid;
    if (game) game->info(output);
}

void online::session::load (json& input, json& output) {
    output[out_signal::type] = api_type::game_load;
    state->load(input, output);
}

void online::session::save (json& output) {
    output[out_signal::type] = api_type::game_save;
    state->save(output);
}

void online::session::join (int player_uid, json& output) {
    output[out_signal::type] = api_type::game_join;
    state->join(player_uid, output);
}

void online::session::quit (int player_uid, json& output) {
    output[out_signal::type] = api_type::game_quit;
    state->quit(player_uid, output);
}

void online::session::play (json& output) {
    output[out_signal::type] = api_type::game_play;
    state->play(output);
}

void online::session::pause (json& output) {
    output[out_signal::type] = api_type::game_pause;
    state->pause(output);
}

void online::session::stop (json& output) {
    output[out_signal::type] = api_type::game_stop;
    state->stop(output);
}

void online::session::setup (json& input, json& output) {
    output[out_signal::type] = api_type::game_setup;
    state->setup(input, output);
}

void online::session::update (json& output) {
    output[out_update::type] = api_type::game_update;
    output[out_update::session_data::players_uid] = players_uid;
    output[out_update::session_data::state] = state->type();
    state->update(output);
}

void online::session::signal (json& input, json& output) {
    output[out_signal::type] = api_type::game_signal;
    state->signal(input, output);
}

void online::session::transition_to (std::unique_ptr<ihandler> nstate) {
    state = std::move(nstate);
    //TODO log?
}











