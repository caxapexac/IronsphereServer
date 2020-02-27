#ifndef LOGIC_GAME_MAIN_HPP
#define LOGIC_GAME_MAIN_HPP

#include <string>
#include "game_lobby.hpp"
#include "../base/interfaces.hpp"

/// TODO json structures of commands
/// Static class for client interactions
class game_main {
private:
    static game_lobby lobby;
    game_main () = default;

public:
    /// One frame of game logic (default N ms)
    /// \param output json scheme is update_output
    static void update (json& output);

    /// Action from player
    /// \param input json scheme is signal_input
    /// \param output json scheme is signal_output
    static void signal (json& input, json& output);
};

game_lobby game_main::lobby = game_lobby();

void game_main::update (json& output) {
    lobby.update(output);
}

void game_main::signal (json& input, json& output) {
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

#endif //LOGIC_GAME_MAIN_HPP