#ifndef LOGIC_ABSTRACT_TILEMAP_HPP
#define LOGIC_ABSTRACT_TILEMAP_HPP

#include "../base/interfaces.hpp"
#include "../structs/vector2.hpp"
#include "tile.hpp"
#include "tile_money.hpp"
#include "tile_damage.hpp"

//TODO foreach iterator on tiles
class abstract_tilemap : public iserializable {
protected:
    vector2<int> scale; // X - width, Y - height
    tile** data;

public:
    explicit abstract_tilemap ();
    abstract_tilemap (const abstract_tilemap& copy);
    abstract_tilemap& operator= (const abstract_tilemap& copy);
    ~abstract_tilemap () override;
    void serialize (json& package) const override;
    void deserialize (json& package) override;

    virtual tile& operator[] (const vector2<int>& position) const;
    virtual tile* get_tile (const vector2<int>& position) const;
    virtual std::vector<vector2<int>> get_path(vector2<int> source, vector2<int> destination) = 0;

protected:
    int size() const;
    virtual bool is_valid(const vector2<int>& position) const;
    virtual std::vector<tile*> get_neighbours (vector2<int> point) = 0;
    virtual float get_euristic_distance (vector2<int> source, vector2<int> destination) = 0;
};

#endif //LOGIC_ABSTRACT_TILEMAP_HPP
