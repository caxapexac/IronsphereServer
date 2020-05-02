#ifndef LOGIC_TILE_HPP
#define LOGIC_TILE_HPP

#include "../base/interfaces.hpp"

class tile : public iserializable {
private:
    float height; // Ground

public:
    explicit tile (float nheight = 0);
    tile (const tile& copy);
    tile& operator= (const tile& copy);
    void serialize (json& package) const override;
    void deserialize (json& package) override;

    float get_height ();

    virtual void on_unit_enter (unit& sender);
    virtual void on_unit_stay (unit& sender);
    virtual void on_unit_exit (unit& sender);
};

#endif //LOGIC_TILE_HPP
