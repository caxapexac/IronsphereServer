#ifndef LOGIC_GAME_MAIN_HPP
#define LOGIC_GAME_MAIN_HPP

#include <string>
#include "game_lobby.hpp"
#include "../base/interfaces.hpp"

//TODO json structures of commands
class game_main {
private:
    static game_lobby lobby;
    game_main () = default;

public:
    /// One frame of game logic (default N ms)
    /// \return json scheme is update_return
    static std::string update ();

    /// Action from player
    /// \param data_string : json scheme is signal
    /// \return json scheme is signal_return
    static std::string signal (const std::string& data_string);
};

std::string game_main::update () {
    return lobby.update();
}

std::string game_main::signal (const std::string& data_string) {
    json package = data_string;
    if (package["command"] == nullptr) return json{"error", "Input isn't correct"}.dump();
    if (package["command"] == "chat") {
        return lobby.chat(package["data"]);
    }
    else if (package["command"] == "join_session") { // Create or join room
        return lobby.join_session(package["data"]);
    }
    else if (package["command"] == "setup_rules") { // Choose map
        return lobby.setup_rules(package["data"]);
    }
    else if (package["command"] == "start_arena") { // Start
        return lobby.start_arena(package["data"]);
    }
    else if (package["command"] == "arena_input") { // Attac
        return lobby.arena_input(package["data"]);
    }
    else if (package["command"] == "pause_arena") { //Optional, pause button
        return lobby.pause_arena(package["data"]);
    }
    else if (package["command"] == "destroy_session") { // Die
        return lobby.destroy_session(package["data"]);
    }
    else return json{"error", "Command isn't correct"}.dump();
}

game_lobby game_main::lobby = game_lobby();

#endif //LOGIC_GAME_MAIN_HPP