#include "./Block.hpp"

#include <string>

std::string toy_lang::Block::to_string() {
  if (block_type_ == BlockType::Symbol) {
    return ":" + raw_val_;
  }
  if (block_type_ == BlockType::Number) {
    return raw_val_;
  }
  if (block_type_ == BlockType::String) {
    return "\"" + raw_val_ + "\"";
  }
  if (block_type_ == BlockType::Lambda) {
    return "<Lmabda>";
  }
  if (block_type_ == BlockType::Proc) {
    return "<Proc>";
  }
  if (block_type_ == BlockType::List) {
    std::string res = "(";
    for (auto b : args_) {
      res += b.to_string() + " ";
    }
    res += ")";
    return res;
  }
  return raw_val_;
}
