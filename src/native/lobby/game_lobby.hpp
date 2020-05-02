#ifndef LOGIC_GAME_LOBBY_HPP
#define LOGIC_GAME_LOBBY_HPP

#include "game_session.hpp"
#include "../utils/singleton.hpp"
#include "../base/constants.hpp"
#include "../base/interfaces.hpp"
#include "../logger/l.hpp"

/// TODO json structures of commands
/// Facade of the game
class game_lobby : public singleton<game_lobby> {
private:
    float delta_time;
    std::map<int, std::shared_ptr<game_session>> sessions;
    json chat_buffer; // TODO chat class
    json log_buffer; // TODO connect with logger TODO into chat

public:
    OBSOLETE l log;

    game_lobby () noexcept; //TODO make private (its singleton)

    /// One server frame
    /// \param output
    void update (json& output);

    /// Action from player
    /// \param input json scheme is signal_input
    /// \param output json scheme is signal_output
    void signal (json& input, json& output);

private:
    /// TODO
    /// Client menu get_info (players online, room list, etc)
    /// \param output
    void get_info (json& output);

    /// TODO
    /// Add message from user to the message buffer
    /// \param input
    /// \param output
    void write_chat (json& input, json& output);

    /// Create new session
    /// \param input
    /// \param output
    void create_session (json& input, json& output);

    /// Everything in the session (including join_or_create, quit, signals and setup)
    /// \param input
    /// \param output
    void signal_session (json& input, json& output);
};

#endif //LOGIC_GAME_LOBBY_HPP
