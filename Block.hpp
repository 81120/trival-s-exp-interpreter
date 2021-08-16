#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <functional>
#include <list>
#include <map>
#include <string>
#include <vector>

namespace toy_lang {
enum BlockType { Symbol, Number, String, List, Proc, Lambda };

class Block {
 public:
  using ProcType = std::function<Block(const std::list<Block>&)>;

  Block() : block_type_(BlockType::Symbol) {
  }

  Block(BlockType block_type, std::string raw_val)
      : block_type_(block_type), raw_val_(raw_val) {
  }

  Block(std::list<Block> args) : block_type_(BlockType::List), args_(args) {
  }

  Block(ProcType proc) : block_type_(BlockType::Proc), proc_(proc) {
  }

  std::string to_string();

  BlockType              block_type_;
  ProcType               proc_;
  std::string            raw_val_;
  std::list<Block>       args_;
};
}  // namespace toy_lang

#endif
