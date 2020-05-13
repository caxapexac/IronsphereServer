#ifndef LOGIC_TILE_MONEY_HPP
#define LOGIC_TILE_MONEY_HPP

#include "tile.hpp"

const std::string tile_money_type = "tile_money";
class tile_money : public tile {
private:
    int money;
public:
    explicit tile_money (float nheight = 0, int nmoney = 1);
    void serialize (json& package) const override;
    void deserialize (json& package) override;
    const std::string& type () const override;

    void on_unit_enter (unit& sender) override;
    void on_unit_touch (unit& sender) override;
    void on_unit_exit (unit& sender) override;
};

#endif //LOGIC_TILE_MONEY_HPP
