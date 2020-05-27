#ifndef LOGIC_LOGGER_USER_HPP
#define LOGIC_LOGGER_USER_HPP

#include "abstract_logger.hpp"
//#include "../transmitter.hpp"

namespace l {
    class logger_user : public l::abstract_logger {
    private:
        int addressee;

    public:
        void change_addressee (int newcomer);
        void let (std::string& verbal, streams stream) override;
    };
}

#endif //LOGIC_LOGGER_USER_HPP
