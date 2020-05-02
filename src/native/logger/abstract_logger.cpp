#include "abstract_logger.hpp"

std::string& abstract_logger::get_time_name (bool full) {
    time_t raw_time;
    struct tm* time_info;
    char buffer[80];

    time(&raw_time);
    time_info = localtime(&raw_time);

    const char* format;
    if (full) format = "%d-%m-%Y %H:%M:%S";
    else format = "%d-%m-%Y";

    strftime(buffer, sizeof(buffer), format, time_info);
    auto now = new std::string(buffer);
    return *now;
}
