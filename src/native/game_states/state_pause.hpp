#ifndef LOGIC_STATE_PAUSE_HPP
#define LOGIC_STATE_PAUSE_HPP

#include "../base/includes.hpp"

const std::string state_pause_type = "state_pause";
class state_pause : public ihandler {
private:
    game_session& session;
public:
    explicit state_pause (game_session& context);
    const std::string& type () const override;
    void load (json& input, json& output) override;
    void save (json& output) override;
    void join (json& input, json& output) override;
    void quit (json& input, json& output) override;
    void play (json& output) override;
    void pause (json& output) override;
    void stop (json& output) override;
    void setup (json& input, json& output) override;
    void update (json& output) override;
    void signal (json& input, json& output) override;
};


#endif //LOGIC_STATE_PAUSE_HPP
