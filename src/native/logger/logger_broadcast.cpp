#include "logger_broadcast.hpp"
#include "../online/api.hpp"



void l::logger_broadcast::let (std::string& verbal, streams stream, bool decorated) {
    char str = decorated ? (char) stream : (char) streams::message;
    online::api::get().broadcast_buffer.push(stts::chat_message(str, verbal));
}
