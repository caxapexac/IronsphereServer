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
        item.second->update(output["sessions"][item.first]);
    }
}

void game_lobby::signal (json& input, json& output) {
    if (input["version"] == nullptr || input["version"].get<int>() != constants::version) {
        output = {{"error", "Please download the latest version of the game"}};
        return;
    }

    if (input["command"] == nullptr) {
        output = {{"error", "Input isn't correct"}};
        return;
    }
    ///
    if (input["command"] == "get_info") {
        get_info(output);
    }
    else if (input["command"] == "write_chat") {
        write_chat(input["data"], output);
    }
    else if (input["command"] == "create_session") {
        create_session(input["data"], output);
    }
    else if (input["command"] == "signal_session") {
        signal_session(input["data"], output);
    }
    else {
        output = {{"error", "Command isn't correct"}};
    }
}

void game_lobby::get_info (json& output) {
    output["status"] = "alive";

    int players_online = 0;
    for (const auto& item : sessions) {
        output["sessions"][item.first]["session_name"] = item.second->get_session_name();
        output["sessions"][item.first]["player_count"] = item.second->get_player_count();
        players_online += item.second->get_player_count();
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

void game_lobby::create_session (json& input, json& output) {
    if (input["method"] == nullptr || input["session_id"] == nullptr || input["sender"] == nullptr || input["session_name"] == nullptr) {
        output = {{"error", "Input isn't correct"}};
        return;
        //TODO maybe into exceptions
    }
    if (sessions[input["session_id"]] != nullptr) {
        output = {{"error", "Room is already exist"}};
        return;
    }
    ///
    sessions[input["session_id"]] = std::make_shared<game_session>(input["session_name"]);
    sessions[input["session_id"]]->join(input["sender"], output);
}

void game_lobby::signal_session (json& input, json& output) {
    if (input["method"] == nullptr || input["session_id"] == nullptr || input["sender"] == nullptr) {
        output = {{"error", "Input isn't correct"}};
        return;
        //TODO maybe into exceptions
    }

    std::shared_ptr<game_session> session = sessions[input["session_id"]];
    if (session == nullptr) {
        output = {{"error", "Session wasn't found"}};
        return;
    }

    ///
    if (input["method"] == "quit") {
        session->quit(input, output);
    }
    else if (input["method"] == "play") {
        session->play(output);
    }
    else if (input["method"] == "pause") {
        session->pause(output);
    }
    else if (input["method"] == "stop") {
        session->stop(output);
    }
    else if (input["method"] == "setup") {
        session->setup(input, output);
    }
    else if (input["method"] == "signal") {
        session->signal(input, output);
    }
    else {
        output = {{"error", "Method isn't correct"}};
    }

    if (sessions[input["session_id"]]->get_player_count() == 0) {
        sessions.erase(input["session_id"]);
        output = {{"success", "Session was deleted"}};
    }
}


