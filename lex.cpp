#include "./lex.hpp"

#include <list>
#include <string>

#include "./constant.hpp"

std::list<std::string> toy_lang::tokenize(const std::string& source_code) {
  std::list<std::string> tokens;
  const char*            p = source_code.c_str();
  while (*p) {
    while (*p == STR_SPACE) {
      ++p;
    }
    if (*p == L_BRACE || *p == R_BRACE) {
      tokens.push_back(std::string(1, *p));
      ++p;
    } else if (*p == STR_START) {
      const char* s = p;
      while (*s && *s != STR_END) {
        ++s;
      }
      tokens.push_back(std::string(p, s + 1));
      p = s + 1;
    } else {
      const char* t = p;
      while (*t && *t != STR_SPACE && *t != STR_START && *t != STR_END &&
             *t != L_BRACE && *t != R_BRACE) {
        ++t;
      }
      tokens.push_back(std::string(p, t));
      p = t;
    }
  }

  return tokens;
}

