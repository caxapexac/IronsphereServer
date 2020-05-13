#ifndef LOGIC_CONSTANTS_HPP
#define LOGIC_CONSTANTS_HPP

#include "third_party_includes.hpp"

//TODO all strings into enum constants
//TODO add common constants (generic RTS)
//TODO uint -> int ?
namespace constants {
    const std::string empty_string = "";
    const int version = 101; // Game version (Anti chEET)
    const int lobby_delta_time = 1000; // ms (start game loop delay)
    const char game_title[] = "Ironsphere";
    //const unsigned int player_units_limit = 100;
    //const unsigned int neutral_units_limit = 25;
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
