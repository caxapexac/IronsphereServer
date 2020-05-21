#ifndef LOGIC_CONSTANTS_VALUES_HPP
#define LOGIC_CONSTANTS_VALUES_HPP

#include "third_party_includes.hpp"

namespace api_type {
    const std::string signal = "signal";
    const std::string server_info = "server_info";
    const std::string read_chat = "read_chat";
    const std::string write_chat = "write_chat";
    const std::string create_session = "create_session";
    const std::string signal_session = "signal_session"; // Only response

    const std::string game_info = "game_info";
    const std::string game_load = "game_load";
    const std::string game_save = "game_save";
    const std::string game_join = "game_join";
    const std::string game_quit = "game_quit";
    const std::string game_play = "game_play";
    const std::string game_pause = "game_pause";
    const std::string game_stop = "game_stop";
    const std::string game_setup = "game_setup";
    const std::string game_update = "game_update";
    const std::string game_signal = "game_signal";
}


#endif //LOGIC_CONSTANTS_VALUES_HPP
