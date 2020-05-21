#ifndef LOGIC_CONSTANTS_RESPONSES_HPP
#define LOGIC_CONSTANTS_RESPONSES_HPP

#include "third_party_includes.hpp"

namespace out_update {
    const std::string type = "type"; // : string
    const std::string delta_time = "delta_time"; // : float
    const std::string chat_buffer_updates = "chat_buffer_updates"; // : int
    const std::string sessions = "sessions"; // : map<int, session_data>

    namespace session_data {
        const std::string players_uid = "players_uid"; // : set<int>
        const std::string state = "state"; // : string
        const std::string players = "players"; // : map<int, serialized player>
        const std::string players_data = "players_data"; // : map<int, player_data>
        // TODO

        namespace player_data {
            //const std::string units = "units"; // map<int, unit>
            //const std::string units_public = "units_public"; // map<int, unit_public> (units but without some params)
        }
    }
}

namespace out_signal {
    const std::string type = "type"; // : string
    const std::string error = "error"; // : string?
    const std::string success = "success"; // : string?
}

namespace out_server_info { // : out_signal
    const std::string sessions = "sessions"; // : map<int, session_info>?

    namespace session_info {
        const std::string state = "state"; // : string
        const std::string session_name = "session_name"; // : string
        const std::string player_count = "player_count"; // : int
    }
}

namespace out_read_chat { // : out_signal
    const std::string chat_buffer = "chat_buffer"; // : queue<chat_message>?
}

namespace out_write_chat { // : out_signal
    // Nothing
}

namespace out_create_session { // : out_signal
    // Nothing
}

namespace out_signal_session { // : out_signal
    // Nothing
}

namespace out_game_info { // : out_signal
    const std::string players_uid = "players_uid"; // : set<int>
    const std::string game_type = "game_type"; // : string?
    const std::string tilemap = "tilemap"; // : tilemap?
}

namespace out_game_load { // : out_signal
    // Nothing
}

namespace out_game_save { // : out_signal
    const std::string game = "game"; // : base_game?
}

namespace out_game_join { // : out_signal
    // Nothing
}

namespace out_game_quit { // : out_signal
    // Nothing
}

namespace out_game_play { // : out_signal
    // Nothing
}

namespace out_game_pause { // : out_signal
    // Nothing
}

namespace out_game_stop { // : out_signal
    // Nothing
}

namespace out_game_setup { // : out_signal
    // Nothing
}

namespace out_game_signal { // : out_signal
    // Nothing
}




#endif //LOGIC_CONSTANTS_RESPONSES_HPP
