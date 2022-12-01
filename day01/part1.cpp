#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      long long int max = 0, curr_sum = 0;

      while (std::getline(file, input)) {
        if (input == "") {
          max = std::max(max, curr_sum);
          curr_sum = 0;
        } else {
          curr_sum += atoi(&input[0]);
        }
      }
      std::cout << max << std::endl;
      file.close();
    }
  }
  return 0;
}