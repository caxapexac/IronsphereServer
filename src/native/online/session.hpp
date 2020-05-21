#ifndef LOGIC_SESSION_HPP
#define LOGIC_SESSION_HPP

#include "../base/includes.hpp"
#include "../game/base_game.hpp"
#include "../states/choosing.hpp"
#include "../states/playing.hpp"
#include "../states/holding.hpp"

namespace online {
    const std::string session_type = "session";
    class session : public ihandler {
        friend class states::choosing;
        friend class states::playing;
        friend class states::holding;

    private:
        std::string session_name;
        std::set<int> players_uid; // For security
        std::unique_ptr<ihandler> state; // Game state TODO maybe change all output errors to exceptions?
        std::unique_ptr<game::base_game> game; // Game & game rules

    public:
        explicit session (const std::string& nsession_name);
        const std::string& type () const override;

        std::string get_session_name ();
        int get_player_count ();
        void session_info(json& output);
        void info (json& output);
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

    private:
        void transition_to (std::unique_ptr<ihandler> nstate);
    };
}

#endif //LOGIC_SESSION_HPP
