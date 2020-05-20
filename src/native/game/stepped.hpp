#ifndef LOGIC_STEPPED_HPP
#define LOGIC_STEPPED_HPP

#include "base_game.hpp"

namespace game {
    const std::string stepped_type = "game_stepped";
    class stepped : public game::base_game {
    public:
        const std::string& type () const override;
        bool check_end_game (json& output) override;
    private:
        void frame () override;
        void calculate_client_data (int player_uid, json& output) override;
    };
}


#endif //LOGIC_STEPPED_HPP
