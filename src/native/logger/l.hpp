#ifndef UNTITLED_LOG_HPP
#define UNTITLED_LOG_HPP


#include <vector>
#include <sstream>

#include "logger.hpp"
#include "loggers.hpp"
#include "streams.hpp"

#include "server_logger.hpp"
#include "client_logger.hpp"
#include "user_logger.hpp"
#include "file_logger.hpp"

#include "../utils/json_tools.hpp"
#include "../lobby/game_lobby.hpp"

class l {
private:
    bool subduce();
    void send(std::string& verbal);

    streams stream;
    unsigned int logs;
    std::ostringstream alpha;
    bool to;

    logger* log_arr [3];
    user_logger* usr;

public:
    explicit l();
    ~l() = default;

    void set_logger(logger* log, loggers type);
    void set_user_logger(user_logger* log);

    static l& say(streams str = message, unsigned int logs = 7);
    static l& say_to(std::string& addressee, streams str = message);

    template <typename T>
    friend l& operator<< (l &out, const T &value);
    friend l& operator<< (l &out, json& object);
    friend l& operator<< (l &out, l& (*f) (l&));
    friend void operator<< (l &out, void (*f) (l&));
    //TODO: for iSerializable,  any object to say

    static l& over(l& out);
    static void out(l& out);
    //....
};



template<typename T>
l &operator<<(l & out, const T &value) {
    out.alpha << value;
    return out;
}


#endif //UNTITLED_LOG_HPP
