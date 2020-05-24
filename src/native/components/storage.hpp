#ifndef LOGIC_STORAGE_HPP
#define LOGIC_STORAGE_HPP

#include "../base/includes.hpp"

namespace com {
    // JSON
    namespace j_storage {
        const std::string type = TOSTRING(storage);
    }

    class storage : public icomponent {
    public:
        const std::string& type () const override;
        void serialize_public (const ent::unit& owner, json& package) const override;
        void setup_prototype (ent::unit_prototype& prototype) override;
        void command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) override;
        void signal (ent::unit& owner, game::abstract_game& context, json& input) override;
        void update (ent::unit& owner, game::abstract_game& context) override;
    };
}


#endif //LOGIC_STORAGE_HPP
