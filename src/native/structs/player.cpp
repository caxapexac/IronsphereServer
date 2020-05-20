#include "player.hpp"
#include "../game/base_game.hpp"
#include "parameter_map.hpp"

stts::player::player (int nteam) : team(nteam) {
    parameters = parameter_map();
}

stts::player::player (const player& copy) {
    *this = copy;
}

stts::player& stts::player::operator= (const player& copy) {
    if (this != &copy) {
        team = copy.team;
        parameters = parameter_map();
    }
    return *this;
}

void stts::player::serialize (json& package) const {
    package["team"] = team;
    parameters.serialize(package["parameters"]);
}

void stts::player::deserialize (json& package) {
    team = package["team"].get<int>();
    parameters.deserialize(package["parameters"]);
}

