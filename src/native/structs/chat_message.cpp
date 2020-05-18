#include "chat_message.hpp"


chat_message::chat_message (int nuid, const std::string& nmessage) {
    uid = nuid;
    message = nmessage;
}

chat_message::chat_message (json& package) {
    deserialize(package);
}

chat_message::chat_message (const chat_message& other) : uid(other.uid), message(other.message) { }

chat_message& chat_message::operator= (const chat_message& other) {
    if (this != &other) {
        uid = other.uid;
        message = other.message;
    }
    return *this;
}

void chat_message::serialize (json& package) const {
    package["uid"] = uid;
    package["message"] = message;
}

void chat_message::deserialize (json& package) {
    uid = package["uid"].get<int>();
    message = package["message"].get<std::string>();
}
