#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      int len = 4;

      while (std::getline(file, input)) {
        for (int i = 0; i <= input.length() - len; i++) {
          bool included[26] = {false}, done = true;
          for (int j = 0; j < len; j++) {
            if (included[input[i + j] - 'a']) {
              done = false;
              break;
            } else included[input[i + j] - 'a'] = true;
          }

          if (done) {
            std::cout << i + len << std::endl;
            break;;
          }
        }
      }
      file.close();
    }
  }
  return 0;
}