#ifndef LOGIC_TILEMAP_SQUARE_HPP
#define LOGIC_TILEMAP_SQUARE_HPP

#include "abstract_tilemap.hpp"

const std::string tilemap_square_type = "tilemap_square";
class tilemap_square : public abstract_tilemap {
public:
    explicit tilemap_square(const vector2<int>& nscale = vector2<int>(0, 0));
    const std::string& type () const override;
    const tile* get_tile (int x, int y) const override;
    void set_tile (int x, int y, tile* item) override;
    std::queue<vector2<int>> get_path (const vector2<int>& source, const vector2<int>& destination) override;
protected:
    bool is_valid (const vector2<int>& position) const override;
    std::vector<tile*> get_neighbours (vector2<int> point) override;
    float get_euristic_distance (vector2<int> source, vector2<int> destination) override;
};

#endif //LOGIC_TILEMAP_SQUARE_HPP
