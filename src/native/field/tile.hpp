#ifndef LOGIC_TILE_HPP
#define LOGIC_TILE_HPP

#include <memory>
#include "../base/interfaces.hpp"
#include "../units/unit.hpp"
#include "../a_temp/id.hpp"

class tile : public iserializable {
private:
    float height; // Ground
    int texture; // Ground TODO maybe texture is fixed/static/const based on the type of the tile
    std::shared_ptr<unit> occupier; // Not serializable

public:
    explicit tile (float nheight = 1.0f, int ntexture = 0);
    tile (const tile& copy);
    tile& operator= (const tile& copy);
    virtual void serialize (json& package, serializers type) const override;
    virtual void deserialize (json& package) override;

    float get_height ();
    std::shared_ptr<unit> get_unit (); ///TODO is_empty()
    void set_unit (std::shared_ptr<unit> nunit);

    /// Action on occupier
    virtual void update();
};

tile::tile (float nheight, int ntexture) : height(nheight), texture(ntexture) { }

tile::tile (const tile& copy) {
    *this = copy;
}

tile& tile::operator= (const tile& copy) {
    if (this != &copy) {
        height = copy.height;
        texture = copy.texture;
        occupier = nullptr;
    }
    return *this;
}

void tile::serialize (json& package, serializers type) const {
    // TODO type (how to deserialize tile_damage etc)
    package["height"] = height;
    package["texture"] = texture;
}

void tile::deserialize (json& package) {
    height = package["height"];
    texture = package["texture"].get<int>();
}

float tile::get_height () {
    return height;
}

std::shared_ptr<unit> tile::get_unit () {
    return occupier;
}

void tile::set_unit (std::shared_ptr<unit> nunit) {
    occupier = nunit;
    //TODO optional log
}

void tile::update () {
    return;
    // Do nothing
}

#endif //LOGIC_TILE_HPP
