#include "abstract_tilemap.hpp"


abstract_tilemap::abstract_tilemap (const vector2<int>& nscale) {
    scale = nscale;
    data = new tile*[tile_count()];
    for (int i = 0; i < tile_count(); ++i) {
        data[i] = new tile();
    }

}

abstract_tilemap::abstract_tilemap (const abstract_tilemap& copy) {
    *this = copy;
}

abstract_tilemap& abstract_tilemap::operator= (const abstract_tilemap& copy) {
    if (this != &copy) {
        scale = copy.scale;
        data = new tile*[tile_count()];
        for (int i = 0; i < tile_count(); ++i) {
            data[i] = copy.data[i]; //TODO it will not copy (check)
        }
    }
    return *this;
}

abstract_tilemap::~abstract_tilemap () {
    for (int i = 0; i < tile_count(); ++i) delete data[i];
    delete[] data;
}

void abstract_tilemap::serialize (json& package) const {
    package["type"] = type();
    scale.serialize(package["scale"]);
    package["data"] = json::array();
    for (int i = 0; i < tile_count(); ++i) {
        json j;
        data[i]->serialize(j); //TODO no alloc
        package["data"].push_back(j);
    }
}

void abstract_tilemap::deserialize (json& package) {
    scale.deserialize(package["scale"]);
    json j_data = package["data"];
    delete [] data;
    data = new tile*[tile_count()];
    for (int i = 0; i < tile_count(); ++i) {
        // TODO delete old tiles
        data[i] = json_tools::unpack_tile(j_data[i]);
    }
}

const tile* abstract_tilemap::get_tile (const vector2<int>& position) const {
    return get_tile(position.x, position.y);
}

void abstract_tilemap::set_tile (const vector2<int>& position, tile* item) {
    set_tile(position.x, position.y, item);
}

bool abstract_tilemap::is_valid (const vector2<int>& position) const {
    return is_valid(position.x, position.y);
}

const tile& abstract_tilemap::operator[] (const vector2<int>& position) const {
    if (!is_valid(position)) throw todo_exception("tilemap overflow exception");
    return *get_tile(position.x, position.y);
}

int abstract_tilemap::tile_count () const {
    return scale.x * scale.y;
}


