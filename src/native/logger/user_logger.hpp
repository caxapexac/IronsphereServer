#ifndef UNTITLED_USER_LOGGER_HPP
#define UNTITLED_USER_LOGGER_HPP


#include "logger.hpp"
#include "../transmitter.hpp"

class user_logger : public logger {
private:
    std::string addressee;

public:
    void change_addressee(std::string& newcomer);
    void let(std::string& verbal, streams stream) override;
};

#endif //UNTITLED_USER_LOGGER_HPP
