#ifndef DOTENVCPP_DOTENV_HPP
#define DOTENVCPP_DOTENV_HPP

#include <dotenv/env.hpp>
#include <dotenv/lang/lplang.hpp>
#include <dotenv/lang/lpdat.hpp>

#include <optional>
#include <map>

#include <iostream>
#include <fstream>
#include <string>

std::string read_env(const std::string& env_path);

namespace env {
    std::string env_path;
    std::map<std::string, std::string> env_dict;

    void set_env_path(std::string new_env_path);
    std::map<std::string, std::string> load_env();
}

#endif //DOTENVCPP_DOTENV_HPP
