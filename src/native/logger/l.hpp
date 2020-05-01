#ifndef LOGIC_LOG_HPP
#define LOGIC_LOG_HPP


#include <vector>
#include <sstream>

#include "abstract_logger.hpp"
#include "loggers.hpp"
#include "streams.hpp"

#include "logger_server.hpp"
#include "logger_client.hpp"
#include "logger_user.hpp"
#include "logger_file.hpp"

#include "../utils/json_tools.hpp"
#include "../lobby/game_lobby.hpp"

// TODO rename please) maybe out
class l {
private:
    bool subduce();
    void send(std::string& verbal);

    streams stream;
    unsigned int logs;
    std::ostringstream alpha;
    bool to;

    abstract_logger* log_arr [3];
    logger_user* usr;

public:
    explicit l();
    ~l() = default;

    void set_logger(abstract_logger* log, loggers type);
    void set_user_logger(logger_user* log);

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


#endif //LOGIC_LOG_HPP
