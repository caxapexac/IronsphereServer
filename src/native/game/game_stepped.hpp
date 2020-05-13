#ifndef LOGIC_GAME_STEPPED_HPP
#define LOGIC_GAME_STEPPED_HPP

#include "base_game.hpp"

const std::string game_stepped_type = "game_stepped";
class game_stepped : public base_game {
public:
    const std::string& type () const override;
    bool check_end_game (json& output) override;
private:
    void frame () override;
    void calculate_client_data (int player_uid, json& output) override;
};


#endif //LOGIC_GAME_STEPPED_HPP
