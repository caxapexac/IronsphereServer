#include "game_loop.hpp"

std::string game_loop::start (const std::string& data) {
    return "starts with: " + data;
}

std::string game_loop::update (const std::string& data) {
    return "updates with: " + data;
}

std::string game_loop::signal (const std::string& data) {
    return "signals with: " + data;
}

std::string game_loop::destroy (const std::string& data) {
    return "destroys with: " + data;
}
