#include "logger_broadcast.hpp"

void l::logger_broadcast::let (std::string& verbal, streams stream, bool decorated) {
    std::string timed_verbal = "! " + abstract_logger::get_time_name(true) + ": " + verbal + "\n";
    timed_verbal.insert(timed_verbal.begin(), (char) stream);
    timed_verbal.insert(0, "[Global]: ");
    //transmitter::transmit_all(trans_verbal); FIXME
}
