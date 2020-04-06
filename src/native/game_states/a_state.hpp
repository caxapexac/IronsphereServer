#ifndef LOGIC_A_STATE_HPP
#define LOGIC_A_STATE_HPP

#include "../base/interfaces.hpp"

class game_session;

class a_state : public iserializable {
protected:
    game_session& session;

    explicit a_state (game_session& context);
public:
    virtual void join (json& input, json& output) = 0;
    virtual void quit (json& input, json& output) = 0;
    virtual void play (json& output) = 0;
    virtual void pause (json& output) = 0;
    virtual void stop (json& output) = 0;
    virtual void setup (json& input, json& output) = 0;
    virtual void update (json& output) = 0;
    virtual void action (json& input, json& output) = 0;
    void serialize (json& package, serializers type) const override = 0;
    void deserialize (json& package) final;
    ~a_state () override = default;
};

#endif //LOGIC_A_STATE_HPP
