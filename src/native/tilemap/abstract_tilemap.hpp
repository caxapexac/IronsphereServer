#ifndef LOGIC_ABSTRACT_TILEMAP_HPP
#define LOGIC_ABSTRACT_TILEMAP_HPP

#include "../base/includes.hpp"
#include "../structs/vector2.hpp"
#include "../tiles/tile.hpp"
#include "../tiles/tile_money.hpp"
#include "../tiles/tile_damage.hpp"

//TODO foreach iterator on tiles
class abstract_tilemap : public iserializable, public ityped {
    OBSOLETE friend class json_tools;
protected:
    vector2<int> scale; // X - width, Y - height
    tile** data;

public:
    explicit abstract_tilemap (const vector2<int>& nscale = vector2<int>(0, 0));
    abstract_tilemap (const abstract_tilemap& copy);
    abstract_tilemap& operator= (const abstract_tilemap& copy);
    ~abstract_tilemap () override;
    void serialize (json& package) const override;
    void deserialize (json& package) override;

    tile& operator[] (const vector2<int>& position);
    tile* get_tile (const vector2<int>& position);
    void set_tile (const vector2<int>& position, tile* item);
    bool is_valid(const vector2<int>& position) const;
    std::vector<tile*> get_neighbours (const vector2<int>& point);
    float get_distance (const vector2<int>& source, const vector2<int>& destination);
    std::queue<vector2<int>> get_path(const vector2<int>& source, const vector2<int>& destination);

    virtual tile* get_tile (int x, int y) = 0;
    virtual void set_tile (int x, int y, tile* item) = 0;
    virtual bool is_valid(int x, int y) const = 0;
    virtual std::vector<tile*> get_neighbours (int x, int y) = 0;
    virtual float get_distance (int source_x, int source_y, int destination_x, int destination_y) = 0;
    virtual std::queue<vector2<int>> get_path(int source_x, int source_y, int destination_x, int destination_y) = 0;

protected:
    int tile_count() const;
};

#endif //LOGIC_ABSTRACT_TILEMAP_HPP
