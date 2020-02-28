#ifndef LOGIC_STATE_PLAY_HPP
#define LOGIC_STATE_PLAY_HPP

#include "abstract_state.hpp"

class state_play : public abstract_state {
public:
    explicit state_play (game_session* context);
    void play (json& output) override;
    void pause (json& output) override;
    void stop (json& output) override;
    void setup (json& input, json& output) override;
    void update (json& output) override;
    void action (json& input, json& output) override;
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;
    ~state_play () override;
};

#endif //LOGIC_STATE_PLAY_HPP
