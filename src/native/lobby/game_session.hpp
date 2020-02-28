#ifndef LOGIC_GAME_SESSION_HPP
#define LOGIC_GAME_SESSION_HPP

#include "../base/interfaces.hpp"
#include "../a_temp/strategies/abstract_strategy.hpp"
#include "../game_states/abstract_state.hpp"

class game_session : iiserializable {
private:
    std::vector<int> players_id; // For security
    std::shared_ptr<abstract_state> state; // Game state
    std::unique_ptr<abstract_strategy> strategy; // Game rules
    std::unique_ptr<tilemap> map; // Field
    std::unique_ptr<std::vector<player>> Players; //TODO player 0 holds neutral objects

    friend class state_choose;
    friend class state_play;
    friend class state_pause;
    friend class state_finish;

public:
    game_session ();

    /// Checks if there is no players in session
    bool is_empty ();

    /// Generic info about session
    /// \param output
    void get_info (json& output);

    ///
    /// \return current session state to interact with
    std::shared_ptr<abstract_state> get_state ();

    /// Adds player to the session
    /// \param input
    /// \param output
    void add_player (json& input, json& output);

    /// One session frame
    /// \param output
    void update (json& output);

    /// Input from the player
    /// \param input
    /// \param output
    void signal (json& input, json& output);

    /// Removes player from the session if exist
    /// \param input
    /// \param output
    void remove_player (json& input, json& output);

private:
    /// \param player_id
    /// \return index of specified player. Returns -1 if not found
    int get_player_index (int player_id);

    /// Signal setup
    /// \param input
    /// \param output
    void setup_game (json& input, json& output);
};

game_session::game_session () {
    //state = std::make_unique<state_choose>(this);
    players_id = std::vector<int>();
    game = nullptr;
}

bool game_session::is_empty () {
    return players_id.empty();
}

void game_session::get_info (json& output) {
    if (game != nullptr) {
        game->serialize(output["game"], serial_info);
    }
    output["players_id"] = players_id;
}

std::shared_ptr<abstract_state> game_session::get_state () {
    return state;
}


void game_session::add_player (json& input, json& output) {
    int index = get_player_index(input.get<int>());
    if (index == -1) {
        players_id.push_back(input);
        output = {{"success", "Player was added into the room"}};
    }
    else {
        output = {{"error", "Player is already in the room"}};
        return;
    }
}

void game_session::update (json& output) {
    if (game != nullptr) {
        game->update(output);
    }
}

void game_session::signal (json& input, json& output) {
    if (input["signal"] == nullptr || input["sender"] == nullptr) {
        output = {{"error", "Input isn't correct"}};
        return;
    }

    int player_index = get_player_index(input["sender"]); // TODO admin permissions
    if (player_index == -1) {
        output = {{"error", "Player isn't in session"}};
        return;
    }

    if (input["signal"] == "setup") {
        setup_game(input, output);
        if (game != nullptr && (game->get_state() == g_play || game->get_state() == g_pause)) {

        }
        else {
            output = {{"error", "Session was already started"}};
        }
    }
    else if (input["signal"] == "start") {
        if (state == g_choosing || state == g_finished) {
            state = g_choosing;
        }
        else {
            output = {{"error", "Session was already started"}};
        }
    }
    else if (input["signal"] == "pause") {
        if (state == g_choosing || state == g_finished) {
            state = g_choosing;
        }
        else {
            output = {{"error", "Session was already started"}};
        }
    }
    else if (input["signal"] == "stop") {
        if (state == g_choosing || state == g_finished) {
            state = g_choosing;
        }
        else {
            output = {{"error", "Session was already started"}};
        }
    }
    else if (input["signal"] == "input") {

    }
    else {
        output = {{"error", "Command isn't correct"}};
    }
}

void game_session::remove_player (json& input, json& output) {
    int index = get_player_index(input.get<int>());
    if (index == -1) {
        output = {{"error", "Player is not in this room"}};
    }
    else {
        players_id.erase(players_id.begin() + index);
        output = {{"success", "Player was removed from the room"}};
    }

}

int game_session::get_player_index (int player_id) {
    for (int i = 0; i < players_id.size(); ++i) {
        if (players_id[i] == player_id) return i;
    }
    return -1;
}

void game_session::setup_game (json& input, json& output) {

}



#endif //LOGIC_GAME_SESSION_HPP
