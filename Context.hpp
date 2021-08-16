#ifndef _CONTEXT_HPP
#define _CONTEXT_HPP

#include <map>
#include <string>

#include "./Block.hpp"

namespace toy_lang {
class Context {
 public:
  Context() {
  }

  void  set_val(const std::string& name, Block val);
  Block get_val(const std::string& name);
  void  set_build_in_proc(const std::string& name, Block::ProcType proc);
  Block eval(Block b);
  void  show();

 private:
  std::map<std::string, Block> payload_;
};
}  // namespace toy_lang

#endif

