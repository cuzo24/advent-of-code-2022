#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>

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
      long long int x, y;
      std::regex pattern("[+-]?[0-9]+");
      const int n = 4000000;
      std::vector<std::pair<int, int>> sensors;
      std::vector<int> distances;
      int sensor_x, sensor_y, beacon_x, beacon_y;

      while (std::getline(file, input)) {
        if (input == "") continue;

        std::regex_iterator<std::string::iterator> it(input.begin(), input.end(), pattern);
        sensor_x = std::atoi(it->str(0).data()); it++;
        sensor_y = std::atoi(it->str(0).data()); it++;
        beacon_x = std::atoi(it->str(0).data()); it++;
        beacon_y = std::atoi(it->str(0).data()); it++;

        sensors.push_back(std::make_pair(sensor_x, sensor_y));
        distances.push_back(manhattan(sensor_x, sensor_y, beacon_x, beacon_y));
      }

      for (int i = 0; i <= n; i++) {
        int unavailable = 0;
        std::vector<std::pair<int, int>> ranges;
        std::vector<int> x_coords;

        for (int j = 0; j < sensors.size(); j++) {
          int remaining_dist = (
              distances[j] - manhattan(sensors[j].first, sensors[j].second, sensors[j].first, i)
          );
          if (remaining_dist >= 0) {
            int start = std::max(0, sensors[j].first - remaining_dist);
            int end = std::min(n, sensors[j].first + remaining_dist) + 1;
            ranges.push_back(std::make_pair(start, end));
            x_coords.push_back(start);
            x_coords.push_back(end);
          }
        }

        if (ranges.size() > 0) {
          sort(x_coords.begin(), x_coords.end());
          std::vector<bool> compressed(x_coords.size(), false);

          for (int j = 0; j < ranges.size(); j++) {
            int start = get_lower_bound(x_coords, ranges[j].first);
            int end = get_lower_bound(x_coords, ranges[j].second);

            for (int k = start; k < end; k++) {
              compressed[k] = true;
            }
          }

          for (int j = 0; j < compressed.size() - 1; j++) {
            if (compressed[j]) {
              unavailable += (x_coords[j + 1] - x_coords[j]);
            }
          }

          if (unavailable == n) {
            y = i;
            break;
          }
        }
      }

      for (int i = 0; i <= n; i++) {
        int unavailable = 0;
        std::vector<std::pair<int, int>> ranges;
        std::vector<int> y_coords;

        for (int j = 0; j < sensors.size(); j++) {
          int remaining_dist = (
              distances[j] - manhattan(sensors[j].first, sensors[j].second, i, sensors[j].second)
          );
          if (remaining_dist >= 0) {
            int start = std::max(0, sensors[j].second - remaining_dist);
            int end = std::min(n, sensors[j].second + remaining_dist) + 1;
            ranges.push_back(std::make_pair(start, end));
            y_coords.push_back(start);
            y_coords.push_back(end);
          }
        }

        if (ranges.size() > 0) {
          sort(y_coords.begin(), y_coords.end());
          std::vector<bool> compressed(y_coords.size(), false);

          for (int j = 0; j < ranges.size(); j++) {
            int start = get_lower_bound(y_coords, ranges[j].first);
            int end = get_lower_bound(y_coords, ranges[j].second);

            for (int k = start; k < end; k++) {
              compressed[k] = true;
            }
          }

          for (int j = 0; j < compressed.size() - 1; j++) {
            if (compressed[j]) {
              unavailable += (y_coords[j + 1] - y_coords[j]);
            }
          }

          if (unavailable == n) {
            x = i;
            break;
          }
        }
      }

      std::cout << x*n + y << std::endl;
      file.close();
    }
  }
  return 0;
}