#ifndef LOGIC_LOGGER_USER_HPP
#define LOGIC_LOGGER_USER_HPP


#include "abstract_logger.hpp"
//#include "../transmitter.hpp"

class logger_user : public abstract_logger {
private:
    std::string addressee;

public:
    void change_addressee(std::string& newcomer);
    void let(std::string& verbal, streams stream) override;
};

#endif //LOGIC_LOGGER_USER_HPP
