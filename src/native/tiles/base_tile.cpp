#include "base_tile.hpp"
#include "../entities/unit.hpp"

tile::base_tile::base_tile (float nheight) : height(nheight), occupier_uid(0) { }

tile::base_tile::base_tile (json& package) {
    base_tile::deserialize(package);
}

tile::base_tile::base_tile (const base_tile& copy) {
    *this = copy;
}

tile::base_tile& tile::base_tile::operator= (const base_tile& copy) {
    if (this != &copy) {
        height = copy.height;
    }
    return *this;
}

void tile::base_tile::serialize (json& package) const {
    package[j_typed::type] = type();
    package[j_base_tile::height] = height;
    package[j_base_tile::occupier_uid] = occupier_uid;
}

void tile::base_tile::deserialize (json& package) {
    height = package[j_base_tile::height];
    occupier_uid = package[j_base_tile::occupier_uid];
}

void tile::base_tile::serialize_public (json& package) {
    serialize(package);
    package[j_base_tile::occupier_uid] = 0;
}

const std::string& tile::base_tile::type () const {
    return j_base_tile::type;
}

float tile::base_tile::get_height () const {
    return height;
}

void tile::base_tile::set_height (float nheight) {
    height = nheight;
}

int tile::base_tile::get_occupier_id () const {
    return occupier_uid;
}

bool tile::base_tile::is_occupied () const {
    return occupier_uid != 0;
}

void tile::base_tile::on_unit_enter (ent::unit& sender) {
    if (is_occupied() && sender.get_id() != occupier_uid) throw todo_exception("Uh, sama lamaa duma lama you assuming I'm a human\n What I gotta do to get it through to you I'm superhuman\nInnovative and I'm made of rubber\nSo that anything you say is ricocheting off of me and it'll glue to you\nI'm devastating, more than ever demonstrating\nHow to give a motherfuckin' audience a feeling like it's levitating\nNever fading, and I know the haters are forever waiting\nFor the day that they can say I fell off, they'd be celebrating\nCause I know the way to get 'em motivated\nI make elevating music, you make elevator music");
    occupier_uid = sender.get_id();
    // Do nothing
}

void tile::base_tile::on_unit_touch (ent::unit& sender) {
    occupier_uid = sender.get_id(); // FIXME delete this (only for debug)
    // Do nothing
}

void tile::base_tile::on_unit_exit (ent::unit& sender) {
    if (occupier_uid != sender.get_id()) throw todo_exception("What is the strength, bro?");
    occupier_uid = 0;
    // Do nothing
}










