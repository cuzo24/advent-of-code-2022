#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

inline bool is_valid(int x, int y, int rows, int cols) {
  return (0 <= x && x < rows && 0 <= y && y < cols);
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      std::vector<std::vector<int>> height_map;
      std::stack<std::pair<int, int>> starting_choices;
      std::pair<int, int> end;

      while (std::getline(file, input)) {
        if (input == "") continue;

        int len = input.length();
        height_map.push_back(std::vector<int> (len));
        for (int i = 0; i < len; i++) {
          if (input[i] == 'S') {
            input[i] = 'a';
          } else if (input[i] == 'E') {
            end = std::make_pair(height_map.size() - 1, i);
            input[i] = 'z';
          }

          if (input[i] == 'a') starting_choices.push(std::make_pair(height_map.size() - 1, i));
          height_map.back()[i] = input[i] - 'a';
        }
      }

      int rows = height_map.size();
      int cols = height_map[0].size();
      std::vector<std::pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
      int minimum_steps = INT32_MAX;

      while (!starting_choices.empty()){
        std::vector<std::vector<int>> distances(rows, std::vector<int> (cols, -1));
        std::deque<std::pair<int, int>> q;
        std::pair<int, int> start = starting_choices.top();
        starting_choices.pop();
        distances[start.first][start.second] = 0;
        q.push_back(start);

        while (!q.empty()) {
          auto u = q.front();
          q.pop_front();

          for (auto &dir : directions) {
            std::pair<int, int> v = std::make_pair(u.first + dir.first, u.second + dir.second);
            if (
                is_valid(v.first, v.second, height_map.size(), height_map[0].size()) &&
                distances[v.first][v.second] == -1 &&
                height_map[u.first][u.second] + 1 >= height_map[v.first][v.second]
            ) {
              distances[v.first][v.second] = distances[u.first][u.second] + 1;
              q.push_back(v);
            }
          }
        }

        if (distances[end.first][end.second] != -1) {
          minimum_steps = std::min(minimum_steps, distances[end.first][end.second]);
        }
      }
      std::cout << minimum_steps << std::endl;
      file.close();
    }
  }
  return 0;
}