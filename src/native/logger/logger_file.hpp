#ifndef LOGIC_LOGGER_FILE_HPP
#define LOGIC_LOGGER_FILE_HPP

#include "../base/includes.hpp"
#include "abstract_logger.hpp"

namespace l {
    class logger_file : public l::abstract_logger {
    private:
        static void write_to_file (std::string& filename, std::string& verbal);

    public:
        void let (std::string& verbal, streams stream) override;
    };
}

#endif //LOGIC_LOGGER_FILE_HPP
