#ifndef LOGIC_ABSTRACT_STRATEGY_HPP
#define LOGIC_ABSTRACT_STRATEGY_HPP

#include "../../field/tilemap.hpp"
#include "../../game/player.hpp"

class abstract_strategy {
    virtual void generate (tilemap& map) = 0;
    virtual int check_end_game(std::vector<player>& players) = 0;
    //static const int player_count = P; //TODO make something not so rubbish-like

    ///
    //map_builder builder; //TODO L6
    // TODO L6 Win rule
    // TODO L6 Step queue (useless)
    // TODO new game ability ?
};

#endif //LOGIC_ABSTRACT_STRATEGY_HPP
