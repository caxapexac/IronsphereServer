#ifndef LOGIC_STATE_PLAY_HPP
#define LOGIC_STATE_PLAY_HPP

#include "ihandler.hpp"

class state_play : public ihandler {
private:
    game_session& session;
public:
    explicit state_play (game_session& context);
    void join (json& input, json& output) override;
    void quit (json& input, json& output) override;
    void play (json& output) override;
    void pause (json& output) override;
    void stop (json& output) override;
    void setup (json& input, json& output) override;
    void update (json& output) override;
    void signal (json& input, json& output) override;
};

#endif //LOGIC_STATE_PLAY_HPP
