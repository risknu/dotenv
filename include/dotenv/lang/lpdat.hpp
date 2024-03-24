#pragma once
#ifndef DOTENV_LPDAT_HPP
#define DOTENV_LPDAT_HPP

#include <utility>
#include <string>

namespace types {
    const std::string comment = "comment";
    const std::string untitled = "untitled";
    const std::string string = "string";

    const std::string equal = "equal";

    const std::string endc = "endc";
    const std::string endl = "endl";
} namespace lp_data {
    const char ban_chars[] = {'=', '"', '\'', '#', '\n', '\0', ';'};
}

class token {
public:
    token(std::string  key_string, std::string  value_string);
    explicit token(const std::string& to_all_string);

    [[nodiscard]] std::string get_key() const;
    [[nodiscard]] std::string get_value() const;
private:
    std::string key_string;
    std::string value_string;
};

#endif //DOTENV_LPDAT_HPP
