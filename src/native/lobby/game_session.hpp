#ifndef LOGIC_GAME_SESSION_HPP
#define LOGIC_GAME_SESSION_HPP

#include "../base/interfaces.hpp"
#include "../structs/game_storage.hpp"
#include "../game_states/abstract_state.hpp"
#include "../game_states/state_choose.hpp"
#include "../game_states/state_play.hpp"
#include "../game_states/state_pause.hpp"
#include "../game_states/state_finish.hpp"
#include "../game_strategies/abstract_strategy.hpp"

class game_session : public iserializable {
    friend class tester;
    friend class abstract_state;
    friend class state_choose;
    friend class state_play;
    friend class state_pause;
    friend class state_finish;

private:
    N_S std::vector<int> players_id; // For security
    std::unique_ptr<abstract_state> state; // Game state
    std::unique_ptr<abstract_strategy> strategy; // Game rules
    std::unique_ptr<game_storage> storage;

public:
    game_session ();

    /// Checks if there is no players in session
    bool is_empty ();

    /// The most important part of the session
    /// \return current session state to interact with
    abstract_state& get_state ();

    /// \param player_id
    /// \return index of specified player. Returns -1 if not found
    int get_player_index (int player_id);

    /// Save/update/get info from the game
    /// \param package
    /// \param type
    void serialize (json& package, serializers type) const override;

    /// Load the game
    /// \param package
    void deserialize (json& package) override;

private:
    /// Changes state
    /// \param state is new state
    void transition_to (std::unique_ptr<abstract_state> nstate);
};

#endif //LOGIC_GAME_SESSION_HPP
