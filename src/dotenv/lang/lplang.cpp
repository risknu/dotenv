#include <utility>

#include "dotenv/lang/lplang.hpp"

lp_pos::lp_pos(int global_char_index, int global_line_index, int local_char_index) :
    global_char_index(global_char_index), global_line_index(global_line_index), local_char_index(local_char_index) {}
lp_pos::lp_pos(int global_to_all_index) :
    global_char_index(global_to_all_index), global_line_index(global_to_all_index), local_char_index(global_to_all_index) {}
int lp_pos::get_global_char() const { return global_char_index; }
int lp_pos::get_global_line() const { return global_line_index; }
int lp_pos::get_local_char() const { return local_char_index; }
int lp_pos::advance(const char current_char) {
    ++global_char_index;
    ++local_char_index;
    if (current_char == '\n' || current_char == ';') {
        ++global_line_index;
        local_char_index = 0u;
    }
    return global_char_index;
} int lp_pos::advance(const token &current_token) {
    ++global_char_index;
    ++local_char_index;
    if (current_token.get_key() == types::endc) {
        ++global_line_index;
        local_char_index = 0u;
    }
    return global_char_index;
}

lexer_object::lexer_object(std::string text_string, const lp_pos &lp_pos_class) :
    text_string(std::move(text_string)), lp_pos_class(lp_pos_class) {}
int lexer_object::advance_next() {
    lp_pos_class.advance(current_char);
    if (lp_pos_class.get_global_char() < text_string.size())
        current_char = text_string[lp_pos_class.get_global_char()];
    else
        current_char = '\0';
    return  lp_pos_class.get_global_char();
}
std::vector<token> lexer_object::to_token_vector() {
    advance_next();
    std::vector<token> tmp_tokens_vector;
    while (current_char != '\0') {
        if (current_char == '\n' || current_char == ';') {
            tmp_tokens_vector.emplace_back(types::endl, types::endl);
            advance_next();
        } else if (current_char == '=') {
            tmp_tokens_vector.emplace_back(types::equal, types::equal);
            advance_next();
        } else if (current_char == '\'' || current_char == '"') {
            if (current_char == '\'')
                tmp_tokens_vector.push_back(tokenize_raw_string());
            else
                tmp_tokens_vector.push_back(tokenize_string());
            advance_next();
        } else if (current_char == '#')
            tmp_tokens_vector.push_back(tokenize_comment());
        else
            tmp_tokens_vector.push_back(tokenize_untitled());
    }
    tmp_tokens_vector.emplace_back(types::endc, types::endc);
    return tmp_tokens_vector;
}
token lexer_object::tokenize_raw_string() {
    std::string tmp_string;
    advance_next();
    while (current_char != '\0' && current_char != '\'') {
        tmp_string += current_char;
        advance_next();
    }
    return {types::string, tmp_string};
} token lexer_object::tokenize_string() {
    std::string tmp_string;
    advance_next();
    while (current_char != '\0' && current_char != '"') {
        tmp_string += current_char;
        advance_next();
    }
    return {types::string, tmp_string};
} token lexer_object::tokenize_comment() {
    std::string tmp_comment_description;
    advance_next();
    while (current_char != '\n') {
        tmp_comment_description += current_char;
        advance_next();
    }
    return {types::comment, tmp_comment_description};
} token lexer_object::tokenize_untitled() {
    std::string tmp_untitled;
    bool is_close = false;
    while (!is_close) {
        tmp_untitled += current_char;
        advance_next();
        for (char ban_char : lp_data::ban_chars) {
            if (ban_char == current_char) {
                is_close = true;
                break;
            }
        }
    }
    return {types::untitled, tmp_untitled};
}

interpret_to::interpret_to(std::vector<token> tokens_vector, const lp_pos &lp_pos_class) :
    tokens_array(std::move(tokens_vector)), lp_pos_class(lp_pos_class), current_token(token(types::endl)) {}
int interpret_to::advance_next() {
    lp_pos_class.advance(current_token);
    if (lp_pos_class.get_global_char() < tokens_array.size())
        current_token = tokens_array[lp_pos_class.get_global_char()];
    else
        current_token = token(types::endc);
    return  lp_pos_class.get_global_char();
} token interpret_to::advance_NW() {
    if (lp_pos_class.get_global_char()+1 < tokens_array.size())
        return tokens_array[lp_pos_class.get_global_char()+1];
    return token(types::endc);
} token interpret_to::advance_BW() {
    if (lp_pos_class.get_global_char()-1 < tokens_array.size())
        return tokens_array[lp_pos_class.get_global_char()-1];
    return token(types::endc);
}
void interpret_to::interpret_tokens_to() {
    advance_next();
    while (current_token.get_key() != types::endc) {
        if (current_token.get_key() == types::equal)
            interpret_kv_equal();
        else
            advance_next();
    }
} void interpret_to::interpret_kv_equal() {
    std::string key_value = advance_BW().get_value();
    std::string value_string = advance_NW().get_value();
    advance_next();
    bool set_status = set_env(key_value, value_string);
}
