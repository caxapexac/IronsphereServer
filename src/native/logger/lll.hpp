#ifndef LOGIC_LOG_HPP
#define LOGIC_LOG_HPP

// TODO logger should be accesible using base/includes import, includes should be changed to avoid forward declaration
#include "../base/includes.hpp"

#include "abstract_logger.hpp"
#include "logger_server.hpp"
#include "logger_client.hpp"
#include "logger_user.hpp"
#include "logger_file.hpp"

class game_lobby;

namespace l {
    // TODO rename please) maybe out
    class lll {
    private:
        bool subduce ();
        void send (std::string& verbal);

        streams stream;
        unsigned int logs;
        std::ostringstream alpha;
        bool to;

        abstract_logger* log_arr[3];
        logger_user* usr;

    public:
        explicit lll ();
        ~lll () = default;

        void set_logger (abstract_logger* log, loggers type);
        void set_user_logger (logger_user* log);

        static lll& say (streams str = message, unsigned int logs = 7);
        static lll& say_to (std::string& addressee, streams str = message);

        template<typename T>
        friend lll& operator<< (lll& out, const T& value);
        friend lll& operator<< (lll& out, json& object);
        friend lll& operator<< (lll& out, lll& (* f) (lll&));
        friend void operator<< (lll& out, void (* f) (lll&));
        //TODO: for iSerializable,  any object to say

        static lll& over (lll& out);
        static void out (lll& out);
        //....
    };
}

template<typename T>
l::lll& operator<< (l::lll& out, const T& value) {
    out.alpha << value;
    return out;
}


#endif //LOGIC_LOG_HPP
