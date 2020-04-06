#ifndef LOGIC_A_STRATEGY_HPP
#define LOGIC_A_STRATEGY_HPP

#include "../structs_field/a_tilemap.hpp"
#include "../structs/player.hpp"

class a_strategy : public iserializable {
protected:


public:
    virtual std::unique_ptr<game_storage> generate () = 0; //TODO

    virtual int check_end_game (game_storage& storage) = 0; //TODO

    virtual void serialize (json& package, serializers type) const override = 0; //TODO

    virtual void deserialize (json& package) override = 0; //TODO


    //static const int player_count = P; //TODO make something not so rubbish-like
    //map_builder builder; //TODO L6
    // TODO map type (square/hex)
    // TODO map size
    // TODO max units count
    // TODO L6 Win rule
    // TODO L6 Step queue (useless)
    // TODO new game ability ?
};

#endif //LOGIC_A_STRATEGY_HPP
