#include "logger_user.hpp"
#include "../online/api.hpp"

#define SERVER_ID -1



void l::logger_user::let (std::string& verbal, streams stream, bool decorated) {
    std::stringstream ss;
    ss << (char) stream << "! " << verbal;
    std::string timed_verbal = decorated ? ss.str() : verbal;
    online::api::get().chat_buffer.push(stts::chat_message(int(SERVER_ID), timed_verbal));
    if (online::api::get().chat_buffer.size() > online::api::get().chat_capacity) online::api::get().chat_buffer.pop();
    online::api::get().chat_buffer_updates++;
}
