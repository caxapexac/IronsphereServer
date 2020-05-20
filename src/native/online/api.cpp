#include "api.hpp"
#include "session.hpp"
#include "../base/includes.hpp"
#include "../structs/chat_message.hpp"

online::api::api () noexcept {
    delta_time = constants::lobby_delta_time;
    sessions = std::map<int, std::shared_ptr<session>>();
    chat_buffer = std::queue<stts::chat_message>();
    log_buffer = std::queue<std::string>();
    //lllll = l::lll(); FIXME
    //TODO log it (server started at xx:xx xx.xx.xxxx)
}

void online::api::update (json& output) {
    output["delta_time"] = delta_time;
    output["chat_buffer_updates"] = chat_buffer_updates;
    output["log_buffer_updates"] = log_buffer_updates;
    for (const auto& item : sessions) {
        item.second->update(output["sessions"][item.first]);
    }
}

void online::api::signal (json& input, json& output) {
    if (input["version"] == nullptr || input["version"].get<int>() != constants::version) {
        output = {{"error", "Please download the latest version of the game"}};
        return;
    }
    if (input["sender"] == nullptr || input["command"] == nullptr) {
        output = {{"error", "Input isn't correct"}};
        return;
    }

    if (input["command"] == "get_info") {
        get_info(output);
    }
    else if (input["command"] == "read_chat") {
        read_chat(output);
    }
    else if (input["command"] == "write_chat") {
        write_chat(input, output);
    }
    else if (input["command"] == "create_session") {
        create_session(input, output);
    }
    else if (input["command"] == "signal_session") {
        signal_session(input, output);
    }
    else {
        output = {{"error", "Command isn't correct"}};
    }
}

void online::api::get_info (json& output) {
    output["type"] = "info";
    output["data"]["status"] = "alive";

    int players_online = 0;
    for (const auto& item : sessions) {
        output["data"]["sessions"][item.first]["session_name"] = item.second->get_session_name();
        output["data"]["sessions"][item.first]["player_count"] = item.second->get_player_count();
        players_online += item.second->get_player_count();
    }

    output["data"]["players_online"] = players_online;
}

void online::api::read_chat (json& output) {
    output["type"] = "chat";
    json_tools::pack_queue(chat_buffer, output["data"]["chat_buffer"]);
}

void online::api::write_chat (json& input, json& output) {
    if (input["data"]["message"] == nullptr) {
        output = {{"error", "Input isn't correct"}};
        return;
        //TODO maybe into exceptions
    }
    chat_buffer.push(stts::chat_message(input["sender"].get<int>(), input["data"]["message"]));
    if (chat_buffer.size() > constants::chat_queue_capacity) chat_buffer.pop();
    output = {"success", "Message has been sent"};
    //TODO improve, make write_chat rooms
    //TODO important game events into write_chat (or log) (for example, logger::setup_lobby(this) then use logger::log_chat();
}

void online::api::create_session (json& input, json& output) {
    if (input["data"]["session_id"] == nullptr || input["data"]["session_name"] == nullptr) {
        output = {{"error", "Input isn't correct"}};
        return;
        //TODO maybe into exceptions
    }
    if (sessions[input["data"]["session_id"]] != nullptr) {
        output = {{"error", "Room is already exist"}};
        return;
    }
    ///
    sessions[input["data"]["session_id"]] = std::make_shared<session>(input["data"]["session_name"]);
    sessions[input["data"]["session_id"]]->join(input["sender"], output);
}

void online::api::signal_session (json& input, json& output) {
    if (input["data"]["method"] == nullptr || input["data"]["session_id"] == nullptr) {
        output = {{"error", "Input isn't correct"}};
        return;
        //TODO maybe into exceptions
    }

    std::shared_ptr<session> session = sessions[input["data"]["session_id"]];
    if (session == nullptr) {
        output = {{"error", "Session wasn't found"}};
        return;
    }

    ///
    std::string method = input["data"]["method"];
    if (method == "quit") {
        session->quit(input["data"]["payload"], output);
    }
    else if (method == "play") {
        session->play(output);
    }
    else if (method == "pause") {
        session->pause(output);
    }
    else if (method == "stop") {
        session->stop(output);
    }
    else if (method == "setup") {
        session->setup(input["data"]["payload"], output);
    }
    else if (method == "signal") {
        session->signal(input["data"]["payload"], output);
    }
    else {
        output = {{"error", "Method isn't correct"}};
    }

    if (sessions[input["data"]["session_id"]]->get_player_count() == 0) {
        sessions.erase(input["data"]["session_id"]);
        output = {{"success", "Session was deleted"}};
    }
}



