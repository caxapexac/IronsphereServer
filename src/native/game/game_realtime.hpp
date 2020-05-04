#ifndef LOGIC_GAME_REALTIME_HPP
#define LOGIC_GAME_REALTIME_HPP

#include "base_game.hpp"

// template <int PlayerCount>
class game_realtime : public base_game {
public:
    static const std::string type;

    bool check_end_game (json& output) override;
private:
    void frame () override;
    void calculate_client_data (int player_uid, json& output) override;
};

#endif //LOGIC_GAME_REALTIME_HPP
