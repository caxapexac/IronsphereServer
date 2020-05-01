#include "abstract_state.hpp"
#include "../lobby/game_session.hpp"

abstract_state::abstract_state (game_session& context) : session(context) { }

void abstract_state::deserialize (json& package) {
    // TODO throw or remove method
}

