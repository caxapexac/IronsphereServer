#ifndef LOGIC_LOGGER_HPP
#define LOGIC_LOGGER_HPP

class logger;

#include <memory>
#include <iostream>
#include "../base/interfaces.hpp"


// Singleton
// TODO Maybe remove singleton?
// TODO Cuz of L4 change into proxy pattern (ilogger + concrete loggers)
// TODO Change output format using agapter
class logger {
private:
    static std::shared_ptr<logger> instance_ptr;

    logger () = default;

public:
    logger (logger const&) = delete;
    void operator= (logger const&) = delete;

    static logger& get () {
        if (!instance_ptr)
            instance_ptr = std::shared_ptr<logger>(new logger());
        return *instance_ptr;
    }

    enum log_flags {
        O_Cons = 1,
        O_File = 2,
        O_Users = 4,
        O_Broad = 8,
        T_Plain = 16,
        T_Info = 32,
        T_Warn = 64,
        T_Error = 128,
        TODO = 256
    };

    friend inline logger::log_flags operator| (logger::log_flags a, logger::log_flags b) {
        return static_cast<logger::log_flags>(static_cast<unsigned>(a) | static_cast<unsigned>(b));
    }

    template<class... Args> void log (log_flags flags, Args... args);
    void log (log_flags flags, iserializable& obj);
};

std::shared_ptr<logger> logger::instance_ptr = nullptr;

template<class... Args> void logger::log (log_flags flags, Args... args) {
    // TODO
    (std::cout << ... << args) << std::endl;
}

void logger::log (log_flags flags, iserializable& obj) {
    // TODO
    std::cout << obj.serialize(serializers::serial_full)->dump(2) << std::endl;
}

#endif //LOGIC_LOGGER_HPP