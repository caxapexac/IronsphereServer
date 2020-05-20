#ifndef LOGIC_REALTIME_HPP
#define LOGIC_REALTIME_HPP

#include "base_game.hpp"

namespace game {
    // template <int PlayerCount>
    const std::string realtime_type = "game_realtime";
    class realtime : public game::base_game {
    public:
        const std::string& type () const override;
        bool check_end_game (json& output) override;
    private:
        void frame () override;
        void calculate_client_data (int player_uid, json& output) override;
    };

}

#endif //LOGIC_REALTIME_HPP
