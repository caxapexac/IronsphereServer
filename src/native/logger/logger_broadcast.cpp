#include "logger_broadcast.hpp"
#include "../online/api.hpp"



void l::logger_broadcast::let (std::string& verbal, streams stream, bool decorated) {
    char str = decorated ? (char) stream : (char) streams::message; //FIXME: c++ stupidity: streams::ord(stream)
    stts::chat_message msg(str, verbal);
    online::api::get().to_broadcast(msg);
}
