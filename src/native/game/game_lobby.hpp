#ifndef LOGIC_GAME_LOBBY_HPP
#define LOGIC_GAME_LOBBY_HPP

#include <map>
#include <vector>
#include "../base/interfaces.hpp"
#include "game_session.hpp"

class game_lobby {
private:
    std::map<std::string, std::unique_ptr<game_session>> sessions;
    json chat_buffer;

public:
    game_lobby ();
    std::string update();
    std::string chat(json& package);
    std::string join_session(json& package);
    std::string setup_rules(json& package);
    std::string start_arena(json& package);
    std::string arena_input(json& package);
    std::string pause_arena(json& package);
    std::string destroy_session(json& package);
};

game_lobby::game_lobby () {
    sessions = std::map<std::string, std::unique_ptr<game_session>>();
    chat_buffer = json::array();
}

//TODO change_delta_time return command
std::string game_lobby::update () {
    json package;
    package["chat_buffer"] = chat_buffer;
    chat_buffer.clear();
    for (int i = 0; i < sessions.size(); ++i) {

    }
}

std::string game_lobby::chat (json& package) {
    chat_buffer.push_back(package);
}

std::string game_lobby::join_session (json& package) {

}

std::string game_lobby::setup_rules (json& package) {

}

std::string game_lobby::start_arena (json& package) {

}

std::string game_lobby::arena_input (json& package) {

}

std::string game_lobby::pause_arena (json& package) {

}

std::string game_lobby::destroy_session (json& package) {

}

#endif //LOGIC_GAME_LOBBY_HPP
