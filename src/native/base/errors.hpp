#ifndef LOGIC_ERRORS_HPP
#define LOGIC_ERRORS_HPP

#include <exception>
#include <string>

// TODO add more generic exceptions
// TODO make it more complex and useful
// L7
struct shared_pointer_exception : public std::exception {
    std::string info;

    explicit shared_pointer_exception (std::string& msg) : info(msg) {
    }

    const char* what () const noexcept override {
        return ("[shared pointer exception] " + info).c_str();
    }
};

struct serialization_exception : public std::exception {
    std::string info;

    explicit serialization_exception (std::string& msg) : info(msg) {
    }

    const char* what () const noexcept override {
        return ("[Serialization exception] " + info).c_str();
    }
};

struct todo_exception : public std::exception {
    std::string info;

    explicit todo_exception (std::string& msg) : info(msg) {
    }

    const char* what () const noexcept override {
        return ("[RELEASE THIS EXCEPTION] " + info).c_str();
    }
};

#endif //LOGIC_ERRORS_HPP