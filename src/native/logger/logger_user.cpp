#include "logger_user.hpp"

void l::logger_user::let (std::string& verbal, streams stream) {
    verbal.insert(0, "[Server]: ");
    //transmitter::transmit(addressee, verbal);
}

void l::logger_user::change_addressee (int newcomer) {
    addressee = newcomer;
}
