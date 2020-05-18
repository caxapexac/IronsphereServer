#ifndef LOGIC_TILEMAP_HEXAGONAL_HPP
#define LOGIC_TILEMAP_HEXAGONAL_HPP

#include "abstract_tilemap.hpp"

const std::string tilemap_hexagonal_type = "tilemap_hexagonal";
class tilemap_hexagonal : public abstract_tilemap {
public:
    const std::string& type () const override;
    tile& get_tile (int x, int y) override;
    void set_tile (int x, int y, tile* item) override;
    bool is_valid (int x, int y) const override;
    std::vector<vector2<int>> get_neighbours (int x, int y) override;
    float get_distance (int source_x, int source_y, int destination_x, int destination_y) override;
    std::queue<vector2<int>> get_path (int source_x, int source_y, int destination_x, int destination_y) override;
};

#endif //LOGIC_TILEMAP_HEXAGONAL_HPP
