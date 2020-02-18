#ifndef LOGIC_GAME_LOOP_HPP
#define LOGIC_GAME_LOOP_HPP

#include <string>

class game_loop {
private:
    game_loop () = default;

public:
    static std::string start (std::string data);
    static std::string update (std::string data);
    static std::string signal (std::string data);
    static std::string destroy (std::string data);
};

#endif //LOGIC_GAME_LOOP_HPP