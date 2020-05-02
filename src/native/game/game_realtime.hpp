#ifndef LOGIC_GAME_REALTIME_HPP
#define LOGIC_GAME_REALTIME_HPP

#include "abstract_game.hpp"

// template <int PlayerCount>
class game_realtime : public abstract_game {
public:
    bool check_end_game (json& output) override;
private:
    void frame () override;
    void calculate_client_data (int player_uid, json& output) override;
public:
    static const std::string type;

};

#endif //LOGIC_GAME_REALTIME_HPP
