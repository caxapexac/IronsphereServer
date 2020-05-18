#ifndef LOGIC_LOGIC_TEST_HPP
#define LOGIC_LOGIC_TEST_HPP

#include "../base/includes.hpp"
#include "../utils/timer.hpp"
#include "../game/game_realtime.hpp"
#include "../tilemap/tilemap_square.hpp"

namespace unit_testing {
    void test_logic() {
        std::cout << "* test_logic [started] \n"
                     "* Print '-' to stop testing\n"
                     "* Enter empty string to update\n" << std::endl; //TODO logger

        srand(time(nullptr));
        const vector2<int> tilemap_scale = vector2<int>(9, 12);


        base_game game = base_game();

        // Tilemap
        std::unique_ptr<abstract_tilemap> tilemap = std::make_unique<tilemap_square>(tilemap_scale);
        game.set_tilemap(std::move(tilemap));

        //tile* t = new tile();
        //tile_damage* t_d = new tile_damage();
        for (int ny = 0; ny < tilemap_scale.y; ny++) {
            for (int nx = 0; nx < tilemap_scale.x; nx++) {
                game.get_tilemap().set_tile(nx, ny, new tile(nx * 10 + ny));
            }
        }

        // Players
        game.set_player(1, new player(1));
        game.set_player(2, new player(2));

        // Factory
        unit_prototype p_runner = unit_prototype("runner");
        p_runner.add_component(com_move_type);
        game.set_prototype(&p_runner);

        // Units
        unit& u_runner_1 = game.make_unit("runner", 1);
        game.get_tilemap().transpose(u_runner_1, vector2<int>(0, 0));
        unit& u_runner_2 = game.make_unit("runner", 2);
        game.get_tilemap().transpose(u_runner_2, vector2<int>(6, 7));

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

        std::string command = "";
        while (command != "-") {
            //std::cin >> command;
            std::getline(std::cin, command);

            if (command.empty()) {
                //std::cout << "upd" << std::endl;
                json j;
                game.update(j);
            }
            else {
                json input;
                vector2<int> position = vector2<int>(rand() % tilemap_scale.x, rand() % tilemap_scale.y);
                input["component"] = com_move_type;
                input["is_moving"] = true;
                position.serialize(input["move_target"]);
                json output;
                u_runner_1.signal(game, input);
                //game.signal(input, output);
            }
            //
            json_tools::print_tilemap(game.get_tilemap());
            //
        }
        std::cout << "* test_logic [success]" << std::endl;
    }
}

#endif //LOGIC_LOGIC_TEST_HPP
