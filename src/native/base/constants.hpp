#ifndef LOGIC_CONSTANTS_HPP
#define LOGIC_CONSTANTS_HPP

#include "third_party_includes.hpp"

//TODO add common constants (generic RTS)
namespace constants {
    const std::string empty_string = "";
    const int version = 102; // Game version (Anti chEET)
    const int lobby_delta_time = 1000; // ms (start game loop delay)
    const int chat_queue_capacity = 100;
    const int log_queue_capacity = 100;
    const char game_title[] = "Ironsphere";
    //const int player_units_limit = 100;
    //const int neutral_units_limit = 25;
}

namespace p {
    const std::string position = "position";
    const std::string is_moving = "is_moving";
    const std::string move_target = "move_target";
    const std::string move_path = "move_path";

}

enum loggers {
    server_console_logger = 1, all_clients_logger = 2, server_file_logger = 4
};

enum streams : char {
    error = 'E', warning = 'W', debug = 'D', message = 'M', special = 'S'
};

//TODO into class

/*Patterns
 * L1 Unit attributes, abilities (components(?)) (?)
 * L1 Create Unit (factory/abstract factory)
 * L2 Store unit get_info (composite) is json legal?
 * L2 Get unit in base (observer) events subscribe
 * L2 Tilemap - Unit (proxy)
 * L2 Neutral - Unit (strategy)
 * STARTED L3 Input (facade)
 * L3 Unit - Unit (mediator)
 * L3 Input - Unit (command)
 * L3 User - Unit (chain of responsibility)
 * STARTED L4 Logging level (proxy)
 * L4 Logging format (adapter)
 * STARTED L5 Save/Load (memento) is json legal?
 * L6 Player1 - Player2 - Player1 (State) idk how cuz we have RTS
 * L6 Game class (singleton)
 * L7
 * Other
 */


#endif //LOGIC_CONSTANTS_HPP
