#ifndef LOGIC_TILEMAP_PROXY_HPP
#define LOGIC_TILEMAP_PROXY_HPP

#include "tilemap.hpp"

// TODO https://refactoring.guru/design-patterns/proxy/cpp/example
class tilemap_proxy : public itilemap {
private:
    std::shared_ptr<tilemap> subject;

public:
    explicit tilemap_proxy(tilemap ntilemap);

};

//tilemap_proxy::tilemap_proxy (tilemap ntilemap) : subject(ntilemap) {

}

#endif //LOGIC_TILEMAP_PROXY_HPP
