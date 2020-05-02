#include "logger_user.hpp"

void logger_user::let (std::string& verbal, streams stream) {
    verbal.insert(0, "[Server]: ");
    //transmitter::transmit(addressee, verbal);
}

void logger_user::change_addressee (std::string& newcomer) {
    addressee = newcomer;
}
