#ifndef LOGIC_STATE_PAUSE_HPP
#define LOGIC_STATE_PAUSE_HPP

#include "abstract_state.hpp"

class state_pause : public abstract_state {
public:
    explicit state_pause (game_session& context);
    void join (json& input, json& output) override;
    void quit (json& input, json& output) override;
    void play (json& output) override;
    void pause (json& output) override;
    void stop (json& output) override;
    void setup (json& input, json& output) override;
    void update (json& output) override;
    void action (json& input, json& output) override;
    void serialize (json& package, serializers type) const override;
};


#endif //LOGIC_STATE_PAUSE_HPP
