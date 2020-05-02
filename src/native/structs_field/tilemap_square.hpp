#ifndef LOGIC_TILEMAP_SQUARE_HPP
#define LOGIC_TILEMAP_SQUARE_HPP

#include "abstract_tilemap.hpp"

class tilemap_square : public abstract_tilemap {
public:
    static const std::string type;

    explicit tilemap_square ();

    tile& operator[] (const vector2<int>& position) const override;
    tile* get_tile (const vector2<int>& position) const override;
    std::vector<vector2<int>> get_path (vector2<int> source, vector2<int> destination) override;

protected:
    bool is_valid (const vector2<int>& position) const override;
    std::vector<tile*> get_neighbours (vector2<int> point) override;
    float get_euristic_distance (vector2<int> source, vector2<int> destination) override;
};

#endif //LOGIC_TILEMAP_SQUARE_HPP
