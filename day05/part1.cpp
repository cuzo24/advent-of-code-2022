#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <deque>

int main(int argc, char *argv[]) {
  if (argc > 1) {
    std::fstream file_stacks, file_instructions;
    file_stacks.open(argv[1], std::ios::in);

    if (file_stacks.is_open()) {
      std::vector<std::deque<char>> stacks(9, std::deque<char> ());
      std::string input;

      while (std::getline(file_stacks, input)) {
        for (int i = 1; i < input.length(); i += 4) {
          if (input[i] != ' ') {
            stacks[i / 4].push_back(input[i]);
          }
        }
      }

      file_instructions.open(argv[2], std::ios::in);
      if (file_instructions.is_open()) {
        std::regex str_pattern("[0-9]+");

        while (std::getline(file_instructions, input)) {
          if (input == "") continue;

          int quantity, from, to;
          std::regex_token_iterator<std::string::iterator> a(input.begin(), input.end(), str_pattern);

          quantity = atoi(&((std::string)*a++)[0]);
          from = atoi(&((std::string)*a++)[0]) - 1;
          to = atoi(&((std::string)*a++)[0]) - 1;

          for (int i = 0; i < quantity; i++) {
            char letter = stacks[from].front();
            stacks[from].pop_front();
            stacks[to].push_front(letter);
          }
        }

        std::string answer = "";
        for (int i = 0; i < stacks.size(); i++) {
          answer += stacks[i].front();
        }

        std::cout << answer << std::endl;
        file_instructions.close();
      }

      file_stacks.close();
    }
  }
  return 0;
}