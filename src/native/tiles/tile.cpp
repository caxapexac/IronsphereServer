#include "tile.hpp"
#include "../entities/unit.hpp"

tile::tile (float nheight) : height(nheight), occupier_id(0) { }

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
    package["type"] = type();
    package["height"] = height;
    package["occupier_id"] = occupier_id;
}

void tile::deserialize (json& package) {
    height = package["height"];
    occupier_id = package["occupier_id"];
}

const std::string& tile::type () const {
    return tile_type;
}

float tile::get_height () const {
    return height;
}

int tile::get_occupier_id () const {
    return occupier_id;
}

bool tile::is_occupied () const {
    return occupier_id != 0;
}

void tile::on_unit_enter (unit& sender) {
    if (is_occupied() && sender.get_id() != occupier_id) throw todo_exception("Uh, sama lamaa duma lama you assuming I'm a human\n What I gotta do to get it through to you I'm superhuman\nInnovative and I'm made of rubber\nSo that anything you say is ricocheting off of me and it'll glue to you\nI'm devastating, more than ever demonstrating\nHow to give a motherfuckin' audience a feeling like it's levitating\nNever fading, and I know the haters are forever waiting\nFor the day that they can say I fell off, they'd be celebrating\nCause I know the way to get 'em motivated\nI make elevating music, you make elevator music");
    occupier_id = sender.get_id();
    // Do nothing
}

void tile::on_unit_touch (unit& sender) {
    occupier_id = sender.get_id(); // FIXME delete this (only for debug)
    // Do nothing
}

void tile::on_unit_exit (unit& sender) {
    if (occupier_id != sender.get_id()) throw todo_exception("What is the strength, bro?");
    occupier_id = 0;
    // Do nothing
}






