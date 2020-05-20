#ifndef LOGIC_UNIT_HPP
#define LOGIC_UNIT_HPP

#include "../base/includes.hpp"
#include "unit_prototype.hpp"

namespace game { class base_game; }

namespace ent {
    class unit : public stts::parameter_map {
    private:
        unit_prototype* prototype;
        int player_id;
        int id;

    public:
        explicit unit (unit_prototype* nprototype = nullptr, int nplayer_id = -1, int nid = -1);
        void serialize (json& package) const final;
        void deserialize (json& package) final;

        void set_prototype (unit_prototype* nprototype);

        int get_player_id ();
        int get_id ();

        void update (game::base_game& context); // Server -> Unit
        void signal (game::base_game& context, json& input); // User -> Unit
        void command (unit& sender, game::base_game& context, json& input); // Unit -> Unit

        template<typename T>
        T get_parameter (const std::string& parameter_name);

        template<typename T>
        void set_parameter (const std::string& parameter_name, T data);
    };

    template<typename T>
    T unit::get_parameter (const std::string& parameter_name) {
        T result;
        if (get<T>(parameter_name, result)) {
            return result;
        }
        else if (prototype) {
            return prototype->get_parameter<T>(parameter_name);
        }
        else {
            throw todo_exception(parameter_name + " parameter wasn't found");
        }
    }

    template<typename T>
    void unit::set_parameter (const std::string& parameter_name, T data) {
        // TODO is needed?
        set(parameter_name, data);
    }
}


#endif //LOGIC_UNIT_HPP
