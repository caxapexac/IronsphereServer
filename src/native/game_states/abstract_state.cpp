#include "abstract_state.hpp"
#include "../lobby/game_session.hpp"

abstract_state::abstract_state (game_session& context) : session(context) { }

void abstract_state::deserialize (json& package) {
    if (package == "state_choose") session.transition_to(std::make_unique<state_choose>(session));
    else if (package == "state_play") session.transition_to(std::make_unique<state_play>(session));
    else if (package == "state_pause") session.transition_to(std::make_unique<state_pause>(session));
    else if (package == "state_finish") session.transition_to(std::make_unique<state_finish>(session));
}

