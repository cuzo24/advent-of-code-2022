#include <iostream>
#include <fstream>

inline bool fully_overlaps(int a, int b, int x, int y) {
  return ((a <= x && y <= b) || (x <= a && b <= y));
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      int overlaps = 0, total = 4;

      while (std::getline(file, input)) {
        int nums[total], j = 0, prev = 0;

        for (int i = 0; i < input.length(); i++) {
          if (input[i] == '-' || input[i] == ',') {
            nums[j] = atoi(&input.substr(prev, i - prev)[0]);
            prev = i + 1; j++;

            if (j + 1 == total) {
              nums[j] = atoi(&input.substr(i + 1)[0]);
              break;
            }
          }
        }

        if (fully_overlaps(nums[0], nums[1], nums[2], nums[3])) {
          overlaps++;
        }
      }
      std::cout << overlaps << std::endl;
      file.close();
    }
  }
  return 0;
}