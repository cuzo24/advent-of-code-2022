#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      long long int signal_strength_sum = 0;
      int cycle = 1, x_register = 1;

      while (std::getline(file, input)) {
        if (input == "") continue;

        if (cycle % 40 == 20) {
          signal_strength_sum += cycle * x_register;
        }

        cycle++;
        if (input[0] == 'n') continue;
        int v = std::atoi(&input.substr(5)[0]);
        if (cycle % 40 == 20) {
          signal_strength_sum += cycle * x_register;
        }
        cycle++;
        x_register += v;
      }

      std::cout << signal_strength_sum << std::endl;
      file.close();
    }
  }
  return 0;
}