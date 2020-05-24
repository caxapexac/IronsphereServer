#include "simple_realtime_skirmish.hpp"

generators::simple_realtime_skirmish::simple_realtime_skirmish (int nseed, int nplayers_count, const stts::vector2<int>& ntilemap_scale) {
    seed = nseed;
    players_count = nplayers_count;
    tilemap_scale = ntilemap_scale;
}

generators::simple_realtime_skirmish::simple_realtime_skirmish (json& package) {
    simple_realtime_skirmish::deserialize(package);
}

void generators::simple_realtime_skirmish::serialize (json& package) const {
    abstract_generator::serialize(package);
    package[j_simple::seed] = seed;
    package[j_simple::players_count] = players_count;
    tilemap_scale.serialize(package[j_simple::tilemap_scale]);
}

void generators::simple_realtime_skirmish::deserialize (json& package) {
    abstract_generator::deserialize(package);
    package[j_simple::seed] = seed;
    package[j_simple::players_count] = players_count;
    tilemap_scale.serialize(package[j_simple::tilemap_scale]);
}

const std::string& generators::simple_realtime_skirmish::type () const {
    return j_simple::type;
}

std::unique_ptr<game::abstract_game> generators::simple_realtime_skirmish::generate () {
    std::unique_ptr<game::abstract_game>();
}



