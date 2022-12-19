#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>
#include <map>

int get_max_flow(
    const std::vector<std::vector<int>> &adj, const std::vector<std::vector<int>> &cost,
    const std::vector<int> &rates, const std::vector<int> &nonzero_rates,
    std::vector<bool> &visited, int curr, int time_left
) {
  if (time_left <= 2) return 0;
  int max = 0;
  visited[curr] = true;

  for (int v : adj[curr]) {
    if (!visited[v]) {
      int time = time_left - cost[nonzero_rates[curr]][nonzero_rates[v]] - 1;
      if (time > 0) {
        int flow = time * rates[nonzero_rates[v]];
        max = std::max(max, get_max_flow(adj, cost, rates, nonzero_rates, visited, v, time) + flow);
      }
    }
  }

  visited[curr] = false;
  return max;
}

void get_shortest_paths(std::vector<std::vector<int>> &grid, const std::vector<std::vector<int>> &adj) {
  int len = adj.size();

  for (int u = 0; u < len; u++) {
    grid[u][u] = 0;
    for (int v : adj[u]) {
      grid[u][v] = 1;
    }
  }

  for (int k = 0; k < len; k++) {
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < len; j++) {
        grid[i][j] = std::min(grid[i][j], grid[i][k] + grid[k][j]);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input, start = "AA";
      int time = 30;
      const int INF = 1000000;
      std::vector<int> rates, nonzero_rates;
      std::vector<std::vector<int>> adj;
      std::map<std::string, int> mp;
      std::regex pattern("([A-Z]{2}|[0-9]+)");

      while (std::getline(file, input)) {
        if (input == "") continue;

        std::regex_iterator<std::string::iterator> it(input.begin(), input.end(), pattern), rend;
        std::string label = it->str(0); it++;
        int rate = std::stoi(it->str(0).data()); it++;

        auto mp_it = mp.find(label);
        if (mp_it == mp.end()) {
          mp.insert(std::make_pair(label, rates.size()));
          adj.push_back(std::vector<int> ());
          rates.push_back(rate);
        } else {
          rates[mp_it->second] = rate;
        }

        if (rate > 0) {
          nonzero_rates.push_back(mp[label]);
        }

        while (it != rend) {
          std::string valve = it->str(0); it++;
          mp_it = mp.find(valve);
          if (mp_it == mp.end()) {
            mp.insert(std::make_pair(valve, rates.size()));
            adj.push_back(std::vector<int> ());
            rates.push_back(0);
          }

          adj[mp[label]].push_back(mp[valve]);
        }
      }

      nonzero_rates.push_back(mp[start]);
      std::vector<std::vector<int>> cost(rates.size(), std::vector<int> (rates.size(), INF));
      std::vector<std::vector<int>> modified_adj(nonzero_rates.size(), std::vector<int> ());
      std::vector<bool> visited(nonzero_rates.size(), false);
      get_shortest_paths(cost, adj);

      for (int i = 0; i < nonzero_rates.size(); i++) {
        for (int j = 0; j < nonzero_rates.size(); j++) {
          int c = cost[nonzero_rates[i]][nonzero_rates[j]];
          if (0 < c && c < INF) {
            modified_adj[i].push_back(j);
          }
        }
      }

      std::cout << (
          get_max_flow(modified_adj, cost, rates, nonzero_rates, visited, nonzero_rates.size() - 1, time)
      ) << std::endl;
      file.close();
    }
  }
  return 0;
}