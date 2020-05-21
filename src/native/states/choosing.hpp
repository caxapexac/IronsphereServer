#ifndef LOGIC_CHOOSING_HPP
#define LOGIC_CHOOSING_HPP

#include "../base/includes.hpp"

namespace online { class session; }

namespace states {
    const std::string choosing_type = "state_choose";
    class choosing : public ihandler {
    private:
        online::session& session;
    public:
        explicit choosing (online::session& context);
        const std::string& type () const override;
        void load (json& input, json& output) override;
        void save (json& output) override;
        void join (int player_uid, json& output) override;
        void quit (int player_uid, json& output) override;
        void play (json& output) override;
        void pause (json& output) override;
        void stop (json& output) override;
        void setup (json& input, json& output) override;
        void update (json& output) override;
        void signal (json& input, json& output) override;
    };
}


#endif //LOGIC_CHOOSING_HPP
