#ifndef LOGIC_GAME_REALTIME_HPP
#define LOGIC_GAME_REALTIME_HPP

#include "base_game.hpp"

// template <int PlayerCount>
const std::string game_realtime_type = "game_realtime";
class game_realtime : public base_game {
public:
    const std::string& type () const override;
    bool check_end_game (json& output) override;
private:
    void frame () override;
    void calculate_client_data (int player_uid, json& output) override;
};

#endif //LOGIC_GAME_REALTIME_HPP
