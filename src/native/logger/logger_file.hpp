#ifndef LOGIC_LOGGER_FILE_HPP
#define LOGIC_LOGGER_FILE_HPP

#include "../base/includes.hpp"
#include "abstract_logger.hpp"

class logger_file : public abstract_logger {
private:
    static void write_to_file (std::string& filename, std::string& verbal);

public:
    void let (std::string& verbal, streams stream) override;
};

#endif //LOGIC_LOGGER_FILE_HPP
