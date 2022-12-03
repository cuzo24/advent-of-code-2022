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
      std::string elf[3] = {""};
      const int elves = 3;
      long long int sum = 0;

      while (
          std::getline(file, elf[0]) &&
          std::getline(file, elf[1]) &&
          std::getline(file, elf[2])
      ) {
        int included[52] = {0};
        for (int i = 0; i < elves; i++) {
          for (int j = 0; j < elf[i].length(); j++) {
            int index = get_index(elf[i][j]);
            included[index] = included[index] | (1 << i);

            if (i + 1 == elves && included[index] == (1 << elves) - 1) {
              sum += index + 1;
              break;
            }
          }
        }
      }
      std::cout << sum << std::endl;
      file.close();
    }
  }
  return 0;
}