#ifndef LOGIC_STORAGE_HPP
#define LOGIC_STORAGE_HPP

#include "../base/includes.hpp"

namespace com {
    const std::string storage_type = "storage";
    class storage : public icomponent {
    public:
        const std::string& type () const override;
        void setup_prototype (ent::unit_prototype& prototype) override;
        void command (ent::unit& sender, ent::unit& owner, game::base_game& context, json& input) override;
        void signal (ent::unit& owner, game::base_game& context, json& input) override;
        void update (ent::unit& owner, game::base_game& context) override;
    };
}


#endif //LOGIC_STORAGE_HPP
