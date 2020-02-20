#ifndef LOGIC_GAME_LOOP_HPP
#define LOGIC_GAME_LOOP_HPP

#include <string>

class game_loop {
private:
    game_loop () = default;

public:
    static std::string start (const std::string& data);
    static std::string update (const std::string& data);
    static std::string signal (const std::string& data);
    static std::string destroy (const std::string& data);
};

// // is called when game is initialized;
// extern "C" std::string* on_start(int seed) {
//     std::shared_ptr<game> g = game::get(seed);
//     log::say("Game initialized.");
//     return new std::string();
// }
//
// // is called on every update loop iteration;
// extern "C" std::vector<std::string>* on_update() {
//     log::say("State updated.");
//     return new std::vector<std::string>();
// }
//
// // is called on every user command, including save/load;
// extern "C" std::string* on_signal(const char* json_input) {
//     log::say("State updated.");
//     return new std::string();
// }
//
// // is called when game session finished;
// extern "C" void on_destroy() {
//     log::say("Game terminated.");
// }

#endif //LOGIC_GAME_LOOP_HPP