#ifndef LOGIC_API_HPP
#define LOGIC_API_HPP

#include "session.hpp"
#include "../base/includes.hpp"
#include "../utils/singleton.hpp"
#include "../logger/lll.hpp"
#include "../structs/chat_message.hpp"

namespace online {
    /// TODO json structures of commands
    /// Facade of the game
    class api : public utils::singleton<api> {
        friend class singleton;
    private:
        float delta_time;
        int chat_buffer_updates;
        std::queue<stts::chat_message> chat_buffer;
        std::map<int, std::shared_ptr<session>> sessions;
        l::lll lllll;

        api () noexcept;

    public:
        l::lll& get_logger() {
            return lllll;
        }

        /// One server frame
        /// \param output
        void update (json& output);

        /// Action from player
        /// \param input json scheme is signal_input
        /// \param output json scheme is signal_output
        void signal (json& input, json& output);

    private:
        /// Client menu get_info (players online, room list, etc)
        /// \param output
        void server_info (json& output);

        /// Chat and log buffer
        /// \param output
        void read_chat (json& output);

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
}

#endif //LOGIC_API_HPP
