#include "./runtime.hpp"

#include <iostream>
#include <string>

#include "./parse.hpp"

std::string toy_lang::Runtime::get_prompt() {
  return prompt_;
}

void toy_lang::Runtime::set_prompt(std::string prompt) {
  prompt_ = prompt;
}

toy_lang::Context toy_lang::Runtime::get_context() {
  return ctx_;
}

void toy_lang::Runtime::set_context(toy_lang::Context& ctx) {
  ctx_ = ctx;
}

toy_lang::Block toy_lang::Runtime::get_val_from_ctx(std::string name) {
  return ctx_.get_val(name);
}

void toy_lang::Runtime::set_val_to_ctx(std::string name, Block val) {
  ctx_.set_val(name, val);
}

void toy_lang::Runtime::set_build_in_proc_to_ctx(std::string     name,
                                                 Block::ProcType proc) {
  ctx_.set_build_in_proc(name, proc);
}

void toy_lang::Runtime::repl() {
  while (true) {
    std::cout << prompt_;
    std::string line;
    std::getline(std::cin, line);
    if (line.size() == 0) {
      continue;
    }
    Block item = parse(line);
    Block res  = ctx_.eval(item);
    std::cout << res.to_string() << std::endl;
  }
}

