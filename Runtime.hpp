#ifndef _RUNTIME_HPP
#define _RUNTIME_HPP

#include <string>

#include "./Block.hpp"
#include "./Context.hpp"

namespace toy_lang {
class Runtime {
 public:
  Runtime() {
  }

  Runtime(std::string prompt) : prompt_(prompt) {
  }

  std::string get_prompt();
  void        set_prompt(std::string prompt);
  Context     get_context();
  void        set_context(Context& context);
  Block       get_val_from_ctx(std::string name);
  void        set_val_to_ctx(std::string name, Block val);
  void        set_build_in_proc_to_ctx(std::string name, Block::ProcType proc);
  void        repl();

 private:
  std::string prompt_ = "toy_lang>>)";
  Context     ctx_;
};
}  // namespace toy_lang

#endif

