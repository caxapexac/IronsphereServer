#include "game_lobby.hpp"

game_lobby::game_lobby () noexcept {
    delta_time = constants::lobby_delta_time;
    sessions = std::map<int, std::shared_ptr<game_session>>();
    chat_buffer = json::array();
    // TODO log it
}

void game_lobby::update (json& output) {
    output["delta_time"] = delta_time;
    output["chat_buffer"] = chat_buffer;
    // TODO maybe output["log"] = logger_client::get().log();
    chat_buffer.clear();
    for (const auto& item : sessions) {
        item.second->get_state().update(output["sessions"][item.first]);
    }
}

void game_lobby::signal (json& input, json& output) {
    if (input["version"] == nullptr || input["version"].get<int>() != constants::version) {
        output = {{"error", "Please download the latest version of the game"}};
        return;
    }

    if (input["command"] == nullptr) {
        output = {{"error", "Input isn't correct"}};
    }
    else if (input["command"] == "get_info") {
        get_info(output);
    }
    else if (input["command"] == "write_chat") {
        write_chat(input["data"], output);
    }
    else if (input["command"] == "join_or_create") {
        join_or_create(input["data"], output);
    }
    else if (input["command"] == "session") {
        session(input["data"], output);
    }
    else {
        output = {{"error", "Command isn't correct"}};
    }
}

void game_lobby::get_info (json& output) {
    output["status"] = "alive";

    std::set<int> players_online;
    for (const auto& item : sessions) {
        item.second->get_state().serialize(output["sessions"][item.first], serial_info);
        for (const auto& player_id : output["sessions"][item.first]["players_id"]) {
            players_online.emplace(player_id);
        }
    }

    output["players_online"] = players_online;
}

void game_lobby::write_chat (json& input, json& output) {
    chat_buffer.push_back(input);
    output = {"success", "Message has been sent"};
    //TODO improve, make write_chat rooms
    //TODO write_chat history
    //TODO important game events into write_chat (for example, logger::setup_lobby(this) then use logger::log_chat();
}

void game_lobby::join_or_create (json& input, json& output) {
    // Error checking
    if (input["method"] == nullptr || input["session_id"] == nullptr || input["sender"] == nullptr) {
        output = {{"error", "Input isn't correct"}};
        return;
        //TODO maybe into exceptions
    }
    // Algorithm
    if (sessions[input["session_id"]] == nullptr) {
        sessions[input["session_id"]] = std::make_shared<game_session>();
        sessions[input["session_id"]]->get_state().join(input["sender"], output);
    }
    else if (sessions[input["session_id"]]->get_player_index(input["sender"].get<int>()) == -1) {
        sessions[input["session_id"]]->get_state().join(input["sender"], output);
    }
    else {
        output = {{"error", "Player is already in this room"}};
    }
}

void game_lobby::session (json& input, json& output) {
    // Error checking
    if (input["method"] == nullptr || input["session_id"] == nullptr || input["sender"] == nullptr) {
        output = {{"error", "Input isn't correct"}};
        return;
        //TODO maybe into exceptions
    }

    std::shared_ptr<game_session> current = sessions[input["session_id"]];
    if (current == nullptr) {
        output = {{"error", "Session wasn't found"}};
        return;
    }

    if (current->get_player_index(input.get<int>()) == -1) {
        output = {{"error", "Player is not in this room"}};
        return;
    }
    // Algorithm
    a_state& state = current->get_state();
    if (input["method"] == "quit") {
        state.quit(input, output);
    }
    else if (input["method"] == "play") {
        state.play(output);
    }
    else if (input["method"] == "pause") {
        state.pause(output);
    }
    else if (input["method"] == "stop") {
        state.stop(output);
    }
    else if (input["method"] == "setup") {
        state.setup(input, output);
    }
    else if (input["method"] == "action") {
        state.action(input, output);
    }
    else {
        output = {{"error", "Method isn't correct"}};
    }

    if (sessions[input["session_id"]]->is_empty()) {
        sessions.erase(input["session_id"]);
        output = {{"success", "Session was deleted"}};
    }
}


