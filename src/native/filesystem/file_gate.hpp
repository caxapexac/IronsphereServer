#ifndef LOGIC_FILE_GATE_HPP
#define LOGIC_FILE_GATE_HPP

#include "../online/api.hpp"

namespace file {
    class file_gate {
        friend class online::api;

    private:
        static std::string ROOT;
    };
}

#endif //LOGIC_FILE_GATE_HPP
