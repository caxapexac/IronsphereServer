#ifndef LOGIC_LOGGER_SERVER_HPP
#define LOGIC_LOGGER_SERVER_HPP

#include "../base/includes.hpp"
#include "abstract_logger.hpp"

namespace l {
    class logger_server : public l::abstract_logger {
    public:
        void let(std::string& verbal, streams stream, bool decorated) override;
    };
}

#endif //LOGIC_LOGGER_SERVER_HPP
