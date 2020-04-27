#include "pathfinder.hpp"

// TODO: (probably) clear this when WE will be done.

pathfinder::pathfinder(tilemap_square &map) : map(map) {
    grid = new tile_plus[map.size()];

    for (int i = 0; i < map.get_scale().x; ++i) {
        for (int j = 0; j < map.get_scale().y; ++j) {
            grid[i].content = &(map[vector2<int>(i, j)]);
            grid[i].position = vector2<int>(i, j);
        }
    }
}

std::list<vector2<int>> pathfinder::find_path(vector2<int>& from, vector2<int>& to) {
    for (int i = 0; i < map.size(); ++i) {
        grid[i].clear();
    }
    path.clear();

    begin_node = get_plus(from.x, from.y);
    end_node = get_plus(to.x, to.y);

    // set the `g` and `f` value of the start node to be zero
    begin_node->g = 0;
    begin_node->f = 0;

    // push the begin node into the open list
    open_list.push_back(begin_node);
    begin_node->opened = true;

    tile_plus* node = nullptr;

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



bool pathfinder::can_walk(int x, int y) {
    if (((x < 0) || (x >= map.get_scale().x)) || ((y < 0) || (y >= map.get_scale().y))) return false;
    tile_plus* node = get_plus(x, y);
    return node && node->content->is_empty();
}

tile_plus* pathfinder::get_plus(int x, int y) {
    return &(grid[y * map.get_scale().y + x]);
}

void pathfinder::identify_successors(tile_plus* node) {
    tile_plus* jumpnode = nullptr;
    int d = 0;
    int g = 0;

    std::vector<tile_plus*> cells = find_neighbors(node);
    for (auto itr = cells.begin(); itr != cells.end(); ++itr) {
        auto result = jump((*itr)->position.x, (*itr)->position.y, node->position.x, node->position.y);

        int jx = std::get<0>(result);
        int jy = std::get<1>(result);
        if (jx < 0) // NEEDED????
            continue;

        jumpnode = get_plus(jx, jy);
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
                open_list.sort([] (const tile_plus* a, const tile_plus* b)->bool // TODO: replace with in-place search.
                                {
                                    return a->f < b->f;
                                });

                jumpnode->opened = true;
            }
        }
    }
}

std::tuple<int, int> pathfinder::jump(int x, int y, int px, int py) {
    int dx = x - px;
    int dy = y - py;

    if (!can_walk(x, y))
        return std::make_tuple(-1, -1);

    if (get_plus(x, y) == end_node)
        return std::make_tuple(x, y);

    // check for forced neighbors
    // along the diagonal
    if ( dx != 0 && dy != 0 ) {
        if ( (can_walk(x - dx, y + dy) && !can_walk(x - dx, y)) || (can_walk(x + dx, y - dy) && !can_walk(x, y - dy)) )
            return std::make_tuple(x, y);

        if ((std::get<0>(jump(x + dx, y, x, y)) != -1) || (std::get<0>(jump(x, y + dy, x, y)) != -1))
            return std::make_tuple(x, y);

    } else { // horizontally/vertically
        if (dx != 0) {
            if ((can_walk(x + dx, y + 1) && !can_walk(x, y + 1)) || (can_walk(x + dx, y - 1) && !can_walk(x, y - 1)) )
                return std::make_tuple(x, y);

        } else {
            if ((can_walk(x + 1, y + dy) && !can_walk(x + 1, y)) || (can_walk(x - 1, y + dy) && !can_walk(x - 1, y)))
                return std::make_tuple(x, y);
        }
    }

    return jump(x + dx, y + dy, x, y);
}

std::vector<tile_plus*> pathfinder::find_neighbors(tile_plus* cellNode) {
    std::vector<tile_plus*> neighbours;

    int x = cellNode->position.x;
    int y = cellNode->position.y;

    // directed pruning: can ignore most neighbors, unless forced.
    if ( cellNode->parent ) {
        // get the normalized direction of travel
        int dx = (x - cellNode->parent->position.x) / m_max(abs(x - cellNode->parent->position.x), 1);
        int dy = (y - cellNode->parent->position.y) / m_max(abs(y - cellNode->parent->position.y), 1);

        // search diagonally
        if ( dx != 0 && dy != 0 ) {
            if (can_walk(x, y + dy)) // down
                neighbours.push_back(get_plus(x, y + dy));

            if (can_walk(x + dx, y)) // right
                neighbours.push_back(get_plus(x + dx, y));

            if (can_walk(x + dx, y + dy)) // right down
                neighbours.push_back(get_plus(x + dx, y + dy));

            if (!can_walk(x - dx, y)) // 0 1
                neighbours.push_back(get_plus(x - dx, y + dy));

            if (!can_walk(x, y - dy)) // 1 0
                neighbours.push_back(get_plus(x + dx, y - dy));
        } else { // search horizontally/vertically
            if ( dx == 0 ) {
                if (can_walk(x, y + dy))
                    neighbours.push_back(get_plus(x, y + dy));

                if (!can_walk(x + 1, y))
                    neighbours.push_back(get_plus(x + 1, y + dy));

                if (!can_walk(x - 1, y))
                    neighbours.push_back(get_plus(x - 1, y + dy));
            } else {
                if (can_walk(x + dx, y))
                    neighbours.push_back(get_plus(x + dx, y));

                if (!can_walk(x, y + 1))
                    neighbours.push_back(get_plus(x + dx, y + 1));

                if (!can_walk(x, y - 1))
                    neighbours.push_back(get_plus(x + dx, y - 1));
            }
        }
    } else {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if ((i == 0) && (j == 0)) continue;
                if (can_walk(x + i, y + j)) neighbours.push_back(get_plus(x + i, y + j));
            }
        }
    }

    return neighbours;
}

void pathfinder::backtrace(tile_plus* node) {
    vector2<int> point;

    do {
        point.x = node->position.x;
        point.y = node->position.y;
        path.push_back(point);

        node = node->parent;
    } while (node->parent);

    path.reverse();
}

std::list<vector2<int>> pathfinder::expand_path() {
    std::list<vector2<int>> lastpath;

    int len = (int) path.size();

    if (len < 2) return lastpath;

    auto itr = path.begin();
    auto itrnext = ++path.begin();
    int inc = 0;
    while (inc < len - 1) {
        std::vector<vector2<int>> points = interpolate(itr->x, itr->y, itrnext->x, itrnext->y);
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

std::vector<vector2<int>> pathfinder::interpolate(int x0, int y0, int x1, int y1) {
    std::vector<vector2<int>> lines;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;
    int e2 = 0;

    vector2<int> point;

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
