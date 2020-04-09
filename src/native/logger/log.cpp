#include "log.hpp"

log::log() {
    stream = message;
    logs = 7;
    alpha = std::ostringstream();
    to = false;
}



void log::set_logger(logger* log, loggers type) {
    unsigned int logger_num = log2(type);
    log_arr[logger_num] = log;
}

void log::set_user_logger(user_logger* log) {
    usr = log;
}



bool log::subduce() {
    bool in = logs % 2;
    logs >>= 1u;
    return in;
}

void log::send(std::string& verbal) {
    unsigned int old_logs = logs;
    if (to) {
        log_arr[3]->let(verbal, stream);
    } else {
        if (subduce())
            log_arr[0]->let(verbal, stream);
        if (subduce())
            log_arr[1]->let(verbal, stream);
        if (subduce())
            log_arr[2]->let(verbal, stream);
    }
    logs = old_logs;
    alpha = std::ostringstream();
}



log& log::say(streams str, unsigned int logs) {
    log logger = game_lobby::get().log; //TODO: add!
    logger.stream = str;
    logger.logs = logs;
    logger.to = false;
    return logger;
}

log& log::say_to(std::string &addressee, streams str) {
    log logger = game_lobby::get().log; //TODO: add!
    logger.usr->change_addressee(addressee);
    logger.stream = str;
    logger.to = true;
    return logger;
}



log &operator<<(log &out, log &(*f) (log&)) {
    return f(out);
}

void operator<<(log &out, void (*f)(log&)) {
    f(out);
}



log &log::over(log &out) {
    std::string verbal = out.alpha.str();
    out.send(verbal);
    return out;
}

void log::out(log &out) {
    std::string timed_verbal = "! " + logger::get_time_name(true) + ": " + out.alpha.str();
    timed_verbal.insert(timed_verbal.begin(), (char) out.stream);
    out.send(timed_verbal);
}
