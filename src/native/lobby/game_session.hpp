#ifndef LOGIC_GAME_SESSION_HPP
#define LOGIC_GAME_SESSION_HPP

#include "../base/includes.hpp"
#include "../game/base_game.hpp"
#include "../game_states/state_choose.hpp"
#include "../game_states/state_play.hpp"
#include "../game_states/state_pause.hpp"

const std::string game_session_type = "game_session";
class game_session : ihandler {
    friend class state_choose;
    friend class state_play;
    friend class state_pause;

private:
    std::string session_name;
    std::set<int> players_uid; // For security
    std::unique_ptr<ihandler> state; // Game state
    std::unique_ptr<base_game> game; // Game & game rules

public:
    explicit game_session (const std::string& nsession_name);
    const std::string& type () const override;
    std::string get_session_name ();
    int get_player_count ();
    void get_info (json& output);

    void join (json& input, json& output) override;
    void quit (json& input, json& output) override;
    void play (json& output) override;
    void pause (json& output) override;
    void stop (json& output) override;
    void setup (json& input, json& output) override;
    void update (json& output) override;
    void signal (json& input, json& output) override;

private:
    void transition_to (std::unique_ptr<ihandler> nstate);
};

#endif //LOGIC_GAME_SESSION_HPP
