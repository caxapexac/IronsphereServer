#ifndef LOGIC_MOVE_HPP
#define LOGIC_MOVE_HPP

#include "../base/includes.hpp"

namespace com {
    const std::string move_type = "move";
    class move : public icomponent {
    public:
        const std::string& type () const override;
        void setup_prototype (ent::unit_prototype& prototype) override;
        void command (ent::unit& sender, ent::unit& owner, game::base_game& context, json& input) override;
        void signal (ent::unit& owner, game::base_game& context, json& input) override;
        void update (ent::unit& owner, game::base_game& context) override;
    };
}

#endif //LOGIC_MOVE_HPP
