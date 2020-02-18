#ifndef LOGIC_LOGGER_HPP
#define LOGIC_LOGGER_HPP

#include <memory>
#include <iostream>
#include "../base/object.hpp"
#include "../base/interfaces.hpp"

enum log_flags
{
    O_Console = 1,
    O_File = 2,
    O_Clients = 4,
    O_Broadcast = 8,
    T_Plain = 16,
    T_Info = 32,
    T_Warning = 64,
    T_Error = 128,
    TODO = 256
};

inline log_flags operator|(log_flags a, log_flags b)
{
    return static_cast<log_flags>(static_cast<int>(a) | static_cast<int>(b));
}

// Singleton
// TODO Maybe remove singleton?
class logger
{
private:
    static std::shared_ptr<logger> instance_ptr;
    logger() {}

public:
    static std::shared_ptr<logger> get()
    {
        if (!instance_ptr)
            instance_ptr = std::make_shared<logger>();
        return instance_ptr;
    }
    logger(logger const &) = delete;
    void operator=(logger const &) = delete;

    template <class... Args>
    void log(log_flags flags, Args... args);

    void log(log_flags flags, iserializable& obj);
};

template <class... Args>
void logger::log(log_flags flags, Args... args)
{
    // TODO
    (std::cout << ... << args) << std::endl;
}

void logger::log(log_flags flags, iserializable& obj)
{
    // TODO
    std::cout << obj.serialize(serializers::serial_full)->dump(2);
}

#endif //LOGIC_LOGGER_HPP