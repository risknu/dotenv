#include <dotenv/dotenv.hpp>
#include <utility>

std::string read_env(const std::string& env_path) {
    std::ifstream input_file(env_path);
    if (!input_file)
        return "ERROR=\"File not found => `std::string read_env(const std::string& env_path);`\" # ENV ERROR\n";
    std::string tmp_line;
    std::string text_string_out;
    while (std::getline(input_file, tmp_line))
        text_string_out += tmp_line + '\n';
    input_file.close();
    return text_string_out;
}

namespace env {
    void set_env_path(std::string new_env_path) {
        env::env_path = std::move(new_env_path);
        std::string env_text = read_env(env::env_path);
        env_lang::lp_pos lexer_pos(-1, 0u, -1);
        env_lang::lexer_object lexer_class(env_text, lexer_pos);
        std::vector<env_lang::token> lexer_out = lexer_class.to_token_vector();

        env_lang::lp_pos interpret_pos(-1, 0u, -1);
        env_lang::interpret_to interpret_class(lexer_out, interpret_pos);
        interpret_class.interpret_tokens_to();

    }

}