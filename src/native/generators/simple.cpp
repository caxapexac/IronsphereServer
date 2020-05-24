#include "simple.hpp"
#include "../game/realtime.hpp"

generators::simple::simple (int nseed, int nplayers_count, const stts::vector2<int>& ntilemap_scale) {
    seed = nseed;
    players_count = nplayers_count;
    tilemap_scale = ntilemap_scale;
}

generators::simple::simple (json& package) {
    simple::deserialize(package);
}

void generators::simple::serialize (json& package) const {
    abstract_generator::serialize(package);
    package[j_simple::seed] = seed;
    package[j_simple::players_count] = players_count;
    tilemap_scale.serialize(package[j_simple::tilemap_scale]);
}

void generators::simple::deserialize (json& package) {
    abstract_generator::deserialize(package);
    package[j_simple::seed] = seed;
    package[j_simple::players_count] = players_count;
    tilemap_scale.serialize(package[j_simple::tilemap_scale]);
}

const std::string& generators::simple::type () const {
    return j_simple::type;
}

std::unique_ptr<game::abstract_game> generators::simple::generate () {
    // TODO
    std::unique_ptr<game::abstract_game> game = std::make_unique<game::realtime>();
    // TODO
    return std::move(game);
}



