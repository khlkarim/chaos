#include "utils/string.h"
#include <fstream>

bool isWhitespace(const std::string &s) {
  for (auto c : s) {
    if (!std::isspace(c)) {
      return false;
    }
  }

  return true;
}

std::string readEntireFile(const std::string &path) {
  std::ifstream f(path);
  std::string content, line;

  while (getline(f, line)) {
    content += line;
  }

  f.close();
  return content;
}

std::vector<std::string> split(const std::string &s, const std::string &d) {
  std::vector<std::string> res;

  std::string sub = s + d;
  int idx = sub.find(d);

  while (idx != std::string::npos) {
    if (idx > 0) {
      std::string a = sub.substr(0, idx);

      if (!isWhitespace(a)) {
        res.push_back(a);
      }
    }

    sub = sub.substr(idx + d.length());
    idx = sub.find(d);
  }

  return res;
}
