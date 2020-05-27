#include "on.hpp"
#include "../online/api.hpp"
#include "abstract_logger.hpp"
#include "logger_user.hpp"

l::on::on () : utils::singleton<on>() {
    stream = message;
    serverL = false;
    clientL = false;
    fileL = false;
    SL = nullptr;
    CL = nullptr;
    FL = nullptr;
    UL = nullptr;
    alpha = std::ostringstream();
}



void l::on::set_server_logger (logger_server* log) {
    on& fin = utils::singleton<on>::get();
    fin.SL = log;
}

void l::on::set_client_logger (logger_client* log) {
    on& fin = utils::singleton<on>::get();
    fin.CL = log;
}

void l::on::set_file_logger (logger_file* log) {
    on& fin = utils::singleton<on>::get();
    fin.FL = log;
}

void l::on::set_user_logger (logger_user* log) {
    on& fin = utils::singleton<on>::get();
    fin.UL = log;
}

void l::on::toggle_loggers(bool server, bool client, bool file) {
    on& fin = utils::singleton<on>::get();
    fin.serverL = server;
    fin.clientL = client;
    fin.fileL = file;
}



void l::on::send (std::string& verbal) {
    if (serverL)
        if (SL) SL->let(verbal, stream);
        //else raise Exception;
    if (clientL)
        if (CL) CL->let(verbal, stream);
        //else raise Exception;
    if (fileL)
        if (FL) FL->let(verbal, stream);
        //else raise Exception;
    alpha = std::ostringstream();
}


l::on& l::on::say (streams str) {
    on& fin = utils::singleton<on>::get();
    fin.stream = str;
    return fin;
}

void l::on::say_to (int addressee, std::string& msg, streams str) {
    on& fin = utils::singleton<on>::get();
    //if (!UL) raise Exception;
    fin.UL->change_addressee(addressee);
    fin.UL->let(msg, str);
}

namespace l {
    l::on &operator<<(l::on &out, json &object) {
        out.alpha << object.dump(2);
        return out;
    }

    l::on &operator<<(l::on &out, l::on &(*f)(l::on &)) {
        return f(out);
    }

    void operator<<(l::on &out, void (*f)(l::on &)) {
        f(out);
    }
}


l::on& l::on::over (on& out) {
    std::string verbal = out.alpha.str();
    out.send(verbal);
    return out;
}

void l::on::out (on& out) {
    std::string timed_verbal = "! " + abstract_logger::get_time_name(true) + ": " + out.alpha.str();
    timed_verbal.insert(timed_verbal.begin(), (char)out.stream);
    out.send(timed_verbal);
}
