#ifndef LOGIC_ABSTRACT_LOGGER_HPP
#define LOGIC_ABSTRACT_LOGGER_HPP

#include "../base/includes.hpp"

class abstract_logger {
public:
    abstract_logger () = default;

    static std::string& get_time_name (bool full);
    virtual void let (std::string& verbal, streams stream) = 0;

protected:
    virtual ~abstract_logger () = default;
};


#endif //LOGIC_ABSTRACT_LOGGER_HPP
