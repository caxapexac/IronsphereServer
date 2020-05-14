#ifndef LOGIC_TILE_HPP
#define LOGIC_TILE_HPP

#include "../base/includes.hpp"

const std::string tile_type = "tile";
class tile : public iserializable, public ityped {
private:
    float height;
    int occupier_id;

public:
    explicit tile (float nheight = 0);
    tile (const tile& copy);
    tile& operator= (const tile& copy);
    void serialize (json& package) const override;
    void deserialize (json& package) override;
    const std::string& type () const override;

    float get_height () const;
    int get_occupier_id () const;
    bool is_occupied () const;

    virtual void on_unit_enter (unit& sender);
    virtual void on_unit_touch (unit& sender) const;
    virtual void on_unit_exit (unit& sender);
};

#endif //LOGIC_TILE_HPP
