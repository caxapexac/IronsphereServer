#ifndef LOGIC_STATE_PAUSE_HPP
#define LOGIC_STATE_PAUSE_HPP

#include <utility>

#include "abstract_state.hpp"

class game_session;

class state_pause : public abstract_state {
public:
    explicit state_pause (game_session* context);
    void play (json& output) override;
    void pause (json& output) override;
    void stop (json& output) override;
    void setup (json& input, json& output) override;
    void update (json& output) override;
    void action (json& input, json& output) override;
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;
    ~state_pause () override;
};



#endif //LOGIC_STATE_PAUSE_HPP
