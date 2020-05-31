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

        stts::vector2<int> size {20, 10};
        std::set<int> players;
        players.emplace(1);
        generators::simple gen(1, players, size);
        std::unique_ptr<game::abstract_game> game = gen.generate();

        /*
        srand(time(nullptr));
        const stts::vector2<int> tilemap_scale = stts::vector2<int>(9, 12);

        game::realtime game = game::realtime();

        // Tilemap
        std::unique_ptr<tilemap::abstract_tilemap> tilemap = std::make_unique<tilemap::square>(tilemap_scale);
        game.set_tilemap(std::move(tilemap));

        //tile* t = new tile();
        //tile_damage* t_d = new tile_damage();
        for (int ny = 0; ny < tilemap_scale.y; ny++) {
            for (int nx = 0; nx < tilemap_scale.x; nx++) {
                game.get_tilemap().set_tile(nx, ny, new tile::base_tile(nx * 10 + ny));
            }
        }

        // Players
        game.set_player(1, new stts::player(1));
        game.set_player(2, new stts::player(2));

        // Factory
        ent::unit_prototype p_runner = ent::unit_prototype("runner");
        p_runner.add_component(com::j_move::type);
        game.set_prototype(&p_runner);

        // Units
        ent::unit& u_runner_1 = game.make_unit("runner", 1);
        game.get_tilemap().transpose(u_runner_1, stts::vector2<int>(0, 0));
        ent::unit& u_runner_2 = game.make_unit("runner", 2);
        game.get_tilemap().transpose(u_runner_2, stts::vector2<int>(6, 7));
         */

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
                /*json input;
                input[com::j_move_signal::is_moving] = true;
                stts::vector2<int> position = stts::vector2<int>(rand() % tilemap_scale.x, rand() % tilemap_scale.y);
                position.serialize(input[com::j_move_signal::move_target]);
                json output;
                u_runner_1.signal(game, com::j_move::type, input);*/
                //game.signal(input, output);
            }
            //
            nlohmann::json_tools::print_tilemap(game->get_tilemap());
            //
        }
        std::cout << "* test_logic [success]" << std::endl;
    }
}

#endif //LOGIC_LOGIC_TEST_HPP
