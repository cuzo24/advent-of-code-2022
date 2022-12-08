#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      int answer = 0;
      std::vector<std::string> grid;
      std::vector<std::vector<bool>> included;

      while (std::getline(file, input)) {
        if (input == "") continue;

        int len = input.length();
        grid.push_back(input);
        included.push_back(std::vector<bool> (len, false));

        int max_left = -1, max_right = -1;
        for (int i = 0; i < len; i++) {
          if (!included.back()[i] && (input[i] - '0') > max_left) {
            included.back()[i] = true;
            answer++;
          }

          if (!included.back()[len - i - 1] && (input[len - i - 1] - '0') > max_right) {
            included.back()[len - i - 1] = true;
            answer++;
          }

          max_left = std::max(max_left, input[i] - '0');
          max_right = std::max(max_right, input[len - i - 1] - '0');
        }
      }

      for (int j = 0; j < grid[0].length(); j++) {
        int max_top = -1, max_bottom = -1;
        for (int i = 0; i < grid.size(); i++) {
          if (!included[i][j] && (grid[i][j] - '0') > max_top) {
            included[i][j] = true;
            answer++;
          }

          if (!included[grid.size() - i - 1][j] && (grid[grid.size() - i - 1][j] - '0') > max_bottom) {
            included[grid.size() - i - 1][j] = true;
            answer++;
          }

          max_top = std::max(max_top, grid[i][j] - '0');
          max_bottom = std::max(max_bottom, grid[grid.size() - i - 1][j] - '0');
        }
      }
      std::cout << answer << std::endl;
      file.close();
    }
  }
  return 0;
}