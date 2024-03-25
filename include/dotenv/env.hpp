#pragma once
#ifndef DOTENV_ENV_HPP
#define DOTENV_ENV_HPP

#include <cstdlib>
#include <string>
#ifndef _WIN32
    #include <unistd.h>
#else
    #include <windows.h>
#endif

namespace env {
    std::string get_env(std::string_view key_name);
    bool set_env(std::string_view key_name, std::string_view value_string);
}

#endif //DOTENV_ENV_HPP
