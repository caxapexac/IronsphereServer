#include "errors.hpp"
#include "includes.hpp"

const char *basic_exception::what() const noexcept {
    return info.c_str();
}

basic_exception::basic_exception(const std::string &msg) {
    this->info = "[General exception] " + msg;
    logger::say(info, l::error, true);
}



shared_pointer_exception::shared_pointer_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Shared pointer exception] " + msg;
    logger::say(info, l::error, true);
}

serialization_exception::serialization_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Serialization exception] " + msg;
    logger::say(info, l::error, true);
}

deserialization_exception::deserialization_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Deserialization exception] " + msg;
    logger::say(info, l::error, true);
}

unimplemented_exception::unimplemented_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Unimplemented exception] " + msg;
    logger::say(info, l::error, true);
}

recursion_exception::recursion_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Recursion exception] " + msg;
    logger::say(info, l::error, true);
}

null_pointer_exception::null_pointer_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Null pointer exception] " + msg;
    logger::say(info, l::error, true);
}

out_of_bounds_exception::out_of_bounds_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Out of bounds exception] " + msg;
    logger::say(info, l::error, true);
}

conflict_exception::conflict_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Conflict bounds exception] " + msg;
    logger::say(info, l::error, true);
}

rights_exception::rights_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Rights exception] " + msg;
    logger::say(info, l::error, true);
}

type_exception::type_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Type exception] " + msg;
    logger::say(info, l::error, true);
}
