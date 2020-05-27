#ifndef LOGIC_LOG_HPP
#define LOGIC_LOG_HPP

// TODO logger should be accesible using base/includes import, includes should be changed to avoid forward declaration
#include "../base/includes.hpp"
#include "../utils/singleton.hpp"

#include "abstract_logger.hpp"
#include "logger_server.hpp"
#include "logger_client.hpp"
#include "logger_user.hpp"
#include "logger_file.hpp"

namespace l {
    class on : public utils::singleton<on> {
        friend class utils::singleton<on>;
    private:
        void send (std::string& verbal);

        bool serverL, clientL, fileL;
        logger_server* SL{};
        logger_client* CL{};
        logger_file* FL{};
        logger_user* UL{};

        streams stream;
        std::ostringstream alpha;

        using utils::singleton<on>::get;

    protected:
        on();

    public:
        ~on () = default;

        static void set_server_logger (logger_server* log);
        static void set_client_logger (logger_client* log);
        static void set_file_logger (logger_file* log);
        static void set_user_logger (logger_user* log);
        static void toggle_loggers (bool server, bool client, bool file);

        static on& say (streams str = message);
        static void say_to (int addressee, std::string& msg, streams str = message);

        template<typename T>
        friend l::on& operator<< (l::on& out, const T& value);
        friend l::on& operator<< (l::on& out, json& object);
        friend l::on& operator<< (l::on& out, l::on& (* f) (l::on&));
        friend void operator<< (l::on& out, void (* f) (l::on&));
        //TODO: for iSerializable,  any object to say

        static on& over (on& out);
        static void out (on& out);
        //....
    };


    template<typename T>
    l::on& l::operator<<(l::on &out, const T &value) {
        out.alpha << value;
        return out;
    }
}


#endif //LOGIC_LOG_HPP
