#include <iostream>

#include <dotenv/lang/lpdat.hpp>
#include <dotenv/lang/lplang.hpp>

int main() {
    env_lang::lp_pos lexer_pos(-1, 0u, -1);
    env_lang::lexer_object lexer("TEST=ABC # this is comment\n", lexer_pos);
    std::vector<env_lang::token> lexer_out = lexer.to_token_vector();
    env_lang::lp_pos interpret_pos(-1, 0, -1);
    env_lang::interpret_to interpret(lexer_out, interpret_pos);
    interpret.interpret_tokens_to();

    std::cout << env::get_env("TEST") << std::endl;

    return EXIT_SUCCESS;
}
