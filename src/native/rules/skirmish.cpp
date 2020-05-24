#include "skirmish.hpp"

const std::string& rules::skirmish::type () const {
    return j_skirmish::type;
}

bool rules::skirmish::is_finished (std::map<int, stts::player*> players, std::map<int, ent::unit*> units) const {
    std::set<int> alive;
    for (const auto& i : units) {
        alive.emplace(i.second->get_player_id());
    }
    return alive.size() > 1;
}

rules::skirmish::skirmish (json& package) {
    skirmish::deserialize(package);

}
