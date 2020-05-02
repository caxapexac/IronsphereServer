#include "player.hpp"
#include "../game/abstract_game.hpp"

player::player (int nteam) : team(nteam) {
    parameters = parameter_map();
}

player::player (const player& copy) {
    *this = copy;
}

player& player::operator= (const player& copy) {
    if (this != &copy) {
        team = copy.team;
        parameters = parameter_map();
    }
    return *this;
}

void player::serialize (json& package) const {
    package["team"] = team;
    parameters.serialize(package["parameters"]);
}

void player::deserialize (json& package) {
    team = package["team"].get<int>();
    parameters.deserialize(package["parameters"]);
}

