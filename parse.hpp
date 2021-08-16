#ifndef _PARSE_HPP
#define _PARSE_HPP

#include <list>
#include <string>

#include "./Block.hpp"
#include "./constant.hpp"
#include "./lex.hpp"
#include "./util.hpp"

namespace toy_lang {
Block atom(const std::string& token) {
  if (is_digital(token.front()) || (token.front() == '-' && is_digital(token[1]))) {
    return Block(BlockType::Number, token);
  }

  if (token.front() == STR_START && token.back() == STR_END) {
    return Block(BlockType::String, token.substr(1, token.size() - 2));
  }

  return Block(BlockType::Symbol, token);
}

Block parse_from(std::list<std::string>& tokens) {
  std::string token = tokens.front();
  tokens.pop_front();
  if (token == "(") {
    std::list<Block> args;
    while (tokens.front() != ")") {
      args.push_back(parse_from(tokens));
    }
    tokens.pop_front();
    return Block(args);
  } else {
    return atom(token);
  }
}

Block parse(const std::string& source_code) {
  std::list<std::string> tokens = tokenize(source_code);
  return parse_from(tokens);
}

}  // namespace toy_lang

#endif
