#include "logger_server.hpp"

void l::logger_server::let(std::string &verbal, streams stream, bool decorated) {
    std::string timed_verbal = "! " + abstract_logger::get_time_name(true) + ": " + verbal;
    timed_verbal.insert(timed_verbal.begin(), (char) stream);
    switch (stream) {
        case error:
            std::cout << "\\033[31m" << timed_verbal << "\\033[m\"" << std::endl;
            break;
        case warning:
            std::cout << "\\033[33m" << timed_verbal << "\\033[m\"" << std::endl;
            break;
        case debug:
            std::cout << "\\033[34m" << timed_verbal << "\\033[m\"" << std::endl;
            break;
        case message:
            std::cout << "\\033[38m" << timed_verbal << "\\033[m\"" << std::endl;
            break;
        case special:
            std::cout << "\\033[32m" << timed_verbal << "\\033[m\"" << std::endl;
            break;
    }
}
