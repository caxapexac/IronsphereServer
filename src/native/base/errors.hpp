#include <exception>
#include <string>

struct shared_pointer_exception : public std::exception
{
    std::string info;

    shared_pointer_exception(std::string msg) : info(msg)
    {
    }

    const char *what() const throw()
    {
        return ("[shared pointer exception] " + info).c_str();
    }
};