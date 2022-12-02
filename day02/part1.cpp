#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      long long int score = 0;
      int beats[] = {2, 0, 1};

      while (std::getline(file, input)) {
        if (input == "") continue;

        // opponent -> A = rock, B = paper, C = scissors
        // me -> X = rock, Y = paper, Z = scissors
        // rock -> 1 point, paper -> 2 points, scissors -> 3 points
        // lose -> 0 points, draw -> 3 points, won -> 6 points

        int opponent = (input[0] - 'A'), me = (input[2] - 'X');
        score += (me + 1);

        if (beats[me] == opponent) score += 6;
        else if (opponent == me) score += 3;
      }
      std::cout << score << std::endl;
      file.close();
    }
  }
  return 0;
}