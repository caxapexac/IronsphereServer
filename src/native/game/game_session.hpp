#ifndef LOGIC_GAME_SESSION_HPP
#define LOGIC_GAME_SESSION_HPP

#include "game_arena.hpp"

class game_session : public iserializable {
private:
    enum game_state {
        choosing,
        play,
        pause,
        finished
    };

    game_arena arena; //TODO template
    game_state state;
public:
    game_session();
};


#endif //LOGIC_GAME_SESSION_HPP
