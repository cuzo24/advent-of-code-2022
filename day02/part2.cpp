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
      int loses[] = {1, 2, 0};

      while (std::getline(file, input)) {
        if (input == "") continue;

        // opponent -> A = rock, B = paper, C = scissors
        // outcome -> X = lose, Y = draw, Z = won
        // rock -> 1 point, paper -> 2 points, scissors -> 3 points
        // lose -> 0 points, draw -> 3 points, won -> 6 points

        int opponent = (input[0] - 'A'), outcome = (input[2] - 'X');
        score += outcome * 3;

        score += 1;
        if (outcome == 0) score += beats[opponent];
        else if (outcome == 1) score += opponent;
        else score += loses[opponent];
      }
      std::cout << score << std::endl;
      file.close();
    }
  }
  return 0;
}