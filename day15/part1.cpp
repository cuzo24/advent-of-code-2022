#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>
#include <set>

inline int manhattan(int x1, int y1, int x2, int y2) {
  return std::abs(x2 - x1) + std::abs(y2 - y1);
}

inline int get_lower_bound(const std::vector<int> &v, int value) {
  return static_cast<int>(std::lower_bound(v.begin(), v.end(), value) - v.begin());
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      int answer = 0;
      std::regex pattern("[+-]?[0-9]+");
      const int row = 2000000;
      std::set<int> beacons;
      std::vector<std::pair<int, int>> ranges;
      std::vector<int> x_coords;
      int sensor_x, sensor_y, beacon_x, beacon_y;

      while (std::getline(file, input)) {
        if (input == "") continue;

        std::regex_iterator<std::string::iterator> it(input.begin(), input.end(), pattern);
        sensor_x = std::atoi(it->str(0).data()); it++;
        sensor_y = std::atoi(it->str(0).data()); it++;
        beacon_x = std::atoi(it->str(0).data()); it++;
        beacon_y = std::atoi(it->str(0).data()); it++;

        if (beacon_y == row && beacons.insert(beacon_x).second) {
          answer--;
        }

        int manhattan_dist = manhattan(sensor_x, sensor_y, beacon_x, beacon_y);
        int remaining_dist = manhattan_dist - manhattan(sensor_x, sensor_y, sensor_x, row);
        if (remaining_dist >= 0) {
          ranges.push_back(std::make_pair(sensor_x - remaining_dist, sensor_x + remaining_dist + 1));
          x_coords.push_back(sensor_x - remaining_dist);
          x_coords.push_back(sensor_x + remaining_dist + 1);
        }
      }

      if (ranges.size() > 0) {
        sort(x_coords.begin(), x_coords.end());
        std::vector<bool> compressed(x_coords.size(), false);

        for (int i = 0; i < ranges.size(); i++) {
          int start = get_lower_bound(x_coords, ranges[i].first);
          int end = get_lower_bound(x_coords, ranges[i].second);

          for (int j = start; j < end; j++) {
            compressed[j] = true;
          }
        }

        for (int i = 0; i < compressed.size() - 1; i++) {
          if (compressed[i]) {
            answer += (x_coords[i + 1] - x_coords[i]);
          }
        }
      }

      std::cout << answer << std::endl;
      file.close();
    }
  }
  return 0;
}