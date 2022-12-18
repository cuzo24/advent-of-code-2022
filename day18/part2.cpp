#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <regex>
#include <deque>

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
      int MAX_N = INT32_MIN, MIN_N = INT32_MAX;
      std::set<Cube> set;

      while (std::getline(file, input)) {
        if (input == "") continue;
        Cube cube = parse_cube(input);
        MAX_N = std::max({MAX_N, cube.x, cube. y, cube.z});
        MIN_N = std::min({MIN_N, cube.x, cube. y, cube.z});
        set.insert(cube);
      }

      std::set<Cube>::iterator it;
      std::vector<Cube> d{
          {-1, 0, 0}, {1, 0, 0},{0, -1, 0},
          {0, 1, 0}, {0, 0, -1}, {0, 0, 1}
      };

      bool visited[(MAX_N - MIN_N + 1) + 2][(MAX_N - MIN_N + 1) + 2][(MAX_N - MIN_N + 1) + 2] = {false};
      std::deque<Cube> q;
      q.push_back(Cube(MIN_N - 1, MIN_N - 1, MIN_N - 1));
      visited[0][0][0] = true;
      std::set<Cube> water_cubes;

      while(!q.empty()) {
        Cube cube = q.front();
        q.pop_front();
        water_cubes.insert(cube);

        for (auto &dir : d) {
          Cube other(cube.x + dir.x, cube.y + dir.y, cube.z + dir.z);
          if (
              MIN_N - 1 <= other.x && other.x <= MAX_N + 1 &&
              MIN_N - 1 <= other.y && other.y <= MAX_N + 1 &&
              MIN_N - 1 <= other.z && other.z <= MAX_N + 1 &&
              !visited[other.x - MIN_N + 1][other.y - MIN_N + 1][other.z - MIN_N + 1]
          ) {
            visited[other.x - MIN_N + 1][other.y - MIN_N + 1][other.z - MIN_N + 1] = true;
            it = set.find(other);
            if (it == set.end()) {
              q.push_back(other);
            }
          }
        }
      }

      for (auto &cube : water_cubes) {
        std::set<Cube>::iterator it;
        for (auto &dir : d) {
          it = set.find(Cube(cube.x + dir.x, cube.y + dir.y, cube.z + dir.z));
          if (it != set.end()) answer++;
        }
      }

      std::cout << answer << std::endl;
      file.close();
    }
  }
  return 0;
}