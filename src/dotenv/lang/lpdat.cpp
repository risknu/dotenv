#include "dotenv/lang/lpdat.hpp"

token::token(std::string  key_string, std::string  value_string) :
    key_string(std::move(key_string)), value_string(std::move(value_string)) {}
token::token(const std::string& to_all_string) :
    key_string(to_all_string), value_string(to_all_string) {}
std::string token::get_key() const { return key_string; }
std::string token::get_value() const { return value_string; }
