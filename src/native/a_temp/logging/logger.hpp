#ifndef LOGIC_LOGGER_HPP
#define LOGIC_LOGGER_HPP

#include <memory>
#include <iostream>
#include "../../base/interfaces.hpp"


// Singleton
// TODO Maybe decorator???
// TODO Maybe composite?
// TODO Maybe remove singleton?
// TODO Cuz of L4 change into proxy pattern (ilogger + concrete loggers)
// TODO Change output format using agapter
// TODO logger for statistics (for end game screen stats)
class abstract_logger {
private:
    static std::shared_ptr<abstract_logger> instance_ptr;

    abstract_logger () = default;

public:
    abstract_logger (abstract_logger const&) = delete;
    void operator= (abstract_logger const&) = delete;

    static abstract_logger& get () {
        if (!instance_ptr)
            instance_ptr = std::shared_ptr<abstract_logger>(new abstract_logger());
        return *instance_ptr;
    }

    enum log_flags { //TODO remove
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

    friend inline abstract_logger::log_flags operator| (abstract_logger::log_flags a, abstract_logger::log_flags b) {
        return static_cast<abstract_logger::log_flags>(static_cast<unsigned>(a) | static_cast<unsigned>(b));
    }

     //template<class... Args> void log (log_flags flags, Args... args);
    // void log (log_flags flags, iserializable& obj);
};

std::shared_ptr<abstract_logger> abstract_logger::instance_ptr = nullptr;

// template<class... Args> void abstract_logger::log (log_flags flags, Args... args) {
//     // TODO
//     (std::cout << ... << args) << std::endl;
// }
//
// void abstract_logger::log (log_flags flags, iserializable& obj) {
//     // TODO
//     std::cout << obj.serialize(serializers::serial_save)->dump(2) << std::endl;
// }

#endif //LOGIC_LOGGER_HPP