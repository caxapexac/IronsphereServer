#ifndef UNTITLED_LOGGER_HPP
#define UNTITLED_LOGGER_HPP


#include <string>
#include "streams.hpp"
#include <ctime>

class logger {
public:
    logger() = default;

    static std::string& get_time_name(bool full);
    virtual void let(std::string& verbal, streams stream) = 0;

protected:
    virtual ~logger() = default;
};


#endif //UNTITLED_LOGGER_HPP
