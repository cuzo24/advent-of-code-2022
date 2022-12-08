#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      int answer = 0;
      std::vector<std::string> grid;
      std::vector<std::vector<int>> from_left, from_right;

      while (std::getline(file, input)) {
        if (input == "") continue;

        int len = input.length();
        grid.push_back(input);
        from_left.push_back(std::vector<int> (len, len - 1));
        from_right.push_back(std::vector<int> (len, 0));

        std::stack<int> st_from_left, st_from_right;
        for (int i = 0; i < len; i++) {
          while (
              !st_from_left.empty() &&
              (input[i] - '0') >= (input[st_from_left.top()] - '0')
          ) {
            int top = st_from_left.top();
            st_from_left.pop();
            from_left.back()[top] = i;
          }

          while (
              !st_from_right.empty() &&
              (input[len - i - 1] - '0') >= (input[st_from_right.top()] - '0')
          ) {
            int top = st_from_right.top();
            st_from_right.pop();
            from_right.back()[top] = len - i - 1;
          }

          st_from_left.push(i);
          st_from_right.push(len - i - 1);
        }
      }

      int rows = grid.size(), cols = grid[0].length();
      std::vector<std::vector<int>> from_top(rows, std::vector<int> (cols, rows - 1));
      std::vector<std::vector<int>> from_bottom(rows, std::vector<int> (cols, 0));
      for (int j = 0; j < cols; j++) {
        std::stack<int> st_from_top, st_from_bottom;
        for (int i = 0; i < rows; i++) {
          while (
              !st_from_top.empty() &&
              (grid[i][j] - '0') >= (grid[st_from_top.top()][j] - '0')
          ) {
            int top = st_from_top.top();
            st_from_top.pop();
            from_top[top][j] = i;
          }

          while (
              !st_from_bottom.empty() &&
              (grid[rows - i - 1][j] - '0') >= (grid[st_from_bottom.top()][j] - '0')
          ) {
            int top = st_from_bottom.top();
            st_from_bottom.pop();
            from_bottom[top][j] = rows - i - 1;
          }

          st_from_top.push(i);
          st_from_bottom.push(rows - i - 1);
        }
      }

      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          int scenic_score = (
              (from_left[i][j] - j) * (j - from_right[i][j]) *
              (from_top[i][j] - i) * (i - from_bottom[i][j])
          );

          answer = std::max(scenic_score, answer);
        }
      }
      std::cout << answer << std::endl;
      file.close();
    }
  }
  return 0;
}