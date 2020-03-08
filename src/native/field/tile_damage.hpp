#ifndef LOGIC_TILE_DAMAGE_HPP
#define LOGIC_TILE_DAMAGE_HPP

#include "tile.hpp"
#include "tile_money.hpp"


class tile_damage : public tile {
private:
    int damage;
public:
    explicit tile_damage (int ndamage, float nheight = 1.0f, int ntexture = 0);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;
    void update () override;
};

tile_damage::tile_damage (int ndamage, float nheight, int ntexture) : tile(nheight, ntexture), damage(ndamage) { }

void tile_damage::serialize (json& package, serializers type) const {
    tile::serialize(package, type);
    package["type"] = "damage";
    package["damage"] = damage;
}

void tile_damage::deserialize (json& package) {
    tile::deserialize(package);
    damage = package["damage"].get<int>();
    // TODO json ctor
}

void tile_damage::update () {
    //get_unit().get_player().hp--;
}

#endif //LOGIC_TILE_DAMAGE_HPP
