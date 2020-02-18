#ifndef LOGIC_ERRORS_HPP
#define LOGIC_ERRORS_HPP

#include <exception>
#include <string>

// TODO add more generic exceptions
// L7
struct shared_pointer_exception : public std::exception {
    std::string info;

    explicit shared_pointer_exception (std::string& msg) : info(msg) {
    }

    const char* what () const noexcept override {
        return ("[shared pointer exception] " + info).c_str();
    }
};

#endif //LOGIC_ERRORS_HPP