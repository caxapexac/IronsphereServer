#include "api.hpp"
#include "session.hpp"
#include "../structs/chat_message.hpp"

online::api::api () noexcept {
    delta_time = constants::lobby_delta_time;
    chat_buffer_updates = 0;
    chat_buffer = std::queue<stts::chat_message>();
    sessions = std::map<int, std::shared_ptr<session>>();
    //lllll = l::lll(); FIXME
    //TODO log it (server started at xx:xx xx.xx.xxxx)
}

void online::api::update (json& output) {
    output[out_update::delta_time] = delta_time;
    output[out_update::chat_buffer_updates] = chat_buffer_updates;
    for (const auto& item : sessions) item.second->update(output[out_update::sessions][item.first]);
}

void online::api::signal (json& input, json& output) {
    output[out_signal::type] = api_type::signal;
    if (input[in_signal::version] == nullptr || input[in_signal::type] == nullptr || input[in_signal::sender] == nullptr) {
        output[out_signal::error] = "Input isn't correct";
        return;
    }
    if (input[in_signal::version].get<int>() != constants::version) {
        output[out_signal::error] = "Please download the latest version of the game";
        return;
    }

    std::string type = input[in_signal::type];
    if (type == api_type::server_info) server_info(output);
    else if (type == api_type::read_chat) read_chat(output);
    else if (type == api_type::write_chat) write_chat(input, output);
    else if (type == api_type::create_session) create_session(input, output);
    else signal_session(input, output);
}

void online::api::server_info (json& output) {
    output[out_signal::type] = api_type::server_info;
    for (const auto& item : sessions) item.second->session_info(output[out_server_info::sessions][item.first]);
}

void online::api::read_chat (json& output) {
    output[out_signal::type] = api_type::read_chat;
    json_tools::pack_queue(chat_buffer, output[out_read_chat::chat_buffer]);
}

void online::api::write_chat (json& input, json& output) {
    output[out_signal::type] = api_type::write_chat;
    if (input[in_write_chat::message] == nullptr) {
        output[out_signal::error] = "Input isn't correct";
        return;
    }
    int player_uid = input[in_signal::sender].get<int>();
    chat_buffer.push(stts::chat_message(player_uid, input[in_write_chat::message]));
    if (chat_buffer.size() > constants::chat_queue_capacity) chat_buffer.pop();
    chat_buffer_updates++;
    output[out_signal::success] = "Message has been sent";
    //TODO important game events into write_chat (or log) (for example, logger::setup_lobby(this) then use logger::log_chat();
}

void online::api::create_session (json& input, json& output) {
    output[out_signal::type] = api_type::create_session;
    if (input[in_create_session::session_id] == nullptr || input[in_create_session::session_name] == nullptr) {
        output[out_signal::error] = "Input isn't correct";
        return;
    }
    int session_id = input[in_create_session::session_id].get<int>();
    if (sessions[session_id] != nullptr) {
        output[out_signal::error] = "Room is already exist";
        return;
    }

    sessions[session_id] = std::make_shared<session>(input[in_create_session::session_name]);
    sessions[session_id]->join(input[in_signal::sender], output);
}

void online::api::signal_session (json& input, json& output) {
    output[out_signal::type] = api_type::signal_session;
    if (input[in_signal_session::session_id] == nullptr) {
        output[out_signal::error] = "Input isn't correct";
        return;
    }
    int session_id = input[in_signal_session::session_id].get<int>();
    std::shared_ptr<session> session = sessions[session_id];
    if (session == nullptr) {
        output[out_signal::error] = "Session wasn't found";
        return;
    }

    std::string type = input[in_signal::type];
    if (type == api_type::game_info) session->info(output);
    else if (type == api_type::game_load) session->load(input, output);
    else if (type == api_type::game_save) session->save(output);
    else if (type == api_type::game_join) session->join(input[in_signal::sender].get<int>(), output);
    else if (type == api_type::game_quit) session->quit(input[in_signal::sender].get<int>(), output);
    else if (type == api_type::game_play) session->play(output);
    else if (type == api_type::game_pause) session->pause(output);
    else if (type == api_type::game_stop) session->stop(output);
    else if (type == api_type::game_setup) session->setup(input, output);
    else if (type == api_type::game_signal) session->signal(input, output);
    else output[out_signal::error] = "Type isn't correct";

    if (session->get_player_count() == 0) {
        sessions.erase(session_id);
        output[out_signal::success] = "Session was deleted";
    }
}
