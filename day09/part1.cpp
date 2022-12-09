#include <iostream>
#include <fstream>
#include <set>

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      std::set<std::pair<int, int>> visited;
      int head_x = 0, head_y = 0, tail_x = 0, tail_y = 0;
      visited.insert(std::make_pair(tail_x, tail_y));

      while (std::getline(file, input)) {
        if (input == "") continue;

        char dir = input[0];
        int quantity = atoi(&input.substr(2)[0]);

        for (int i = 0; i < quantity; i++) {
          if (dir == 'U') head_y++;
          else if (dir == 'D') head_y--;
          else if (dir == 'R') head_x++;
          else head_x--;

          if (std::abs(head_y - tail_y) == 2) {
            tail_y += head_y > tail_y ? 1 : -1;
            tail_x = head_x;
          } else if (std::abs(head_x - tail_x) == 2) {
            tail_x += head_x > tail_x ? 1 : -1;
            tail_y = head_y;
          }

          visited.insert(std::make_pair(tail_x, tail_y));
        }
      }

      std::cout << visited.size() << std::endl;
      file.close();
    }
  }
  return 0;
}