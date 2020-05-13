#ifndef LOGIC_TILEMAP_HEXAGONAL_HPP
#define LOGIC_TILEMAP_HEXAGONAL_HPP

#include "abstract_tilemap.hpp"

const std::string tilemap_hexagonal_type = "tilemap_hexagonal";
class tilemap_hexagonal : public abstract_tilemap {
public:
    const std::string& type () const override;
    const tile* get_tile (int x, int y) const override;
    void set_tile (int x, int y, tile* item) override;
    std::queue<vector2<int>> get_path (const vector2<int>& source, const vector2<int>& destination) override;
protected:
    bool is_valid (const vector2<int>& position) const override;
    std::vector<tile*> get_neighbours (vector2<int> point) override;
    float get_euristic_distance (vector2<int> source, vector2<int> destination) override;
};

#endif //LOGIC_TILEMAP_HEXAGONAL_HPP
