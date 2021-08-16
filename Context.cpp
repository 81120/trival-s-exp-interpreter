#include "./Context.hpp"

#include <iostream>

void toy_lang::Context::show() {
  for (auto [name, val] : payload_) {
    std::cout << name << ":" << val.to_string() << std::endl;
  }
}

void toy_lang::Context::set_val(const std::string& name, Block val) {
  payload_[name] = val;
}

void toy_lang::Context::set_build_in_proc(const std::string& name,
                                          Block::ProcType    proc) {
  payload_[name] = Block(proc);
}

toy_lang::Block toy_lang::Context::get_val(const std::string& name) {
  auto temp = payload_.find(name);
  if (temp == payload_.end()) {
    return Block(BlockType::Symbol, "nil");
  }
  return temp->second;
}

toy_lang::Block toy_lang::Context::eval(Block b) {
  if (b.block_type_ == BlockType::Symbol) {
    std::string name = b.raw_val_;
    if (name == "nil" || name == "#t" || name == "#f" || name == "if" ||
        name == "define" || name == "set!" || name == "begin" ||
        name == "lambda") {
      return b;
    } else {
      return this->get_val(name);
    }
  } else if (b.block_type_ == BlockType::Number ||
             b.block_type_ == BlockType::String) {
    return b;
  } else if (b.block_type_ == BlockType::List) {
    Block op = b.args_.front();
    op       = this->eval(op);

    if (op.block_type_ == BlockType::Proc) {
      auto proc = op.proc_;
      b.args_.pop_front();
      std::list<Block> arguments;
      for (auto e : b.args_) {
        auto p = this->eval(e);
        arguments.push_back(p);
      }
      auto res = proc(arguments);
      return res;
    } else if (op.raw_val_ == "nil") {
      std::list<Block> res;
      for (auto e : b.args_) {
        res.push_back(this->eval(e));
      }
      return Block(res);
    } else if (op.raw_val_ == "if") {
      b.args_.pop_front();
      auto pre = b.args_.front().raw_val_ == "#t";
      b.args_.pop_front();
      if (!pre) {
        b.args_.pop_front();
      }
      return this->eval(b.args_.front());
    } else if (op.raw_val_ == "define" || op.raw_val_ == "set!") {
      b.args_.pop_front();
      std::string name = b.args_.front().raw_val_;
      b.args_.pop_front();
      this->set_val(name, this->eval(b.args_.front()));
      return Block(BlockType::Symbol, "nil");
    } else if (op.raw_val_ == "begin") {
      b.args_.pop_front();
      Block res(BlockType::Symbol, "nil");
      for (auto e : b.args_) {
        res = this->eval(e);
      }
      return res;
    } else if (op.raw_val_ == "lambda") {
      return Block(BlockType::Symbol, "nil");
    } else {
      return Block(BlockType::Symbol, "nil");
    }
  } else {
    return Block(BlockType::Symbol, "nil");
  }
}

