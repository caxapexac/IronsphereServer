#ifndef LOGIC_TILE_DAMAGE_HPP
#define LOGIC_TILE_DAMAGE_HPP

#include "tile.hpp"

const std::string tile_damage_type = "tile_damage";
class tile_damage : public tile {
private:
    int damage;
public:
    explicit tile_damage (float nheight = 0, int ndamage = 1);
    void serialize (json& package) const override;
    void deserialize (json& package) override;
    const std::string& type () const override;

    void on_unit_enter (unit& sender) override;
    void on_unit_touch (unit& sender) override;
    void on_unit_exit (unit& sender) override;
};


#endif //LOGIC_TILE_DAMAGE_HPP
