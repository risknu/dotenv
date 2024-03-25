#include <dotenv/env.hpp>

namespace env {
    std::string get_env(std::string_view key_name) {
        #ifdef _WIN32
            char buffer[1024];
            DWORD length = GetEnvironmentVariable(key_name.data(), buffer, sizeof(buffer));
            if (length != 0)
                return buffer;
            else
                return "EXIT_FAILURE_NEZ";
        #elif defined(__unix__) || defined(__APPLE__)
            char* env_value = getenv(key_name.c_str());
                if (env_value == nullptr)
                    return "EXIT_FAILURE_NLPTR";
                return std::string(env_value);
        #else
            return "EXIT_FAILURE_OS";
        #endif
    }

    bool set_env(std::string_view key_name, std::string_view value_string) {
        #ifdef _WIN32
            if (SetEnvironmentVariable(key_name.data(), value_string.data()))
                return EXIT_SUCCESS;
            else
                return EXIT_FAILURE;
        #elif defined(__unix__) || defined(__APPLE__)
            return setenv(key_name.c_str(), value_string.c_str(), 1) == 0;
        #else
            return EXIT_FAILURE;
        #endif
    }
}
