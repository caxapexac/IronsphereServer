#ifndef LOGIC_LOGGER_CLIENT_HPP
#define LOGIC_LOGGER_CLIENT_HPP

#include "abstract_logger.hpp"
//#include "../transmitter.hpp" FIXME

namespace l {
    class logger_client : public l::abstract_logger {
    public:
        void let (std::string& verbal, streams stream) override;
    };
}

#endif //LOGIC_LOGGER_CLIENT_HPP
