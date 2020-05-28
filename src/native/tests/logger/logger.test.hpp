#ifndef LOGIC_LOGGER_TEST_HPP
#define LOGIC_LOGGER_TEST_HPP

#include "../../logger/on.hpp"

namespace unit_testing {
    void test_logger() {
        // maybe add some sample json and iserializable objects to test? Haven't found any with obvious constructors.
        l::on::say() << "Message sent via SO operator, also includes numbers, characters, whatever:" << 'a' << " " << 128 << l::on::over << "And one another string too" << l::on::out;
        l::on::say("Warning string via say operator", l::warning);
        l::on::say(404, l::error);
    }
}

#endif //LOGIC_LOGGER_TEST_HPP
