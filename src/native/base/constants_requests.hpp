#ifndef LOGIC_CONSTANTS_REQUESTS_HPP
#define LOGIC_CONSTANTS_REQUESTS_HPP

#include "third_party_includes.hpp"

namespace in_signal {
    const std::string type = "type"; // : string
    const std::string version = "version"; // : int
    const std::string sender = "sender"; // : int
}

namespace in_server_info { // : in_signal
    // Nothing
}

namespace in_read_chat { // : in_signal
    // Nothing
}

namespace in_write_chat { // : in_signal
    const std::string message = "message"; // : string
}

namespace in_create_session { // : in_signal
    const std::string session_id = "session_id"; // : int
    const std::string session_name = "session_name"; // : string
}

namespace in_signal_session { // : in_signal
    const std::string session_id = "session_id"; // : int
}

namespace in_game_info { // : in_signal_session
    // Nothing
}

namespace in_game_load { // : in_signal_session
    const std::string game = "game"; // : base_game?
}

namespace in_game_save { // : in_signal_session
    // Nothing
}

namespace in_game_join { // : in_signal_session
    // Nothing
}

namespace in_game_quit { // : in_signal_session
    // Nothing
}

namespace in_game_play { // : in_signal_session
    // Nothing
}

namespace in_game_pause { // : in_signal_session
    // Nothing
}

namespace in_game_stop { // : in_signal_session
    // Nothing
}

namespace in_game_setup { // : in_signal_session
    // TODO later
}

namespace in_game_signal { // : in_signal_session
    const std::string selected_units = "selected_units"; // : list<int>
    const std::string command = "command"; // : command_data

    namespace command_data {
        const std::string component = "component"; // : string
        // Other data
    }

}

// Classes

namespace prototype {
    const std::string name = "name"; // : string
    const std::string components = "components"; // : list<string>
    const std::string prototype = "prototype"; // : string?
    const std::string parameters_bool = "parameters_bool"; // : map<string, bool>
    const std::string parameters_int = "parameters_int"; // : map<string, int>
    const std::string parameters_float = "parameters_float"; // : map<string, float>
    const std::string parameters_string = "parameters_string"; // : map<string, string>
    const std::string parameters_vector2_int = "parameters_vector2_int"; // : map<string, vector2<int>>
    const std::string parameters_vector2_float = "parameters_vector2_float"; // : map<string, vector2<float>>
    const std::string parameters_list_vector2 = "parameters_list_vector2"; // : map<string, std::list<vector2<int>>>

}

#endif //LOGIC_CONSTANTS_REQUESTS_HPP
