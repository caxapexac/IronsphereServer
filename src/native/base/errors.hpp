#ifndef LOGIC_ERRORS_HPP
#define LOGIC_ERRORS_HPP

#include "third_party_includes.hpp"

// TODO add more generic exceptions
// TODO make it more complex and useful
// TODO iserializable constructor exception
// TODO tryso
struct shared_pointer_exception : public std::exception {
    mutable std::string info;

    explicit shared_pointer_exception (const std::string& msg) : info(msg) { }

    const char* what () const noexcept override {
        return info.insert(0, "[Shared pointer exception] ").c_str();
    }
};

struct serialization_exception : public std::exception {
    mutable std::string info;

    explicit serialization_exception (const std::string& msg) : info(msg) { }

    const char* what () const noexcept override {
        return info.insert(0, "[Serialization exception] ").c_str();
    }
};

struct todo_exception : public std::exception {
    std::string info;

    explicit todo_exception (const std::string& msg) : info(msg) { }

    const char* what () const noexcept override {
        std::cout << info;
        return "help";
        //return ("[RELEASE THIS EXCEPTION] " + ).c_str(); FIXME
    }
};

#endif //LOGIC_ERRORS_HPP