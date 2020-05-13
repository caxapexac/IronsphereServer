#ifndef LOGIC_LOGIC_TEST_HPP
#define LOGIC_LOGIC_TEST_HPP

#include "../base/includes.hpp"
#include "../utils/timer.hpp"
#include "../game/game_realtime.hpp"
#include "../tilemap/tilemap_square.hpp"

namespace unit_testing {
    void test_logic() {
        std::cout << "* test_base_game [started]" << std::endl; //TODO logger

        std::map<int, unit*> units = std::map<int, unit*>();
        unit_prototype proto_1 = unit_prototype("proto_1");
        proto_1.add_component(com_move_type);
        //unit_prototype proto_2 = unit_prototype("proto_2", &proto_1);
        unit* unit_1 = new unit(&proto_1);
        unit_1->set_parameter("position", vector2<int>(0, 1));
        units[0] = unit_1;

        //units[3] = new unit();

        std::map<int, player*> players = std::map<int, player*>();
        players[0] = new player(0);
        players[1] = new player(1);


        json units_package;
        json_tools::pack_map_of_ptrs(units, units_package);
        //std::cout << units_package.dump(2) << std::endl;

        json players_package;
        json_tools::pack_map_of_ptrs(players, players_package);
        std::cout << players_package.dump(2) << std::endl;

        vector2<int> scale = vector2<int>(2, 3);

        json j;
        //j["type"];
        j["factory"]["next_id"] = 2;
        j["players"] = players_package;
        j["units"] = units_package;
        j["tilemap"]["type"] = tilemap_square_type;
        j["tilemap"]["data"] = json::array();
        for (int i = 0; i < scale.x * scale.y; i++) {
            json tj;
            tile t = tile(i);
            t.serialize(tj);
            j["tilemap"]["data"].push_back(tj);
        }
        j["tilemap"]["scale"]["x"] = scale.x;
        j["tilemap"]["scale"]["y"] = scale.y;

        base_game game = base_game();
        game.deserialize(j);
        // loading

        // ...something

        // saving
        json k;
        game.serialize(k);
        std::cout << k.dump(2);

        json sig;
        sig[com_move_type]["type"] = "move";
        vector2<int> target_position = vector2<int>(1, 2);
        target_position.serialize(sig[com_move_type]["position"]);
        json out;
        game.signal(sig, out);


        //timer t = timer();
        //t.setInterval(game.update, 1000);

        std::string command = "";
        while (command != "-") {
            //std::cin >> command;
            std::getline(std::cin, command);

            if (command == "") {
                //std::cout << "upd" << std::endl;
                json j;
                game.update(j);
            }
            else {
                json input;
                json output;
                game.signal(input, output);
            }
            //
            json_tools::print_tilemap(game.get_tilemap());
            //

        }


        std::cout << "* test_base_game [success]" << std::endl;
    }
}

#endif //LOGIC_LOGIC_TEST_HPP
