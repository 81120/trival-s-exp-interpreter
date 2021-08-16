#include <list>

#include "./Block.hpp"
#include "./runtime.hpp"

using Block     = toy_lang::Block;
using BlockType = toy_lang::BlockType;

Block add(const std::list<Block>& args) {
  float res = 0.0;
  for (auto e : args) {
    float i = std::stof(e.raw_val_);
    res += i;
  }
  return Block(BlockType::Number, std::to_string(res));
}

Block minus(const std::list<Block>& args) {
  float            res       = std::stof(args.front().raw_val_);
  std::list<Block> temp_args = args;
  temp_args.pop_front();
  for (auto& e : temp_args) {
    float i = std::stof(e.raw_val_);
    res -= i;
  }
  return Block(BlockType::Number, std::to_string(res));
}

Block times(const std::list<Block>& args) {
  float res = 1.0;
  for (auto& e : args) {
    float i = std::stof(e.raw_val_);
    res *= i;
  }
  return Block(BlockType::Number, std::to_string(res));
}

Block div_proc(const std::list<Block>& args) {
  float            res       = std::stof(args.front().raw_val_);
  std::list<Block> temp_args = args;
  for (auto& e : temp_args) {
    float i = std::stof(e.raw_val_);
    res /= i;
  }
  return Block(BlockType::Number, std::to_string(res));
}

Block bigger_or_eq(const std::list<Block>& args) {
  std::list<Block> temp_args = args;
  float            left_val  = std::stof(temp_args.front().raw_val_);
  temp_args.pop_front();
  float right_val = std::stof(temp_args.front().raw_val_);
  return Block(BlockType::Symbol, left_val >= right_val ? "#t" : "#f");
}

Block less_or_eq(const std::list<Block>& args) {
  std::list<Block> temp_args = args;
  float            left_val  = std::stof(temp_args.front().raw_val_);
  temp_args.pop_front();
  float right_val = std::stof(temp_args.front().raw_val_);
  return Block(BlockType::Symbol, left_val <= right_val ? "#t" : "#f");
}

Block exit_proc(const std::list<Block>& args) {
  exit(0);
  return Block(BlockType::Symbol, "nil");
}

int main() {
  toy_lang::Runtime rt;
  rt.set_build_in_proc_to_ctx("+", add);
  rt.set_build_in_proc_to_ctx("-", minus);
  rt.set_build_in_proc_to_ctx("*", times);
  rt.set_build_in_proc_to_ctx("/", div_proc);
  rt.set_build_in_proc_to_ctx(">=", bigger_or_eq);
  rt.set_build_in_proc_to_ctx("<=", less_or_eq);
  rt.set_build_in_proc_to_ctx("exit", exit_proc);

  rt.repl();

  return 0;
}

