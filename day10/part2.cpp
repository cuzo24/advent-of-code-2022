#include <iostream>
#include <fstream>

void handle_cycle(int cycle_number, int x_register, int n) {
  int cycle_mod_n = cycle_number % n;
  std::cout << ((x_register <= cycle_mod_n && cycle_mod_n <= x_register + 2) ? '#' : '.');
  if (cycle_mod_n == 0) {
    std::cout << std::endl;
  }
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      int cycle = 1, cycle_mod, x_register = 1;
      const int n = 40;

      while (std::getline(file, input)) {
        if (input == "") continue;

        handle_cycle(cycle, x_register, n);
        cycle++;
        if (input[0] == 'n') continue;

        int v = std::atoi(&input.substr(5)[0]);
        handle_cycle(cycle, x_register, n);
        cycle++;
        x_register += v;
      }

      file.close();
    }
  }
  return 0;
}