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

class log {
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
    explicit log();
    ~log() = default;

    void set_logger(logger* log, loggers type);
    void set_user_logger(user_logger* log);

    static log& say(streams str = message, unsigned int logs = 7);
    static log& say_to(std::string& addressee, streams str = message);

    template <typename T>
    friend log& operator<< (log &out, const T &value);
    friend log& operator<< (log &out, log& (*f) (log&));
    friend void operator<< (log &out, void (*f) (log&));
    //TODO: for iSerializable,  any object to say

    static log& over(log& out);
    static void out(log& out);
    //....
};



template<typename T>
log &operator<<(log &out, const T &value) {
    out.alpha << value;
    return out;
}


#endif //UNTITLED_LOG_HPP
