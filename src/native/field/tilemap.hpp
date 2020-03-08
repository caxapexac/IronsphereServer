#ifndef LOGIC_TILEMAP_HPP
#define LOGIC_TILEMAP_HPP

#include <memory>
#include "tile.hpp"
#include "../base/interfaces.hpp"
#include "../units/unit.hpp"
#include "tile_money.hpp"
#include "tile_damage.hpp"

// L1
//TODO foreach iterator on tiles
class tilemap : public iserializable {
    friend class tester;
protected:
    vector2<int> scale; // X - width, Y - height
    tile** data;

    tile& operator[] (const vector2<int>& position) const;

public:
    explicit tilemap (const vector2<int>& nscale);
    tilemap (const tilemap& copy);
    ~tilemap () override;
    tilemap& operator= (const tilemap& copy);
    void serialize (json& package, serializers type = serial_save) const override;
    void deserialize (json& package) override;

    bool is_valid(const vector2<int>& position) const;
    tile& get_tile (const vector2<int>& position);
    std::shared_ptr<unit> get_unit (const vector2<int>& position);

    int size () const;

    virtual std::shared_ptr<vector2<int>> get_path(vector2<int> source, vector2<int> destination);
};

tile& tilemap::operator[] (const vector2<int>& position) const {
    //if (!is_valid(position)) throw; TODO
    return *data[position.y * scale.y + position.x];
}

tilemap::tilemap (const vector2<int>& nscale) : scale(nscale) {
    data = new tile*[scale.x * scale.y];
    //TODO check will it work
    //Test
    for (int i = 0; i < size(); ++i) {
        if (i % 4) data[i] = new tile(0.9f, 0);
        else data[i] = new tile_money(10, 0.8f, 1);
    }
    //
}

tilemap::tilemap (const tilemap& copy) {
    *this = copy;
}

tilemap::~tilemap () {
    for (int i = 0; i < size(); ++i) delete data[i];
    delete[] data;
}

tilemap& tilemap::operator= (const tilemap& copy) {
    if (this != &copy) {
        scale = copy.scale;
        data = new tile*[size()];
        for (int i = 0; i < size(); ++i) {
            data[i] = new tile(); //TODO it will not work with inheritance
            //data[i] = copy.data[i]; //TODO it will not copy (check)
        }
    }
    return *this;
}

void tilemap::serialize (json& package, serializers type) const {
    scale.serialize(package["scale"], type);
    package["data"] = json::array();
    for (int i = 0; i < size(); ++i) {
        json j;
        data[i]->serialize(j, type); //TODO no alloc
        package["data"].push_back(j);
    }
}

void tilemap::deserialize (json& package) {
    scale.deserialize(package["scale"]);
    for (int i = 0; i < size(); ++i) delete data[i]; //TODO
    delete[] data; //TODO
    data = new tile*[size()];
    for (int i = 0; i < size(); ++i) {
        // TODO simplify
        if (package["data"]["type"] == nullptr) data[i] = new tile();
        else if (package["data"]["type"] == "damage") data[i] = new tile_damage(0);
        else if (package["data"]["type"] == "money") data[i] = new tile_money(0);
        data[i]->deserialize(package["data"]);
    }
}

bool tilemap::is_valid (const vector2<int>& position) const {
    return !(position.x < 0 || position.x >= scale.x || position.y < 0 || position.y >= scale.y);
}

tile& tilemap::get_tile (const vector2<int>& position) {
    return (*this)[position];
}

std::shared_ptr<unit> tilemap::get_unit (const vector2<int>& position) {
    return get_tile(position).get_unit();
}

int tilemap::size () const {
    return scale.x * scale.y;
}

std::shared_ptr<vector2<int>> tilemap::get_path (vector2<int> source, vector2<int> destination) {
    // ^ < > V
}

#endif //LOGIC_TILEMAP_HPP
