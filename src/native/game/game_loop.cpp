#include "game_loop.hpp"

std::string game_loop::start(std::string data)
{
    return "starts with: " + data;
}

std::string game_loop::update(std::string data)
{
    return "updates with: " + data;
}

std::string game_loop::signal(std::string data)
{

    return "signals with: " + data;
}

std::string game_loop::destroy(std::string data)
{

    return "destroys with: " + data;
}
