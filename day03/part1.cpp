#include <iostream>
#include <fstream>

inline bool is_uppercase(char letter) {
  return (0 <= letter - 'A' && letter - 'A' < 26);
}

inline int get_index(char letter) {
  return is_uppercase(letter) ? letter - 'A' + 26 : letter - 'a';
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      long long int sum = 0;

      while (std::getline(file, input)) {
        bool included[52] = {false};
        int len = input.length() / 2;

        for (int i = 0; i < len; i++) {
          int index = get_index(input[i]);
          included[index] = true;
        }

        for (int i = len; i < 2 * len; i++) {
          int index = get_index(input[i]);
          if (included[index]) {
            sum += index + 1;
            break;
          }
        }
      }
      std::cout << sum << std::endl;
      file.close();
    }
  }
  return 0;
}