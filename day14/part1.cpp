#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <set>

int get_number(std::string input) {
  std::regex number_pattern("[0-9]+");
  std::regex_token_iterator<std::string::iterator> it(input.begin(), input.end(), number_pattern), rend;
  return (rend == it ? -1 : atoi(&((std::string)*it)[0]));
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      int answer = 0;
      int max_y = INT32_MIN;
      std::set<std::pair<int, int>> grid;
      std::regex pattern("([+-]?[0-9]+)\\s*,\\s*([+-]?[0-9]+)");

      while (std::getline(file, input)) {
        if (input == "") continue;

        std::regex_iterator<std::string::iterator> it(input.begin(), input.end(), pattern), rend;
        auto prev_coord = std::make_pair(std::stoi(it->str(1).data()), std::stoi(it->str(2).data()));
        max_y = std::max(max_y, prev_coord.second);
        while (++it != rend) {
          auto next_coord = std::make_pair(std::stoi(it->str(1).data()), std::stoi(it->str(2).data()));
          max_y = std::max(max_y, next_coord.second);
          if (prev_coord.first == next_coord.first) {
            for (
                int i = std::min(prev_coord.second, next_coord.second);
                i <= std::max(prev_coord.second, next_coord.second); i++
            ) {
              grid.insert(std::make_pair(prev_coord.first, i));
            }
          } else {
            for (
                int i = std::min(prev_coord.first, next_coord.first);
                i <= std::max(prev_coord.first, next_coord.first); i++
            ) {
              grid.insert(std::make_pair(i, prev_coord.second));
            }
          }
          prev_coord = next_coord;
        }
      }

      bool done = false;
      const int initial_x = 500, initial_y = 0;
      auto initial_coords = std::make_pair(initial_x, initial_y);
      std::vector<std::pair<int, int>> d{{0, 1}, {-1, 1}, {1, 1}};

      while (!done) {
        bool stopped = false;
        std::pair<int, int> coords = initial_coords, next;
        auto it = grid.find(initial_coords);
        if (it != grid.end()) break;

        while (!stopped) {
          bool has_moved = false;
          for (auto &dir: d) {
            next = std::make_pair(coords.first + dir.first, coords.second + dir.second);
            it = grid.find(next);
            if (it == grid.end()) {
              has_moved = true;
              coords = next;
              break;
            }
          }

          if (has_moved) {
            if (coords.second > max_y) {
              done = true;
              stopped = true;
            }
          } else {
            answer++;
            stopped = true;
            grid.insert(coords);
          }
        }
      }

      std::cout << answer << std::endl;
      file.close();
    }
  }
  return 0;
}