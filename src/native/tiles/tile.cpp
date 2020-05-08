#include "tile.hpp"


tile::tile (float nheight) : height(nheight) { }

tile::tile (const tile& copy) {
    *this = copy;
}

tile& tile::operator= (const tile& copy) {
    if (this != &copy) {
        height = copy.height;
    }
    return *this;
}

void tile::serialize (json& package) const {
    package["height"] = height;
}

void tile::deserialize (json& package) {
    height = package["height"];
}

float tile::get_height () {
    return height;
}

void tile::on_unit_enter (unit& sender) {
    // Do nothing
}

void tile::on_unit_stay (unit& sender) {
    // Do nothing
}

void tile::on_unit_exit (unit& sender) {
    // Do nothing
}
