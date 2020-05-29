#ifndef LOGIC_LOGGER_TEST_HPP
#define LOGIC_LOGGER_TEST_HPP

#include "../../base/includes.hpp"
#include "../../structs/chat_message.hpp"
#include "../../filesystem/file_gate.hpp"

namespace unit_testing {
    void test_logger() {
        stts::chat_message vec {42, "Chat message"};
        json j {"asap", 34};

        logger::enable_logger(false, l::loggers::user_logger);
        logger::enable_logger(false, l::loggers::broadcast_logger);

        logger::say("Logger testing started...");
        logger::say() << "This is a not decorated message via stream output operator..." << logger::over << "...and this is a decorated one." << logger::out;
        logger::say() << "Stream operator accepts any types, including: (char) " << 'a' << ", (int) " << 128 << ", (float) " << 128.256 << ", und so weiter..." << logger::out;
        logger::say() << "It also accepts some special types: (JSON) " << j << logger::out;
        logger::say() << "And ISerializable: (iserializable) " << dynamic_cast<iserializable&>(vec) << logger::out; // FIXME: logger iserializable error!
        logger::say() << "And here go some examples of logs send via special logger::say() function (with special modifiers):" << logger::out;
        logger::say() << "A warning string:" << logger::out;
        logger::say("That's the string!", l::warning);
        logger::say() << "An error number:" << logger::out;
        logger::say(404, l::error);
        logger::say() << "A debug iserializable:" << logger::out;
        logger::say(dynamic_cast<iserializable&>(vec), l::debug); // FIXME: logger iserializable error!
        logger::say() << "A special JSON:" << logger::out;
        logger::say(j, l::special);
        logger::say("Logger testing finished!");
        logger::say() << logger::over;
    }
}

#endif //LOGIC_LOGGER_TEST_HPP
