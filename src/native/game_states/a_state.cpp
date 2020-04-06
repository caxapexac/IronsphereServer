#include "a_state.hpp"
#include "../lobby/game_session.hpp"

a_state::a_state (game_session& context) : session(context) { }

void a_state::deserialize (json& package) {
    // TODO move to json_tools
    if (package == "state_choose") session.transition_to(std::make_unique<state_choose>(session));
    else if (package == "state_play") session.transition_to(std::make_unique<state_play>(session));
    else if (package == "state_pause") session.transition_to(std::make_unique<state_pause>(session));
    else if (package == "state_finish") session.transition_to(std::make_unique<state_finish>(session));
}

