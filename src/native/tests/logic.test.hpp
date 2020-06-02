#ifndef LOGIC_LOGIC_TEST_HPP
#define LOGIC_LOGIC_TEST_HPP

#include "../base/includes.hpp"
#include "../utils/timer.hpp"
#include "../game/realtime.hpp"
#include "../tilemap/square.hpp"
#include "../components/component_storage.hpp"
#include "../generators/simple.hpp"

namespace unit_testing {
    void test_logic() {
        std::cout << "* test_logic [started]" << std::endl; //TODO logger

        stts::vector2<int> size {35, 35};
        std::set<int> players;
        players.emplace(1);
        players.emplace(2);
        generators::simple gen(1, players, size);
        std::unique_ptr<game::abstract_game> game = gen.generate();

        // saving
        //json k;
        //game.serialize(k);
        //std::cout << k.dump(2);

        // json sig;
        // sig[com_move_type]["type"] = "move";
        // vector2<int> target_position = vector2<int>(1, 2);
        // target_position.serialize(sig[com_move_type]["position"]);
        // json out;
        // game.signal(sig, out);


        //timer t = timer();
        //t.setInterval(game.update, 1000);

        std::cout << "* Print 'q' to stop testing\n"
                     "* Enter empty string to update" << std::endl;
        std::string command = "";
        while (true) {
            std::getline(std::cin, command);

            if (command.empty()) {
                json j;
                game->update(j);
            }
            else if (command == "q") {
                break;
            }
            else {
                json input2;
                input2[com::j_move_signal::is_moving] = true;
                stts::vector2<int> position = stts::vector2<int>(rand() % game->get_tilemap().get_scale().x, rand() % game->get_tilemap().get_scale().y);
                position.serialize(input2[com::j_move_signal::move_target]);
                input2[com::j_attack_signal::attack_target] = 3;
                input2[com::j_attack_signal::is_attacking] = true;
                json output;
                game->get_unit(2)->signal(*(game.get()), com::j_move::type, input2);
                game->get_unit(2)->signal(*(game.get()), com::j_attack::type, input2);

                json input1;
                input1[com::j_spawner_signal::production_line] = 3;
                output = {};
                game->get_unit(1)->signal(*(game.get()), com::j_spawner::type, input1);
                //game->signal(input, output);
            }
            //
            int money;
            game->get_player(1).get(stts::player_params::money, money);
            std::cout << "Player 1 ownes objects 1, 2; has " << money << " money." << std::endl;
            std::cout << "Object 1 is generating " << game->get_unit(1)->get_parameter<int>(com::j_spawner::production_line) << " objects " <<
                    "(first be ready in " << 10 - game->get_unit(1)->get_parameter<int>(com::j_spawner::production_tikz) << " updates)." << std::endl;
            stts::vector2<int> first_moves = game->get_unit(2)->get_parameter<stts::vector2<int>>(com::j_move::move_target);
            stts::vector2<int> first_at = game->get_unit(2)->get_parameter<stts::vector2<int>>(com::j_locationable::position);
            std::cout << "Object 2 is in tile (" << first_at.x << " ," << first_at.y << ") and is moving towards (" << first_moves.x << " ," << first_moves.y << "). " <<
                    "It is attacking object " << game->get_unit(2)->get_parameter<int>(com::j_attack::attack_target) << " with damage " <<
                            game->get_unit(2)->get_parameter<float>(com::j_attack::damage) << "." << std::endl;
            std::cout << "Object 3 has " << game->get_unit(3)->get_parameter<float>(com::j_mortal::hp) << " HP and "  <<
                    game->get_unit(3)->get_parameter<float>(com::j_mortal::armor) << " armor left." << std::endl;
            nlohmann::json_tools::print_tilemap(game->get_tilemap());
            //
        }
        std::cout << "* test_logic [success]" << std::endl;
    }
}

#endif //LOGIC_LOGIC_TEST_HPP
