#include "chat_message.hpp"


stts::chat_message::chat_message (int nplayer_uid, const std::string& nmessage) {
    player_uid = nplayer_uid;
    message = nmessage;
}

stts::chat_message::chat_message (json& package) {
    deserialize(package);
}

stts::chat_message::chat_message (const chat_message& other) : uid(other.uid), message(other.message) { }

stts::chat_message& stts::chat_message::operator= (const chat_message& other) {
    if (this != &other) {
        uid = other.uid;
        message = other.message;
    }
    return *this;
}

void stts::chat_message::serialize (json& package) const {
    package["uid"] = uid;
    package["message"] = message;
}

void stts::chat_message::deserialize (json& package) {
    uid = package["uid"].get<int>();
    message = package["message"].get<std::string>();
}
