#include <iostream>
#include <fstream>
#include <vector>
#include <set>

struct Rock {
  std::vector<std::pair<int, int>> coords;

  Rock(const std::vector<std::string> &shape, int bottom_edge) {
    int height = shape.size(), width = shape[0].length(), left_edge = 2;
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (shape[i][j] == '#') {
          coords.push_back(std::make_pair(left_edge + j, bottom_edge + height - (i + 1)));
        }
      }
    }
  }

  int get_top() const {
    int top = INT32_MIN;
    for (auto &coord : coords) {
      top = std::max(top, coord.second);
    }
    return top;
  }

  int get_left() const {
    int left = INT32_MAX;
    for (auto &coord : coords) {
      left = std::min(left, coord.first);
    }
    return left;
  }

  int get_right() const {
    int right = INT32_MIN;
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

bool is_colliding(const std::set<std::pair<int, int>> &grid, int width, const Rock &rock) {
  std::set<std::pair<int, int>>::const_iterator it;
  for (auto &coord : rock.coords) {
    it = grid.find(coord);
    if (it != grid.end() || coord.first < 0 || coord.first >= width || coord.second < 0) {
      return true;
    }
  }
  return false;
}

void store_position(std::set<std::pair<int, int>> &grid, const Rock &rock) {
  for (auto &coord : rock.coords) {
    grid.insert(coord);
  }
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string jet_pattern;
      int max_y = 0, jet_index = 0;
      const int steps = 2022, width = 7, number_of_shapes = 5;
      std::set<std::pair<int, int>> grid;
      std::getline(file, jet_pattern);
      std::pair<int, int> down{0, -1}, up{0, 1}, left{-1, 0}, right{1, 0};

      std::vector<std::vector<std::string>> shapes;
      shapes.push_back({"####"});
      shapes.push_back({".#.", "###", ".#."});
      shapes.push_back({"..#", "..#", "###"});
      shapes.push_back({"#", "#", "#", "#"});
      shapes.push_back({"##", "##"});

      for (int i = 0; i < steps; i++) {
        bool stopped = false;
        Rock rock(shapes[i % number_of_shapes], max_y + 3);

        while (!stopped) {
          if (jet_pattern[jet_index] == '<' && rock.get_left() > 0) {
            rock.move(left);
            if (is_colliding(grid, width, rock)) {
              rock.move(right);
            }
          } else if (jet_pattern[jet_index] == '>' && rock.get_right() < width + 1) {
            rock.move(right);
            if (is_colliding(grid, width, rock)) {
              rock.move(left);
            }
          }

          jet_index++;
          if (jet_index == jet_pattern.length()) jet_index = 0;

          rock.move(down);
          if (is_colliding(grid, width, rock)) {
            rock.move(up);
            store_position(grid, rock);
            max_y = std::max(rock.get_top() + 1, max_y); // top + 1 is the first empty row
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