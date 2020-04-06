#ifndef LOGIC_TILE_MONEY_HPP
#define LOGIC_TILE_MONEY_HPP

#include "tile.hpp"

class tile_money : public tile {
private:
    int money;
public:
    explicit tile_money (int nmoney, float nheight = 1.0f, int ntexture = 0);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;
    void update () override;
};

tile_money::tile_money (int nmoney, float nheight, int ntexture) : tile(nheight, ntexture), money(nmoney) { }

void tile_money::serialize (json& package, serializers type) const {
    tile::serialize(package, type);
    package["type"] = "money";
    package["money"] = money;
}

void tile_money::deserialize (json& package) {
    tile::deserialize(package);
    money = package["money"].get<int>();
    // TODO json ctor
}

void tile_money::update () {
    //get_unit().get_player().money += money;
}

#endif //LOGIC_TILE_MONEY_HPP
