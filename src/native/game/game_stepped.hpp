#ifndef LOGIC_GAME_STEPPED_HPP
#define LOGIC_GAME_STEPPED_HPP

#include "base_game.hpp"

class game_stepped : public base_game {
public:
    static const std::string type;

    bool check_end_game (json& output) override;
private:
    void frame () override;
    void calculate_client_data (int player_uid, json& output) override;
};


#endif //LOGIC_GAME_STEPPED_HPP
