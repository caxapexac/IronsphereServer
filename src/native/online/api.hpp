#ifndef LOGIC_API_HPP
#define LOGIC_API_HPP

#include "session.hpp"
#include "../base/includes.hpp"
#include "../utils/singleton.hpp"
#include "../logger/lll.hpp"
#include "../structs/chat_message.hpp"

namespace online {
    namespace j_api { //
        const std::string delta_time = TOSTRING(delta_time); // : float
        const std::string chat_capacity = TOSTRING(chat_capacity); // : int
        const std::string chat_buffer_updates = TOSTRING(chat_buffer_updates); // : int (readonly)
    }

    /// Facade of the game
    class api : public utils::singleton<api> {
        friend class utils::singleton<api>;
    private:
        float delta_time;
        int chat_capacity;
        mutable int chat_buffer_updates;
        std::queue<stts::chat_message> chat_buffer;
        std::map<int, std::shared_ptr<session>> sessions;
        l::lll lllll;

        api();

    public:
        static l::lll& get_logger() {
            return get().lllll; // TODO into cpp declaration
        }

        /// One server frame
        void start (json& config);

        /// One server frame
        void update (json& output);

        /// Action from player
        void signal (json& input, json& output);

    private:
        /// Client menu get_info (players online, room list, etc)
        void server_info (json& output);

        /// Chat and log buffer
        void read_chat (json& output);

        /// Add message from user to the message buffer
        void write_chat (json& input, json& output);

        /// Create new session
        void create_session (json& input, json& output);

        /// Everything in the session (including join_or_create, quit, signals and setup)
        void signal_session (json& input, json& output);
    };
}

#endif //LOGIC_API_HPP
