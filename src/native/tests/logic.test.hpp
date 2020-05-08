#ifndef LOGIC_LOGIC_TEST_HPP
#define LOGIC_LOGIC_TEST_HPP

#include "../base/interfaces.hpp"
#include "../utils/timer.hpp"
#include "../game/game_realtime.hpp"

namespace unit_testing {
    void test_base_game() {
        std::cout << "* test_base_game [started]" << std::endl; //TODO logger
        base_game game = base_game();

        std::map<int, unit*> units = std::map<int, unit*>();
        units[0] = new unit(game);
        units[3] = new unit(game);

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
        j["tilemap"]["type"] = "square";
        j["tilemap"]["data"] = json::array();
        for (int i = 0; i < scale.x * scale.y; i++) {
            json tj;
            tile t = tile(i);
            t.serialize(tj);
            j["tilemap"]["data"].push_back(tj);
        }
        j["tilemap"]["scale"]["x"] = scale.x;
        j["tilemap"]["scale"]["y"] = scale.y;


        game.deserialize(j);
        // loading

        // ...something

        // saving
        json k;
        game.serialize(k);
        std::cout << k.dump(2);

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
            std::cout << command << command.size() << std::endl;
            //

        }


        std::cout << "* test_base_game [success]" << std::endl;
    }
}

#endif //LOGIC_LOGIC_TEST_HPP
