#include "logger_file.hpp"

void l::logger_file::write_to_file (std::string& filename, std::string& verbal) {
    std::ofstream out;
    out.open(filename, std::ofstream::out | std::fstream::app);
    out << verbal << std::endl;
    out.flush();
    out.close();
}

void l::logger_file::let (std::string& verbal, streams stream) {
    std::string PATH = std::string(R"(C:\Users\miles\Documents\untitled\)");

    std::string this_file_name = PATH + get_time_name(false);
    std::string all_file_name = this_file_name + "_all.log";

    switch (stream) {
        case error:
            this_file_name += "_error.log";
            break;
        case warning:
            this_file_name += "_warning.log";
            break;
        case debug:
            this_file_name += "_debug.log";
            break;
        case message:
            this_file_name += "_message.log";
            break;
        case special:
            this_file_name += "_special.log";
            break;
    }

    write_to_file(this_file_name, verbal);
    write_to_file(all_file_name, verbal);
}
