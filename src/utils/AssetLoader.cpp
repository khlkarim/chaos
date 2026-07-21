#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utils/AssetLoader.h"

bool isWhitespace(const std::string &s) {
  for (auto c : s) {
    if (!std::isspace(c)) {
      return false;
    }
  }

  return true;
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

Mesh AssetLoader::load(const std::string &path) {
  std::string line;
  std::ifstream f(path);

  Mesh mesh;
  std::map<std::string, int> faces;
  std::vector<std::vector<float>> v, vn, vt;

  while (getline(f, line)) {
    std::cout << "Line: " << line << std::endl;

    std::vector<std::string> a = split(line, " ");
    if (a.size() < 2) {
      continue;
    }

    if (a[0][0] == 'v') {
      std::vector<float> b;
      for (int i = 1; i < a.size(); i++) {
        b.push_back(std::stof(a[i]));
      }

      if (a[0] == "v") {
        v.push_back(b);
      } else if (a[0] == "vn") {
        vn.push_back(b);
      } else if (a[0] == "vt") {
        vt.push_back(b);
      }
    } else if (a[0] == "f") {
      std::vector<int> indices;

      for (int i = 1; i < a.size(); i++) {
        auto iter = faces.find(a[i]);

        if (iter != faces.end()) {
          indices.push_back(iter->second);

        } else {
          Vertex vertex;
          std::vector<std::string> c = split(a[i], "/");
          int nbSlash = std::count(a[i].begin(), a[i].end(), '/');

          int idx = std::stoi(c[0]);
          idx = idx > 0 ? idx - 1 : v.size() + idx;

          vertex.position = {v[idx][0], v[idx][1], v[idx][2]};
          if (v[idx].size() > 3) {
            vertex.color = {v[idx][3], v[idx][4], v[idx][5], 1};
          }

          idx = nbSlash == 1 || (nbSlash == 2 && c.size() == 3) ? std::stoi(c[1]) : 0;
          if (idx != 0) {
            idx = idx > 0 ? idx - 1 : vt.size() + idx;
            vertex.textureCoords = {vt[idx][0], vt[idx][1]};
          }

          idx = nbSlash == 2 ? std::stoi(c[c.size() - 1]) : 0;
          if (idx != 0) {
            idx = idx > 0 ? idx - 1 : vn.size() + idx;
            vertex.normal = {vn[idx][0], vn[idx][1], vn[idx][2]};
          }

          int index = mesh.vertices.size();
          mesh.vertices.push_back(vertex);

          faces[a[i]] = index;
          indices.push_back(index);
        }
      }

      for (int i = 1; i < indices.size() - 1; i += 2) {
        mesh.indices.push_back(indices[0]);
        mesh.indices.push_back(indices[i]);
        mesh.indices.push_back(indices[i + 1]);
      }
    }
  }

  f.close();
  return mesh;
}
