#ifndef LOGIC_PATHFINDER_HPP
#define LOGIC_PATHFINDER_HPP

#include "../base/includes.hpp"
#include "../tiles/base_tile.hpp"
#include "../tilemap/square.hpp"

#define m_max(a, b)            (((a) > (b)) ? (a) : (b))
#define m_min(a, b)            (((a) < (b)) ? (a) : (b))



class pathfinder {
public:
    explicit pathfinder(tilemap::square &map);
    ~pathfinder() = default;

    std::list<stts::vector2<int>> find_path(const stts::vector2<int>& from, const stts::vector2<int>& to);

private:
    tilemap::square& map;
    std::list<tile::base_tile*> open_list;
    tile::base_tile* begin_node;
    tile::base_tile* end_node;
    std::list<tile::base_tile*> free_list;
    std::list<stts::vector2<int>> path;

    bool can_walk(const stts::vector2<int>& from, const stts::vector2<int>& to);

    void identify_successors(tile::base_tile* node);
    stts::vector2<int> jump(int x, int y, int px, int py);
    std::vector<tile::base_tile*> find_neighbors(tile::base_tile* cellNode);
    void backtrace(tile::base_tile* node);
    std::list<stts::vector2<int>> expand_path();
    std::vector<stts::vector2<int>> interpolate(int x0, int y0, int x1, int y1);

    void realse(tile::base_tile* node) { // TODO: (probably) (re)move this when WE will be done.
        free_list.push_back(node);
    }
    tile::base_tile* create() { // TODO: (probably) (re)move this when WE will be done.
        if (!free_list.empty()) {
            tile::base_tile* node = free_list.front();
            free_list.pop_front();
            node->clear();
            return node;
        }

        return new tile::base_tile();
    }


    int manhattan(int x, int y) { // TODO: (probably) move this to a_tilemap when WE will be done.
        return x + y;
    }

    int octile(int dx, int dy) { // TODO: (probably) move this to a_tilemap when WE will be done.
        double F = sqrt(2) - 1;
        return (int)(dx < dy ? F * dx + dy : F * dy + dx);
    }
};


#endif //LOGIC_PATHFINDER_HPP
