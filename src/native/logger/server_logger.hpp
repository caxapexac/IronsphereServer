#ifndef UNTITLED_SERVER_LOGGER_HPP
#define UNTITLED_SERVER_LOGGER_HPP


#include "logger.hpp"
#include <iostream>

class server_logger : public logger {
public:
    void let(std::string& verbal, streams stream) override;
};

#endif //UNTITLED_SERVER_LOGGER_HPP
