#ifndef LOGIC_GAME_SESSION_HPP
#define LOGIC_GAME_SESSION_HPP

#include <vector>
#include "../rules/game_arena.hpp"
#include "../managers/rules.hpp"

class game_session {
private:
    enum game_state {
        g_choosing, g_play, g_pause, g_finished
    };

    game_state state;
    std::vector<std::string> players;
    std::unique_ptr<rules> rule;

public:
    game_session ();
    // TODO? add more ctors/operators

    /// Checks if there is no players in session
    bool is_empty ();

    /// Generic info about session
    /// \param output
    void get_info (json& output);

    /// Adds player to the session
    /// \param input
    /// \param output
    void add_player (json& input, json& output);

    /// One session frame
    /// \param output
    void update (json& output);

    /// Input from the player
    /// \param input
    /// \param output
    void signal (json& input, json& output);

    /// Removes player from the session if exist
    /// \param input
    /// \param output
    void remove_player (json& input, json& output);

};

game_session::game_session () {
    state = g_choosing;
    players = std::vector<std::string>();
    rule = rules();
}

bool game_session::is_empty () {
    return players.empty();
}

void game_session::get_info (json& output) {
    output["state"] = state;
    output["players"] = players;
    // TODO add rules info
}

void game_session::add_player (json& input, json& output) {
    for (const auto& player : players) {
        if (player == input) {
            output = {"error", "Player is already in the room"};
            return;
        }
    }
    players.push_back(input);
    output = {"success", "Player was added into the room"};
}

void game_session::update (json& output) {
    rule->update(output);
}

void game_session::signal (json& input, json& output) {
    if (input["command"] == nullptr) {
        output = {"error", "Input isn't correct"};
    }
    else if (input["command"] == "get_info") {
        lobby.get_info(output);
    }
    else if (input["command"] == "write_chat") {
        lobby.write_chat(input["data"], output);
    }
    else if (input["command"] == "join_session") {
        lobby.join_session(input["data"], output);
    }
    else if (input["command"] == "input_session") {
        lobby.input_session(input["data"], output);
    }
    else if (input["command"] == "quit_session") {
        lobby.quit_session(input["data"], output);
    }
    else {
        output = {"error", "Command isn't correct"};
    }
}

void game_session::remove_player (json& input, json& output) {
    for (auto it = players.begin(); it != players.end(); ++it) {
        if (*it == input.get<std::string>()) {
            players.erase(it);
            output = {"success", "Player was removed from the room"};
            return;
        }
    }
    output = {"error", "Player is not in this room"};
}


#endif //LOGIC_GAME_SESSION_HPP
