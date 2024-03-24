#include <iostream>

#include <dotenv/lang/lpdat.hpp>
#include <dotenv/lang/lplang.hpp>

int main() {
    lp_pos lexer_pos(-1, 0u, -1);
    lexer_object lexer("TEST=ABC # this is comment\n", lexer_pos);
    std::vector<token> lexer_out = lexer.to_token_vector();
    lp_pos interpret_pos(-1, 0, -1);
    interpret_to interpret(lexer_out, interpret_pos);
    interpret.interpret_tokens_to();

    std::cout << get_env("TEST") << std::endl;

    return EXIT_SUCCESS;
}
