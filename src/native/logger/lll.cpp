#include "lll.hpp"
#include "../online/api.hpp"
#include "abstract_logger.hpp"
#include "logger_user.hpp"

l::lll::lll () {
    stream = message;
    logs = 7;
    alpha = std::ostringstream();
    to = false;
}

void l::lll::set_logger (abstract_logger* log, loggers type) {
    //unsigned int logger_num = log2(type); //FIXME что за жесть, нужно сделать без математики
    // Компилер node-gyp крашится тут
    //log_arr[logger_num] = log;
}

void l::lll::set_user_logger (logger_user* log) {
    usr = log;
}

bool l::lll::subduce () {
    bool in = logs % 2;
    logs >>= 1u;
    return in;
}

void l::lll::send (std::string& verbal) {
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


l::lll& l::lll::say (streams str, unsigned int logs) {
    lll& logger = online::api::get().get_logger(); //TODO: add object!
    logger.stream = str;
    logger.logs = logs;
    logger.to = false;
    return logger;
}

l::lll& l::lll::say_to (std::string& addressee, streams str) {
    //lll& logger = online::api::get().log; //TODO: add object!
    OBSOLETE lll& logger = *new lll();

    logger.usr->change_addressee(addressee);
    logger.stream = str;
    logger.to = true;
    return logger;
}

namespace l {
    l::lll &operator<<(l::lll &out, json &object) {
        //out.alpha << object.dump(2); FIXME
        return out;
    }

    l::lll &operator<<(l::lll &out, l::lll &(*f)(l::lll &)) {
        return f(out);
    }

    void operator<<(l::lll &out, void (*f)(l::lll &)) {
        f(out);
    }
}


l::lll& l::lll::over (lll& out) {
    std::string verbal = out.alpha.str();
    out.send(verbal);
    return out;
}

void l::lll::out (lll& out) {
    std::string timed_verbal = "! " + abstract_logger::get_time_name(true) + ": " + out.alpha.str();
    timed_verbal.insert(timed_verbal.begin(), (char)out.stream);
    out.send(timed_verbal);
}
