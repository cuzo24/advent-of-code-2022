#include <iostream>
#include <fstream>
#include <numeric>

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      const int n = 3;
      long long int max[n] = {0}, curr_sum = 0;

      while (std::getline(file, input)) {
        if (input == "") {
          bool swap = false;
          long long int previous;

          for (int i = 0; i < n; i++) {
            if (swap) {
              std::swap(previous, max[i]);
            } else if (curr_sum > max[i]) {
              previous = max[i];
              max[i] = curr_sum;
              swap = true;
            }
          }
          curr_sum = 0;
        } else {
          curr_sum += atoi(&input[0]);
        }
      }
      std::cout << std::accumulate(max, max + n, 0) << std::endl;
      file.close();
    }
  }
  return 0;
}