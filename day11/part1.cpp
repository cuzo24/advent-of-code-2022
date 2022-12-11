#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <deque>
#include <algorithm>

enum Operation {
  SUM,
  MULTIPLICATION
};

struct Monkey {
  std::deque<int> items;
  Operation op;
  int operand;
  int on_true;
  int on_false;
  int test;
  int business_level = 0;
};

int get_number(std::string input) {
  std::regex number_pattern("[0-9]+");
  std::regex_token_iterator<std::string::iterator> it(input.begin(), input.end(), number_pattern), rend;
  return (rend == it ? -1 : atoi(&((std::string)*it)[0]));
}

int get_worry_level(Operation op, int operand, int old_val) {
  if (operand == -1) operand = old_val;
  return (op == SUM ? old_val + operand : old_val * operand) / 3;
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      const int rounds = 20;
      std::regex number_pattern("[0-9]+");
      std::regex_token_iterator<std::string::iterator> rend;
      std::vector<Monkey> monkeys;

      while (std::getline(file, input)) {
        if (input == "") continue;

        monkeys.push_back(Monkey ());
        std::getline(file, input);
        {
          std::regex_token_iterator<std::string::iterator> it(input.begin(), input.end(), number_pattern);
          while(it != rend) monkeys.back().items.push_back(atoi(&((std::string)*(it++))[0]));
        }

        std::getline(file, input);
        monkeys.back().operand = get_number(input);
        for (int i = 0; i < input.length(); i++) {
          if (input[i] == '+') {
            monkeys.back().op = SUM;
          } else if (input[i] == '*') {
            monkeys.back().op = MULTIPLICATION;
          }
        }
        std::getline(file, input);
        monkeys.back().test = get_number(input);
        std::getline(file, input);
        monkeys.back().on_true = get_number(input);
        std::getline(file, input);
        monkeys.back().on_false = get_number(input);
      }

      for (int i = 0; i < rounds; i++) {
        for (int j = 0; j < monkeys.size(); j++) {
          while (!monkeys[j].items.empty()) {
            int item = monkeys[j].items.front();
            monkeys[j].items.pop_front();
            monkeys[j].business_level++;

            item = get_worry_level(monkeys[j].op, monkeys[j].operand, item);
            if (item % monkeys[j].test == 0) {
              monkeys[monkeys[j].on_true].items.push_back(item);
            } else {
              monkeys[monkeys[j].on_false].items.push_back(item);
            }
          }
        }
      }
      sort(monkeys.begin(), monkeys.end(), [](const Monkey &a, const Monkey &b) {
        return a.business_level > b.business_level;
      });

      std::cout << monkeys[0].business_level * monkeys[1].business_level << std::endl;
      file.close();
    }
  }
  return 0;
}