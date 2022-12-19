#include <iostream>
#include <fstream>
#include <vector>
#include <set>

struct Rock {
  std::vector<std::pair<long long int, long long int>> coords;

  Rock(const std::vector<std::string> &shape, long long int bottom_edge) {
    int height = shape.size(), width = shape[0].length(), left_edge = 2;
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (shape[i][j] == '#') {
          coords.push_back(std::make_pair(left_edge + j, bottom_edge + height - (i + 1)));
        }
      }
    }
  }

  long long int get_top() const {
    long long int top = INT64_MIN;
    for (auto &coord : coords) {
      top = std::max(top, coord.second);
    }
    return top;
  }

  long long int get_left() const {
    long long int left = INT64_MAX;
    for (auto &coord : coords) {
      left = std::min(left, coord.first);
    }
    return left;
  }

  long long int get_right() const {
    long long int right = INT64_MIN;
    for (auto &coord : coords) {
      right = std::max(right, coord.first);
    }
    return right;
  }

  void move(std::pair<int, int> dir) {
    for (auto &coord : coords) {
      coord.first += dir.first;
      coord.second += dir.second;
    }
  }
};

bool is_colliding(
    const std::set<std::pair<long long int, long long int>> &grid,
    int width, const Rock &rock, long long int floor
) {
  std::set<std::pair<long long int, long long int>>::const_iterator it;
  for (auto &coord : rock.coords) {
    it = grid.find(coord);
    if (it != grid.end() || coord.first < 0 || coord.first >= width || coord.second < floor) {
      return true;
    }
  }
  return false;
}

void store_position(std::set<std::pair<long long int, long long int>> &grid, const Rock &rock) {
  for (auto &coord : rock.coords) {
    grid.insert(coord);
  }
}

bool is_row_covered(
    const std::set<std::pair<long long int, long long int>> &grid, int width, int row
) {
  std::set<std::pair<long long int, long long int>>::const_iterator it;
  for (int col = 0; col < width; col++) {
    it = grid.find(std::make_pair(col, row));
    if (it == grid.end()) {
      return false;
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string jet_pattern;
      int jet_index = 0;
      long long int max_y = 0, floor = 0;
      const long long int steps = 1000000000000;
      const int number_of_shapes = 5, width = 7;
      std::vector<std::pair<long long int, long long int>> covered_floor(1, {-1, -1});
      std::set<std::pair<long long int, long long int>> grid;
      std::getline(file, jet_pattern);
      std::pair<int, int> down{0, -1}, up{0, 1}, left{-1, 0}, right{1, 0};

      std::vector<std::vector<std::string>> shapes;
      shapes.push_back({"####"});
      shapes.push_back({".#.", "###", ".#."});
      shapes.push_back({"..#", "..#", "###"});
      shapes.push_back({"#", "#", "#", "#"});
      shapes.push_back({"##", "##"});

      for (long long int i = 0; i < steps; i++) {
        bool stopped = false;
        Rock rock(shapes[i % number_of_shapes], max_y + 3);

        while (!stopped) {
          if (jet_pattern[jet_index] == '<' && rock.get_left() > 0) {
            rock.move(left);
            if (is_colliding(grid, width, rock, floor)) {
              rock.move(right);
            }
          } else if (jet_pattern[jet_index] == '>' && rock.get_right() < width + 1) {
            rock.move(right);
            if (is_colliding(grid, width, rock, floor)) {
              rock.move(left);
            }
          }

          jet_index++;
          if (jet_index == jet_pattern.length()) jet_index = 0;

          rock.move(down);
          if (is_colliding(grid, width, rock, floor)) {
            rock.move(up);
            store_position(grid, rock);
            max_y = std::max(rock.get_top() + 1, max_y);

            if (is_row_covered(grid, width, max_y - 1)) {
              covered_floor.push_back({max_y - 1, i});

              int len = covered_floor.size();
              auto second_to_last = covered_floor[len - 2], last = covered_floor[len - 1];

              if ((last.second - second_to_last.second) % number_of_shapes == 0) {
                long long int quotient = (
                    (steps - last.second - 1) / (last.second - second_to_last.second)
                );
                max_y += quotient * (last.first - second_to_last.first);
                i += quotient * (last.second - second_to_last.second);
                floor = max_y;
              }
            }
            stopped = true;
          }
        }
      }

      std::cout << max_y << std::endl;
      file.close();
    }
  }
  return 0;
}