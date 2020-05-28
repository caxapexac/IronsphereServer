#include "logger_user.hpp"

void l::logger_user::let (std::string& verbal, streams stream, bool decorated) {
    std::string timed_verbal = "! " + abstract_logger::get_time_name(true) + ": " + verbal + "\n";
    timed_verbal.insert(0, "[Server]: ");
    timed_verbal.insert(timed_verbal.begin(), (char) stream);
    //transmitter::transmit(addressee, verbal);
}
