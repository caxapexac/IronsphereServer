#ifndef LOGIC_GAME_MAIN_HPP
#define LOGIC_GAME_MAIN_HPP

#include <string>

//TODO json structures of commands
class game_main {
private:
    game_main () = default;

public:
    /*
     * Inits the game
     */
    static std::string start (const std::string& data);

    /*
     * One frame of game logic
     */
    static std::string update ();

    /*
     * TODO need return?
     */
    static std::string signal (const std::string& data);

    /*
     * TODO maybe into destructor?
     */
    static std::string destroy ();
};

std::string game_main::start (const std::string& data) {
    return "starts with: " + data;
}

std::string game_main::update () { //TODO no argument
    return "updates";
}

std::string game_main::signal (const std::string& data) {
    return "signals with: " + data;
}

std::string game_main::destroy () { //TODO no argument
    return "destroys";
}

#endif //LOGIC_GAME_MAIN_HPP