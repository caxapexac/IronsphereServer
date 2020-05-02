#ifndef LOGIC_TILE_DAMAGE_HPP
#define LOGIC_TILE_DAMAGE_HPP

#include "tile.hpp"
#include "tile_money.hpp"


class tile_damage : public tile {
private:
    int damage;
public:
    static const std::string type;

    explicit tile_damage (int ndamage = 1, float nheight = 0);
    void serialize (json& package) const override;
    void deserialize (json& package) override;

};


#endif //LOGIC_TILE_DAMAGE_HPP
