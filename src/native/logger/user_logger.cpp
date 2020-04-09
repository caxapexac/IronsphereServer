#include "user_logger.hpp"

void user_logger::let(std::string &verbal, streams stream) {
    verbal.insert(0, "[Server]: ");
    transmitter::transmit(addressee, verbal);
}

void user_logger::change_addressee(std::string &newcomer) {
    addressee = newcomer;
}
