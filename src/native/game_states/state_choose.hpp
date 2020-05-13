#ifndef LOGIC_STATE_CHOOSE_HPP
#define LOGIC_STATE_CHOOSE_HPP

#include "../base/includes.hpp"

// TODO state : abstract_state : ihandler (for common session field)
const std::string state_choose_type = "state_choose";
class state_choose : public ihandler {
private:
    game_session& session;
public:
    explicit state_choose (game_session& context);
    const std::string& type () const override;
    void join (json& input, json& output) override;
    void quit (json& input, json& output) override;
    void play (json& output) override;
    void pause (json& output) override;
    void stop (json& output) override;
    void setup (json& input, json& output) override;
    void update (json& output) override;
    void signal (json& input, json& output) override;
};


#endif //LOGIC_STATE_CHOOSE_HPP
