// #ifndef LOGIC_PATHFINDER_HPP
// #define LOGIC_PATHFINDER_HPP
//
// #include <malloc.h>
// #include <string>
// #include <vector>
// #include <tuple>
// #include <list>
// #include <cmath>
// #include <cstring>
// #include "../structs_field/tile.hpp"
// #include "../structs/vector2.hpp"
// #include "../structs_field/tilemap_square.hpp"
//
// #define m_max(a, b)            (((a) > (b)) ? (a) : (b))
// #define m_min(a, b)            (((a) < (b)) ? (a) : (b))
//
// class tile_plus {
// public:
//     tile* content;
//     int f, g, h;
//     vector2<int> position;
//     bool opened;
//     bool closed;
//     tile_plus* parent;
//
//     void clear() {
//         f = 0;
//         g = 0;
//         h = 0;
//         opened = false;
//         closed = false;
//         parent = nullptr;
//     }
//
//     tile_plus() {
//         clear();
//     }
// };
//
//
//
// class pathfinder {
// public:
//     explicit pathfinder(tilemap_square &map);
//     ~pathfinder() = default;
//
//     std::list<vector2<int>> find_path(vector2<int>& from, vector2<int>& to);
//
// private:
//     tilemap_square& map;
//     std::list<tile_plus*> open_list;
//     tile_plus* begin_node;
//     tile_plus* end_node;
//     std::list<tile_plus*> free_list;
//     std::list<vector2<int>> path;
//     tile_plus* grid;
//
//     bool can_walk(int x, int y);
//     tile_plus* get_plus(int x, int y);
//
//     void identify_successors(tile_plus* node);
//     std::tuple<int, int> jump(int x, int y, int px, int py);
//     std::vector<tile_plus*> find_neighbors(tile_plus* cellNode);
//     void backtrace(tile_plus* node);
//     std::list<vector2<int>> expand_path();
//     std::vector<vector2<int>> interpolate(int x0, int y0, int x1, int y1);
//
//     void realse(tile_plus* node) { // TODO: (probably) (re)move this when WE will be done.
//         free_list.push_back(node);
//     }
//     tile_plus* create() { // TODO: (probably) (re)move this when WE will be done.
//         if (!free_list.empty()) {
//             tile_plus* node = free_list.front();
//             free_list.pop_front();
//             node->clear();
//             return node;
//         }
//
//         return new tile_plus();
//     }
//
//
//     int manhattan(int x, int y) { // TODO: (probably) move this to a_tilemap when WE will be done.
//         return x + y;
//     }
//     int octile(int dx, int dy) { // TODO: (probably) move this to a_tilemap when WE will be done.
//         double F = sqrt(2) - 1;
//         return (int)(dx < dy ? F * dx + dy : F * dy + dx);
//     }
//
// };
//
//
// #endif //LOGIC_PATHFINDER_HPP
