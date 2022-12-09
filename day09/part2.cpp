#include <iostream>
#include <fstream>
#include <vector>
#include <set>

void follow(const std::pair<int, int> &head, std::pair<int, int> &tail) {
  bool already_moved_x = false;

  if (std::abs(head.first - tail.first) == 2) {
    tail.first += head.first > tail.first ? 1 : -1;
    already_moved_x = true;
    if (std::abs(head.second - tail.second) == 1) {
      tail.second = head.second;
    }
  }

  if (std::abs(head.second - tail.second) == 2) {
    tail.second += head.second > tail.second ? 1 : -1;
    if (!already_moved_x && std::abs(head.first - tail.first) == 1) {
      tail.first = head.first;
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      const int n = 10;
      std::string input;
      std::vector<std::pair<int, int>> knots(n, {0, 0});
      std::set<std::pair<int, int>> visited;
      visited.insert(knots.back());

      while (std::getline(file, input)) {
        if (input == "") continue;

        char dir = input[0];
        int quantity = atoi(&input.substr(2)[0]);

        for (int i = 0; i < quantity; i++) {
          if (dir == 'U') knots[0].second++;
          else if (dir == 'D') knots[0].second--;
          else if (dir == 'R') knots[0].first++;
          else knots[0].first--;

          for (int j = 1; j < n; j++) {
            follow(knots[j - 1], knots[j]);
          }

          visited.insert(knots.back());
        }
      }

      std::cout << visited.size() << std::endl;
      file.close();
    }
  }
  return 0;
}