#ifndef LOGIC_CHAT_MESSAGE_HPP
#define LOGIC_CHAT_MESSAGE_HPP


#include "../base/includes.hpp"

namespace stts {
    struct chat_message : public iserializable {
        int player_uid;
        std::string message;

        explicit chat_message (int nplayer_uid, const std::string& nmessage);
        explicit chat_message (json& package);
        chat_message (const chat_message& other);
        chat_message& operator= (const chat_message& other);
        void serialize (json& package) const final;
        void deserialize (json& package) final;
    };
}

#endif //LOGIC_CHAT_MESSAGE_HPP
