#ifndef LOGIC_TILE_MONEY_HPP
#define LOGIC_TILE_MONEY_HPP

#include "tile.hpp"

class tile_money : public tile {
private:
    int money;
public:
    static const std::string type;

    explicit tile_money (int nmoney = 1, float nheight = 0);
    void serialize (json& package) const override;
    void deserialize (json& package) override;

};

#endif //LOGIC_TILE_MONEY_HPP
