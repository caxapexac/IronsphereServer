#ifndef LOGIC_PLAYING_HPP
#define LOGIC_PLAYING_HPP

#include "../base/includes.hpp"

namespace online { class session; }

namespace states {
    const std::string playing_type = "playing";
    class playing : public ihandler {
    private:
        online::session& session;
    public:
        explicit playing (online::session& context);
        const std::string& type () const override;
        void info (json& output) override;
        void load (json& input, json& output) override;
        void save (json& output) override;
        void join (json& input, json& output) override;
        void quit (json& input, json& output) override;
        void play (json& output) override;
        void pause (json& output) override;
        void stop (json& output) override;
        void setup (json& input, json& output) override;
        void update (json& output) override;
        void signal (json& input, json& output) override;
    };
}

#endif //LOGIC_PLAYING_HPP
