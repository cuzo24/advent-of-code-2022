#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <regex>

struct Cube {
  int x, y, z;
  Cube() {}
  Cube(int x, int y, int z) : x(x), y(y), z(z) {}
};

bool operator== (const Cube &lhs, const Cube &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator< (const Cube &lhs, const Cube &rhs) {
  if (lhs.x != rhs.x) return lhs.x < rhs.x;
  if (lhs.y != rhs.y) return lhs.y < rhs.y;
  return lhs.z < rhs.z;
}

Cube parse_cube(const std::string &s) {
  Cube result;
  std::regex pattern("([-+]?[0-9]+)\\s*,\\s*([-+]?[0-9]+)\\s*,\\s*([-+]?[0-9]+)");
  std::smatch match_results;
  regex_search(s, match_results, pattern);
  result.x = std::atoi(match_results.str(1).data());
  result.y = std::atoi(match_results.str(2).data());
  result.z = std::atoi(match_results.str(3).data());
  return result;
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      int answer = 0;
      std::set<Cube> set;

      while (std::getline(file, input)) {
        if (input == "") continue;
        Cube cube = parse_cube(input);
        set.insert(cube);
      }

      std::vector<Cube> d{
          {-1, 0, 0}, {1, 0, 0},{0, -1, 0},
          {0, 1, 0}, {0, 0, -1}, {0, 0, 1}
      };
      for (auto &cube : set) {
        int total = 6;
        std::set<Cube>::iterator it;
        for (auto &dir : d) {
          it = set.find(Cube(cube.x + dir.x, cube.y + dir.y, cube.z + dir.z));
          if (it != set.end()) total--;
        }
        answer += total;
      }

      std::cout << answer << std::endl;
      file.close();
    }
  }
  return 0;
}