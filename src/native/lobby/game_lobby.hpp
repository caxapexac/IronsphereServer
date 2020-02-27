#ifndef LOGIC_GAME_LOBBY_HPP
#define LOGIC_GAME_LOBBY_HPP

#include <map>
#include <set>
#include <vector>
#include "game_session.hpp"
#include "../base/constants.hpp"
#include "../base/interfaces.hpp"

class game_lobby {
private:
    float delta_time;
    std::map<int, std::shared_ptr<game_session>> sessions;
    json chat_buffer;

public:
    game_lobby () noexcept;

    /// One server frame
    /// \param output
    void update (json& output);

    /// Client menu info (players online, room list, etc)
    /// \param output
    void get_info (json& output);

    /// Add message from user to the message buffer
    /// \param input
    /// \param output
    void write_chat (json& input, json& output);

    /// Add player to the room. Create if doesn't exist
    /// \param input
    /// \param output
    void join_session (json& input, json& output);

    /// Everything in the session (including changing rules, state changing, game signals, etc)
    /// \param input
    /// \param output
    void input_session (json& input, json& output);

    /// Remove player from the room. Remove room if no players left
    /// \param input
    /// \param output
    void quit_session (json& input, json& output);
};


game_lobby::game_lobby () noexcept {
    delta_time = constants::lobby_delta_time;
    sessions = std::map<int, std::shared_ptr<game_session>>();
    chat_buffer = json::array();
}

void game_lobby::update (json& output) {
    output["delta_time"] = delta_time;
    output["chat_buffer"] = chat_buffer;
    chat_buffer.clear();
    for (const auto& item : sessions) {
        item.second->update(output["sessions"][item.first]);
    }
}

void game_lobby::get_info (json& output) {
    output["status"] = "alive";
    std::set<std::string> players_online;
    for (const auto& item : sessions) {
        item.second->get_info(output["sessions"][item.first]);
        for (const auto& player_id : output["sessions"][item.first]["players"]) {
            players_online.emplace(player_id);
        }
    }
    output["players_online"] = players_online;
}

void game_lobby::write_chat (json& input, json& output) {
    chat_buffer.push_back(input);
    output = {"success", "Message has been sent"};
    //TODO improve, make chat rooms
    //TODO important game events into write_chat (for example, logger::setup_lobby(this) then use logger::log_chat();
}

void game_lobby::join_session (json& input, json& output) {
    if (sessions[input["session_id"]] == nullptr) {
        sessions[input["session_id"]] = std::make_shared<game_session>();
    }
    sessions[input["session_id"]]->add_player(input["player_id"], output);
}

void game_lobby::input_session (json& input, json& output) {
    if (sessions[input["session_id"]] == nullptr) {
        output = {"error", "Session wasn't found"};
        return;
    }
    sessions[input["session_id"]]->signal(input["data"], output);
}

void game_lobby::quit_session (json& input, json& output) {
    if (sessions[input["session_id"]] == nullptr) {
        output = {"error", "Session wasn't found"};
        return;
    }
    sessions[input["session_id"]]->remove_player(input["player_id"], output);
    if (!sessions[input["session_id"]]->is_empty()) {
        output = {"success", "Player was removed from session"};
    }
    else {
        sessions.erase(input["session_id"]);
        output = {"success", "Session was deleted"};
        return;
    }
}

#endif //LOGIC_GAME_LOBBY_HPP
