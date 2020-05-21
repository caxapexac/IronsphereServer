#ifndef LOGIC_UNIT_HPP
#define LOGIC_UNIT_HPP

#include "../base/includes.hpp"
#include "unit_prototype.hpp"

namespace game { class base_game; }

namespace ent {
    class unit : protected stts::parameter_map {
    private:
        unit_prototype* prototype;
        int player_id;
        int id;

        N_S mutable bool is_dirty;
        N_S mutable json cache;
        N_S mutable json cache_public;

    public:
        explicit unit (unit_prototype* nprototype = nullptr, int nplayer_id = -1, int nid = -1);
        void serialize (json& package) const final;
        void deserialize (json& package) final;
        void serialize_public(json& package) const;

        void set_prototype (unit_prototype* nprototype);
        void set_dirty();

        int get_player_id ();
        int get_id ();

        void update (game::base_game& context); // Server -> Unit
        void signal (game::base_game& context, json& input); // User -> Unit
        void command (unit& sender, game::base_game& context, json& input); // Unit -> Unit

        template<typename T>
        bool has_parameter (const std::string& parameter_name) const;

        template<typename T>
        T get_parameter (const std::string& parameter_name) const;

        template<typename T>
        void ensure_parameter (const std::string& parameter_name, T data);

        template<typename T>
        void set_parameter (const std::string& parameter_name, T data);

    private:
        void ensure_cache() const;
    };

    template<typename T>
    bool unit::has_parameter (const std::string& parameter_name) const {
        T result;
        if (get<T>(parameter_name, result)) {
            return true;
        }
        else if (prototype) {
            return prototype->has_parameter<T>(parameter_name);
        }
        else {
            return false;
        }
    }

    template<typename T>
    T unit::get_parameter (const std::string& parameter_name) const {
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
    void unit::ensure_parameter (const std::string& parameter_name, T data) {
        if (!has_parameter<T>(parameter_name)) set(parameter_name, data);
    }

    template<typename T>
    void unit::set_parameter (const std::string& parameter_name, T data) {
        set(parameter_name, data);
    }
}


#endif //LOGIC_UNIT_HPP
