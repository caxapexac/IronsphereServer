#ifndef LOGIC_ABSTRACT_TILEMAP_HPP
#define LOGIC_ABSTRACT_TILEMAP_HPP

#include "../base/interfaces.hpp"
#include "tile.hpp"
#include "tile_money.hpp"
#include "tile_damage.hpp"

//TODO foreach iterator on tiles
class abstract_tilemap : public iserializable {
    friend class tester;
protected:
    vector2<int> scale; // X - width, Y - height
    tile** data;

public:
    explicit abstract_tilemap (const vector2<int>& nscale);
    explicit abstract_tilemap (const json& package);
    abstract_tilemap (const abstract_tilemap& copy);
    ~abstract_tilemap () override;
    abstract_tilemap& operator= (const abstract_tilemap& copy);
    void serialize (json& package, serializers type = serial_save) const override;
    void deserialize (json& package) override;

    virtual tile& operator[] (const vector2<int>& position) const;
    virtual bool is_valid(const vector2<int>& position) const;
    virtual tile& get_tile (const vector2<int>& position);
    virtual std::shared_ptr<a_unit> get_unit (const vector2<int>& position);

    virtual int size () const;
    virtual vector2<int> get_scale();

    virtual std::shared_ptr<vector2<int>> get_path(vector2<int> source, vector2<int> destination);
    virtual std::vector<vector2<int>*>& get_neighbours (vector2<int> point) = 0; // if cell outside of the field returns nullptr!!!
    virtual float get_euristic_distance (vector2<int> source, vector2<int> destination) = 0;
};


abstract_tilemap::abstract_tilemap (const vector2<int>& nscale) : scale(nscale) {
    data = new tile*[scale.x * scale.y];
    //TODO check will it work
    //Test
    for (int i = 0; i < size(); ++i) {
        if (i % 4) data[i] = new tile(0.9f, 0);
        else data[i] = new tile_money(10, 0.8f, 1);
    }
    //
}

abstract_tilemap::abstract_tilemap (const json& package) {
    scale.deserialize(package["scale"]);
    for (int i = 0; i < size(); ++i) delete data[i]; //TODO
    delete[] data; //TODO
    data = new tile*[size()];
    for (int i = 0; i < size(); ++i) {
        // TODO simplify
        data[i] = json_tools::unpack_tile(package["data"].at(i));

        if (package["data"]["type"] == nullptr) data[i] = new tile();
        else if (package["data"]["type"] == "damage") data[i] = new tile_damage(0);
        else if (package["data"]["type"] == "money") data[i] = new tile_money(0);
        data[i]->deserialize(package["data"]);
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

void abstract_tilemap::serialize (json& package, serializers type) const {
    scale.serialize(package["scale"], type);
    package["data"] = json::array();
    for (int i = 0; i < size(); ++i) {
        json j;
        data[i]->serialize(j, type); //TODO no alloc
        package["data"].push_back(j);
    }
}

void abstract_tilemap::deserialize (json& package) {
    // TODO json_tools
}

tile& abstract_tilemap::operator[] (const vector2<int>& position) const {
    //if (!is_valid(position)) throw; TODO
    return *data[position.y * scale.y + position.x];
}

bool abstract_tilemap::is_valid (const vector2<int>& position) const {
    return !(position.x < 0 || position.x >= scale.x || position.y < 0 || position.y >= scale.y);
}

tile& abstract_tilemap::get_tile (const vector2<int>& position) {
    return (*this)[position];
}

std::shared_ptr<a_unit> abstract_tilemap::get_unit (const vector2<int>& position) {
    return get_tile(position).get_unit();
}

int abstract_tilemap::size () const {
    return scale.x * scale.y;
}

std::shared_ptr<vector2<int>> abstract_tilemap::get_path (vector2<int> source, vector2<int> destination) {
    // ^ < > V
}



#endif //LOGIC_ABSTRACT_TILEMAP_HPP
