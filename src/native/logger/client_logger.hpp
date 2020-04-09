#ifndef UNTITLED_CLIENT_LOGGER_HPP
#define UNTITLED_CLIENT_LOGGER_HPP


#include "logger.hpp"
#include "../transmitter.hpp"

class client_logger : public logger {
public:
    void let(std::string& verbal, streams stream) override;
};

#endif //UNTITLED_CLIENT_LOGGER_HPP
