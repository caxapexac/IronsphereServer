#ifndef UNTITLED_FILE_LOGGER_HPP
#define UNTITLED_FILE_LOGGER_HPP


#include "logger.hpp"
#include <ctime>
#include <fstream>

class file_logger : public logger {
private:
    static void write_to_file(std::string& filename, std::string &verbal);

public:
    void let(std::string& verbal, streams stream) override;
};

#endif //UNTITLED_FILE_LOGGER_HPP
