#ifndef LOGIC_LOGGER_TEST_HPP
#define LOGIC_LOGGER_TEST_HPP

#include "../../logger/on.hpp"

namespace unit_testing {
    void test_logger() {
        l::on::set_server_logger(new l::logger_server);
        l::on::set_client_logger(new l::logger_client);
        l::on::set_file_logger(new l::logger_file);
        l::on::toggle_loggers(true, true, true);

        l::on::say() << "Server started at XXX" << l::on::out;

        l::on::set_user_logger(new l::logger_user);
        std::string lol = "LOL";
        l::on::say_to(12, lol);
    }
}

#endif //LOGIC_LOGGER_TEST_HPP
