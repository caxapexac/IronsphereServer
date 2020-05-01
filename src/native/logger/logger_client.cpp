#include "logger_client.hpp"

void logger_client::let(std::string &verbal, streams stream) {
    std::string trans_verbal = verbal + "\n";
    trans_verbal.insert(0, "[Global]: ");
    //transmitter::transmit_all(trans_verbal); FIXME
}
