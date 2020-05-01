#ifndef LOGIC_LOGGER_SERVER_HPP
#define LOGIC_LOGGER_SERVER_HPP


#include "abstract_logger.hpp"
#include <iostream>

class logger_server : public abstract_logger {
public:
    void let(std::string& verbal, streams stream) override;
};

#endif //LOGIC_LOGGER_SERVER_HPP
