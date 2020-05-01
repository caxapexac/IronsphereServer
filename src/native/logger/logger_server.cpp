#include <iostream>
#include "logger_server.hpp"

void logger_server::let(std::string &verbal, streams stream) {
    switch (stream) {
        case error:
            std::cout << "\\033[31m" << verbal << "\\033[m\"" << std::endl;
            break;
        case warning:
            std::cout << "\\033[33m" << verbal << "\\033[m\"" << std::endl;
            break;
        case debug:
            std::cout << "\\033[34m" << verbal << "\\033[m\"" << std::endl;
            break;
        case message:
            std::cout << "\\033[38m" << verbal << "\\033[m\"" << std::endl;
            break;
        case special:
            std::cout << "\\033[32m" << verbal << "\\033[m\"" << std::endl;
            break;
    }
}
