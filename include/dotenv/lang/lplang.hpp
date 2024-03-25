#pragma once
#ifndef DOTENV_LPLANG_HPP
#define DOTENV_LPLANG_HPP

#include <dotenv/env.hpp>
#include <dotenv/lang/lpdat.hpp>

#include <iostream>
#include <utility>
#include <map>
#include <string>
#include <vector>

namespace env_lang {
    class lp_pos {
    public:
        lp_pos(int global_char_index, int global_line_index, int local_char_index);
        explicit lp_pos(int global_to_all_index);

        [[nodiscard]] int get_global_char() const;
        [[nodiscard]] int get_global_line() const;
        [[nodiscard]] int get_local_char() const;

        int advance(char current_char);
        int advance(const token& current_token);
    private:
        int global_char_index;
        int global_line_index;
        int local_char_index;
    };

    class lexer_object {
    public:
        lexer_object(std::string text_string, const lp_pos& lp_pos_class);

        std::vector<token> to_token_vector();
    private:
        int advance_next();
        char current_char{};

        token tokenize_raw_string();
        token tokenize_string();
        token tokenize_comment();
        token tokenize_untitled();

        std::string text_string;
        lp_pos lp_pos_class;
    };

    class interpret_to {
    public:
        interpret_to(std::vector<token> tokens_vector, const lp_pos& lp_pos_class);

        void interpret_tokens_to();
        std::map<std::string, std::string> get_dict();
    private:
        int advance_next();
        token current_token;

        void interpret_kv_equal();

        token advance_NW();
        token advance_BW();

        std::vector<token> tokens_array;
        lp_pos lp_pos_class;
    };
}

#endif //DOTENV_LPLANG_HPP
