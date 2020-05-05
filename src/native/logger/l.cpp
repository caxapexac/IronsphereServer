#include "l.hpp"
#include "../lobby/game_lobby.hpp"

l::l () {
    stream = message;
    logs = 7;
    alpha = std::ostringstream();
    to = false;
}

void l::set_logger (abstract_logger* log, loggers type) {
    //unsigned int logger_num = log2(type); //FIXME что за жесть, нужно сделать без математики
    // Компилер node-gyp крашится тут
    //log_arr[logger_num] = log;
}

void l::set_user_logger (logger_user* log) {
    usr = log;
}

bool l::subduce () {
    bool in = logs % 2;
    logs >>= 1u;
    return in;
}

void l::send (std::string& verbal) {
    unsigned int old_logs = logs;
    if (to) {
        log_arr[3]->let(verbal, stream);
    }
    else {
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


l& l::say (streams str, unsigned int logs) {
    l& logger = game_lobby::get().log; //TODO: add object!
    logger.stream = str;
    logger.logs = logs;
    logger.to = false;
    return logger;
}

l& l::say_to (std::string& addressee, streams str) {
    l& logger = game_lobby::get().log; //TODO: add object!
    logger.usr->change_addressee(addressee);
    logger.stream = str;
    logger.to = true;
    return logger;
}


l& operator<< (l& out, l& (* f) (l&)) {
    return f(out);
}

void operator<< (l& out, void (* f) (l&)) {
    f(out);
}

l& operator<< (l& out, json& object) {
    out.alpha << object.dump(2);
    return out;
}

l& l::over (l& out) {
    std::string verbal = out.alpha.str();
    out.send(verbal);
    return out;
}

void l::out (l& out) {
    std::string timed_verbal = "! " + abstract_logger::get_time_name(true) + ": " + out.alpha.str();
    timed_verbal.insert(timed_verbal.begin(), (char)out.stream);
    out.send(timed_verbal);
}
