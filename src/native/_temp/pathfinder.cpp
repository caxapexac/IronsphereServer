#include "pathfinder.hpp"

// TODO: (probably) clear this when WE will be done.

pathfinder::pathfinder(tilemap::square &map) : map(map) {}

std::list<stts::vector2<int>> pathfinder::find_path(const stts::vector2<int>& from, const stts::vector2<int>& to) {
     map.clear_tiles();
     path.clear();

     begin_node = &map.get_tile(from.x, from.y);
     end_node = &map.get_tile(to.x, to.y);

     // set the `g` and `f` value of the start node to be zero
     begin_node->g = 0;
     begin_node->f = 0;

     // push the begin node into the open list
     open_list.push_back(begin_node);
     begin_node->opened = true;

    tile::base_tile* node = nullptr;

     while (!open_list.empty()) {
         // pop the position of node which has the minimum `f` value.
         node = open_list.front();
         open_list.pop_front();
         node->closed = true;
         if (node == end_node) {
             backtrace(end_node);
             return expand_path();
         }

         identify_successors(node);
     }

     return expand_path();
}



bool pathfinder::can_walk(const stts::vector2<int>& from, const stts::vector2<int>& to) {
     if (((to.x < 0) || (to.x >= map.get_scale().x)) || ((to.y < 0) || (to.y >= map.get_scale().y))) return false;
     tile::base_tile* node = &map.get_tile(to.x, to.y);
     return node && !node->is_occupied() && (abs(map.get_tile(to.x, to.y).get_height() - node->get_height()) < 20);
}

void pathfinder::identify_successors(tile::base_tile* node) {
     tile::base_tile* jumpnode = nullptr;
     int d = 0;
     int g = 0;

     std::vector<tile::base_tile*> cells = find_neighbors(node);
     for (auto itr = cells.begin(); itr != cells.end(); ++itr) {
         auto result = jump((*itr)->position.x, (*itr)->position.y, node->position.x, node->position.y);

         int jx = result.x;
         int jy = result.y;
         if (jx < 0) // NEEDED????
             continue;

         jumpnode = &map.get_tile(jx, jy);
         if (jumpnode->closed) continue;

         // include distance, as parent may not be immediately adjacent:
         d = octile(abs(jx - node->position.x), abs(jy - node->position.y));
         g = node->g + d;

         if (!jumpnode->opened || g < jumpnode->g) {
             jumpnode->g = g;
             if (jumpnode->h == 0)
                 jumpnode->h = manhattan(abs(jx - end_node->position.x), abs(jy - end_node->position.y));
             jumpnode->f = jumpnode->g + jumpnode->h;
             jumpnode->parent = node;

             if (!jumpnode->opened) {
                 open_list.push_back(jumpnode);
                 open_list.sort([] (const tile::base_tile* a, const tile::base_tile* b)->bool // TODO: replace with in-place search.
                                 {
                                     return a->f < b->f;
                                 });

                 jumpnode->opened = true;
             }
         }
     }
 }

