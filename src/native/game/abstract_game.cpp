#include "abstract_game.hpp"
#include "../rules/abstract_rule.hpp"

game::abstract_game::abstract_game () {
    factory = ent::unit_factory();
    rule = nullptr;
    units = std::map<int, ent::unit*>();
    players = std::map<int, stts::player*>();
    tilemap = nullptr; // TODO create tilemap
}

game::abstract_game::abstract_game (json& package) {
    abstract_game::deserialize(package);
}

void game::abstract_game::serialize (json& package) const {
    package[j_typed::type] = type();
    factory.serialize(package[j_abstract_game::factory]);
    if (rule) rule->serialize(package[j_abstract_game::rule]);
    json_tools::pack_map_int_of_ptrs(units, package[j_abstract_game::units]);
    json_tools::pack_map_int_of_ptrs(players, package[j_abstract_game::players]);
    if (tilemap) tilemap->serialize(package[j_abstract_game::tilemap]);
}

void game::abstract_game::deserialize (json& package) {
    factory = ent::unit_factory(package[j_abstract_game::factory]);
    rule = json_tools::unpack_rule(package[j_abstract_game::rule]);
    units = json_tools::unpack_map_int_of_ptrs<ent::unit>(package[j_abstract_game::units]);
    players = json_tools::unpack_map_int_of_ptrs<stts::player>(package[j_abstract_game::players]);
    if (package.contains(j_abstract_game::tilemap)) tilemap = json_tools::unpack_tilemap(package["tilemap"]);
}

void game::abstract_game::serialize_public (json& package) const {
    package[j_typed::type] = type();
    factory.serialize(package[j_abstract_game::factory]);
    rule->serialize(package[j_abstract_game::rule]);
    json_tools::pack_map_int_of_ptrs(players, package[j_abstract_game::players]); // TODO serialize_public
    if (tilemap) tilemap->serialize_public(package[j_abstract_game::tilemap]);
}

bool game::abstract_game::is_finished () const {
    return rule->is_finished(players, units);
}

rules::abstract_rule& game::abstract_game::get_rule () {
    return *rule;
}

void game::abstract_game::set_rule (std::unique_ptr<rules::abstract_rule> nrule) {
    rule = std::move(nrule);
}

void game::abstract_game::signal (json& input, json& output) {
    if (input[in_game_signal::units].type() != json::value_t::array) {
        output[out_signal::error] = LOCATED("wrong json");
        return;
        // TODO more checkings
    }

    int sender_uid = input[in_signal::sender].get<int>();
    for (auto& i : input[in_game_signal::units]) {
        int id = i.get<int>(); // TODO type checking
        ent::unit* target = get_unit(id);
        if (target == nullptr) {
            output[out_signal::error] = LOCATED("Unit with this id doesn't exist check your internet connection");
            // TODO collect all errors in str concat big string maybe
            continue;
        }
        if (target->get_player_id() != sender_uid) {
            output[out_signal::error] = LOCATED("This unit is not yours");
            continue;
        }
        // TODO validate command
        target->signal(*this, input[in_game_signal::component], input[in_game_signal::data]);
        output[out_signal::success] = LOCATED("Your command was sent");
    }
}

ent::unit& game::abstract_game::make_unit (const std::string& prototype_name, int player_uid) {
    ent::unit* result = factory.make_unit(prototype_name, player_uid);
    units[result->get_id()] = result;
    return *units[result->get_id()];
    // TODO simplify
}

ent::unit_prototype* game::abstract_game::get_prototype (const std::string& prototype_name) {
    return factory.get_prototype(prototype_name);
}

void game::abstract_game::set_prototype (ent::unit_prototype* prototype) {
    factory.set_prototype(prototype);
}

ent::unit* game::abstract_game::get_unit (int id) {
    return units[id];
}

stts::player& game::abstract_game::get_player (int uid) {
    return *players[uid];
}

void game::abstract_game::set_player (int uid, stts::player* nplayer) {
    if (players[uid] != nullptr) throw conflict_exception("Player with this uid is already exist");
    // TODO maybe replace instead of exception
    players[uid] = nplayer;
}

tilemap::abstract_tilemap& game::abstract_game::get_tilemap () {
    return *tilemap;
}

void game::abstract_game::set_tilemap (std::unique_ptr<tilemap::abstract_tilemap> ntilemap) {
    tilemap = std::move(ntilemap);
}













