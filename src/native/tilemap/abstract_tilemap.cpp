#include "abstract_tilemap.hpp"


abstract_tilemap::abstract_tilemap (const vector2<int>& nscale) {
    scale = nscale;
    data = new tile*[size()];
    for (int i = 0; i < size(); ++i) {
        data[i] = new tile();
    }

}

abstract_tilemap::abstract_tilemap (const abstract_tilemap& copy) {
    *this = copy;
}

abstract_tilemap::~abstract_tilemap () {
    for (int i = 0; i < size(); ++i) delete data[i];
    delete[] data;
}

abstract_tilemap& abstract_tilemap::operator= (const abstract_tilemap& copy) {
    if (this != &copy) {
        scale = copy.scale;
        data = new tile*[size()];
        for (int i = 0; i < size(); ++i) {
            data[i] = copy.data[i]; //TODO it will not copy (check)
        }
    }
    return *this;
}

void abstract_tilemap::serialize (json& package) const {
    scale.serialize(package["scale"]);
    package["data"] = json::array();
    for (int i = 0; i < size(); ++i) {
        json j;
        data[i]->serialize(j); //TODO no alloc
        package["data"].push_back(j);
    }
}

void abstract_tilemap::deserialize (json& package) {
    scale.deserialize(package["scale"]);
    json j_data = package["data"];
    delete [] data;
    data = new tile*[size()];
    for (int i = 0; i < size(); ++i) {
        // TODO delete old tiles
        data[i] = json_tools::unpack_tile(j_data[i]);
    }
}

const tile& abstract_tilemap::operator[] (const vector2<int>& position) const {
    //if (!is_valid(position)) throw; TODO
    return *get_tile(position);
}

bool abstract_tilemap::is_valid (const vector2<int>& position) const {
    return !(position.x < 0 || position.x >= scale.x || position.y < 0 || position.y >= scale.y);
}

const tile* abstract_tilemap::get_tile (const vector2<int>& position) const {
    return data[position.y * scale.y + position.x];
}

void abstract_tilemap::set_tile (const vector2<int>& position, tile* item) {
    delete get_tile(position);
    data[position.y * scale.y + position.x] = item;
}


int abstract_tilemap::size () const {
    return scale.x * scale.y;
}

