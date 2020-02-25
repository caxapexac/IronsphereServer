#ifndef LOGIC_TILEMAP_PROXY_HPP
#define LOGIC_TILEMAP_PROXY_HPP

#include "tilemap.hpp"

// TODO https://refactoring.guru/design-patterns/proxy/cpp/example
class tilemap_proxy : public itilemap {
private:
    tilemap subject;

public:
    explicit tilemap_proxy(tilemap& ntilemap);

    bool move(unit_moving& mover);
};

tilemap_proxy::tilemap_proxy (tilemap& ntilemap) : subject(ntilemap) {}

bool tilemap_proxy::move(unit_moving &mover) {

}

#endif //LOGIC_TILEMAP_PROXY_HPP