stts::vector2<int> pathfinder::jump(int x, int y, int px, int py) {
     int dx = x - px;
     int dy = y - py;

     if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y)))
         return stts::vector2<int>(-1, -1);

     if (&map.get_tile(x, y) == end_node)
         return stts::vector2<int>(x, y);

     // check for forced neighbors
     // along the diagonal
     if ( dx != 0 && dy != 0 ) {
         if ( (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x - dx, y + dy)) && !can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x - dx, y)))
            || (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + dx, y - dy)) && !can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y - dy))) )
             return stts::vector2<int>(x, y);

         if ((jump(x + dx, y, x, y).x != -1) || (jump(x, y + dy, x, y).x != -1))
             return stts::vector2<int>(x, y);

     } else { // horizontally/vertically
         if (dx != 0) {
             if ((can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + dx, y + 1)) && !can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y + 1)))
                || (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + dx, y - 1)) && !can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y - 1))) )
                 return stts::vector2<int>(x, y);

         } else {
             if ((can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + 1, y + dy)) && !can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + 1, y)))
                || (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x - 1, y + dy)) && !can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x - 1, y))))
                 return stts::vector2<int>(x, y);
         }
     }

     return jump(x + dx, y + dy, x, y);
 }

 std::vector<tile::base_tile*> pathfinder::find_neighbors(tile::base_tile* cellNode) {
     std::vector<tile::base_tile*> neighbours;

     int x = cellNode->position.x;
     int y = cellNode->position.y;

     // directed pruning: can ignore most neighbors, unless forced.
     if ( cellNode->parent ) {
         // get the normalized direction of travel
         int dx = (x - cellNode->parent->position.x) / m_max(abs(x - cellNode->parent->position.x), 1);
         int dy = (y - cellNode->parent->position.y) / m_max(abs(y - cellNode->parent->position.y), 1);

         // search diagonally
         if ( dx != 0 && dy != 0 ) {
             if (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y + dy))) // down
                 neighbours.push_back(&map.get_tile(x, y + dy));

             if (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + dx, y))) // right
                 neighbours.push_back(&map.get_tile(x + dx, y));

             if (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + dx, y + dy))) // right down
                 neighbours.push_back(&map.get_tile(x + dx, y + dy));

             if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x - dx, y))) // 0 1
                 neighbours.push_back(&map.get_tile(x - dx, y + dy));

             if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y - dy))) // 1 0
                 neighbours.push_back(&map.get_tile(x + dx, y - dy));
         } else { // search horizontally/vertically
             if ( dx == 0 ) {
                 if (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y + dy)))
                     neighbours.push_back(&map.get_tile(x, y + dy));

                 if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + 1, y)))
                     neighbours.push_back(&map.get_tile(x + 1, y + dy));

                 if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x - 1, y)))
                     neighbours.push_back(&map.get_tile(x - 1, y + dy));
             } else {
                 if (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + dx, y)))
                     neighbours.push_back(&map.get_tile(x + dx, y));

                 if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y + 1)))
                     neighbours.push_back(&map.get_tile(x + dx, y + 1));

                 if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y - 1)))
                     neighbours.push_back(&map.get_tile(x + dx, y - 1));
             }
         }
     } else {
         for (int i = -1; i <= 1; ++i) {
             for (int j = -1; j <= 1; ++j) {
                 if ((i == 0) && (j == 0)) continue;
                 if (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + i, y + j))) neighbours.push_back(&map.get_tile(x + i, y + j));
             }
         }
     }

     return neighbours;
 }

 void pathfinder::backtrace(tile::base_tile* node) {
     stts::vector2<int> point;

     do {
         point.x = node->position.x;
         point.y = node->position.y;
         path.push_back(point);

         node = node->parent;
     } while (node->parent);

     path.reverse();
 }

 std::list<stts::vector2<int>> pathfinder::expand_path() {
     std::list<stts::vector2<int>> lastpath;

     int len = (int) path.size();

     if (len < 2) return lastpath;

     auto itr = path.begin();
     auto itrnext = ++path.begin();
     int inc = 0;
     while (inc < len - 1) {
         std::vector<stts::vector2<int>> points = interpolate(itr->x, itr->y, itrnext->x, itrnext->y);
         int size = (int) points.size();
         for ( int i = 0; i < size - 1; ++i ) {
             lastpath.push_back(points[i]);
         }

         ++itr;
         ++itrnext;
         ++inc;
     }

     lastpath.push_back(*itr);

     return lastpath;
 }

 std::vector<stts::vector2<int>> pathfinder::interpolate(int x0, int y0, int x1, int y1) {
     std::vector<stts::vector2<int>> lines;

     int dx = abs(x1 - x0);
     int dy = abs(y1 - y0);

     int sx = (x0 < x1) ? 1 : -1;
     int sy = (y0 < y1) ? 1 : -1;

     int err = dx - dy;
     int e2 = 0;

     stts::vector2<int> point;

     while (true) {
         point.x = x0;
         point.y = y0;
         lines.push_back(point);

         if ((x0 == x1) && (y0 == y1)) break;

         e2 = 2 * err;

         if ( e2 > -dy ) {
             err -= dy;
             x0 += sx;
         }

         if ( e2 < dx ) {
             err += dx;
             y0 += sy;
         }
     }

     return lines;
 }
