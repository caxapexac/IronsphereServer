#include "simple.hpp"
#include "../game/realtime.hpp"
#include "../tilemap/square.hpp"
#include "../rules/skirmish.hpp"

#define PI double(3.1415926)


stts::vector2<int> generators::simple::cir_set (int number, int total) {
    double ang = 360.0 / total * number;
    double trueAng = PI * (0.5 - 2.0 * (ang / 360.0));
    int x = tilemap_scale.x / 2 + (int) (cos(trueAng) * tilemap_scale.x / 8 * 3);
    int y = tilemap_scale.y / 2 - (int) (sin(trueAng) * tilemap_scale.y / 8 * 3);
    return stts::vector2<int>(x, y);
}



generators::simple::simple (int nseed, int nplayers_count, const stts::vector2<int>& ntilemap_scale) {
    seed = nseed;
    players_count = nplayers_count;
    tilemap_scale = ntilemap_scale;
}

generators::simple::simple (json& package) {
    simple::deserialize(package);
}

void generators::simple::serialize (json& package) const {
    abstract_generator::serialize(package);
    package[j_simple::seed] = seed;
    package[j_simple::players_count] = players_count;
    tilemap_scale.serialize(package[j_simple::tilemap_scale]);
}

void generators::simple::deserialize (json& package) {
    abstract_generator::deserialize(package);
    package[j_simple::seed] = seed;
    package[j_simple::players_count] = players_count;
    tilemap_scale.serialize(package[j_simple::tilemap_scale]);
}

const std::string& generators::simple::type () const {
    return j_simple::type;
}

std::unique_ptr<game::abstract_game> generators::simple::generate () {
    srand(seed);
    std::unique_ptr<game::abstract_game> game = std::make_unique<game::realtime>();

    // Tilemap
    std::unique_ptr<tilemap::abstract_tilemap> tilemap = std::make_unique<tilemap::square>(tilemap_scale);
    game->set_tilemap(std::move(tilemap));
    for (int ny = 0; ny < tilemap_scale.y; ny++) {
        for (int nx = 0; nx < tilemap_scale.x; nx++) {
            int per_seed = rand();
            int tile_seed = (abs(per_seed * nx * ny)) % 10;
            float height = (float) (per_seed % 50) - 25;

            tile::base_tile* tile;
            if (tile_seed % 5 == 0) {
                tile = new tile::damage_dealer(height);
            } else if (tile_seed % 3 == 0) {
                tile = new tile::money_dealer(height);
            } else {
                tile = new tile::base_tile(height);
            }
            game->get_tilemap().set_tile(nx, ny, tile);
        }
    }
    //game->set_rule(rules::skirmish());

    // Factory
    ent::unit_prototype p_runner = ent::unit_prototype("runner");
    p_runner.add_component(com::j_move::type);
    game->set_prototype(&p_runner);


    // Players
    for (int i = 1; i <= players_count; ++i) {
        stts::player *player = new stts::player(i);
        player->set(stts::player_params::money, seed % 400 + 100);
        game->set_player(i, player);

        stts::vector2<int> spawn = cir_set(i-1, players_count);
        int radius = tilemap_scale.x / 16;

        float middle_height = 0.0;
        double square = radius*radius*4.0;
        for (int j = spawn.y - radius; j < spawn.y + radius; ++j) {
            for (int k = spawn.x - radius; k < spawn.y + radius; ++k) {
                middle_height += game->get_tilemap().get_tile(k, j).get_height();
            }
        }

        middle_height /= (float) square;

        for (int j = spawn.y - radius; j < spawn.y + radius; ++j) {
            for (int k = spawn.x - radius; k < spawn.y + radius; ++k) {
                 game->get_tilemap().get_tile(k, j).set_height(middle_height);
            }
        }

        stts::vector2<int> unit1_offset(-radius/2, 0), unit2_offset(radius/2, 0);

        // Units
        ent::unit &u_runner_1 = game->make_unit("runner", i);
        game->get_tilemap().transpose(u_runner_1, spawn + stts::vector2<int>(-radius/2, 0));

        if (unit1_offset != unit2_offset) { // TODO: remove this to test on SANE-SIZED maps
            ent::unit &u_runner_2 = game->make_unit("runner", i);
            game->get_tilemap().transpose(u_runner_2, spawn + stts::vector2<int>(radius / 2, 0));
        }
    }

    return std::move(game);
}
