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

void online::session::get_info (json& output) {
    output["session_name"] = session_name;
    output["players_uid"] = players_uid;
    if (game) game->get_static_content(output["field"]);
}

void online::session::info (json& output) {
    state->info(output);
}

void online::session::load (json& input, json& output) {
    state->load(input, output);
}

void online::session::save (json& output) {
    state->save(output);
}

void online::session::join (json& input, json& output) {
    state->join(input, output);
}

void online::session::quit (json& input, json& output) {
    state->quit(input, output);
}

void online::session::play (json& output) {
    state->play(output);
}

void online::session::pause (json& output) {
    state->pause(output);
}

void online::session::stop (json& output) {
    state->stop(output);
}

void online::session::setup (json& input, json& output) {
    state->setup(input, output);
}

void online::session::update (json& output) {
    state->update(output);
}

void online::session::signal (json& input, json& output) {
    state->signal(input, output);
}

void online::session::transition_to (std::unique_ptr<ihandler> nstate) {
    state = std::move(nstate);
    //TODO log?
}









